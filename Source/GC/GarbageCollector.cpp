#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>
#include <iostream>
#include <thread>

#include <boost/timer/timer.hpp>

#include "GarbageCollector.h"
#include "CollectedHeap.h"
#include "BlockingQueue.h"

namespace FPTL
{
	namespace Runtime
	{
		typedef std::vector<const DataValue *> MarkList;

		ObjectMarker::~ObjectMarker() = default;

		//-------------------------------------------------------------------------------
		class RootMarker : public ObjectMarker
		{
		public:
			explicit RootMarker(const Collectable::Age maxAge)
				: mMaxAge(maxAge)
			{}

			bool markAlive(Collectable * object, size_t size) override
			{
				if (ObjectMarker::checkAge(object, mMaxAge))
				{
					// Т.к. корни помечаются из потоков мутатора, то в этом методе
					// мы не маркируем объекты, а лишь заносим их в список для
					// дальнейшей маркировки, чтобы избежать гонки со сборщиком.
					mRoots.emplace_back(object, size);
					return true;
				}

				return false;
			}

			void addChild(const DataValue * child) override
			{
				mMarkStack.push_back(child);
			}

			std::vector<std::pair<Collectable *, size_t>> mRoots;
			MarkList mMarkStack;
			Collectable::Age mMaxAge;
		};

		//-------------------------------------------------------------------------------
		class HeapMarker : public ObjectMarker
		{
		public:
			HeapMarker()
				: mAliveSize(0), mMaxAge()
			{
			}

			HeapMarker(RootMarker & rootMarker, const size_t aliveSize)
				: mAliveSize(aliveSize),
				mMaxAge(rootMarker.mMaxAge)
			{
				mMarkStack.swap(rootMarker.mMarkStack);
			}

			bool markAlive(Collectable * object, const size_t size) override
			{
				if (!object->isMarked() && ObjectMarker::checkAge(object, mMaxAge))
				{
					ObjectMarker::setMarked(object, 1);
					mAliveSize += size;
					return true;
				}

				return false;
			}

			void addChild(const DataValue * child) override
			{
				mMarkStack.push_back(child);
			}

			size_t aliveSize() const
			{
				return mAliveSize;
			}

			size_t traceDataRecursively()
			{
				size_t count = 0;

				while (!mMarkStack.empty())
				{
					const auto val = mMarkStack.back();
					mMarkStack.pop_back();

					val->getOps()->mark(*val, this);
					count++;
				}

				return count;
			}

		private:
			size_t mAliveSize;
			MarkList mMarkStack;
			Collectable::Age mMaxAge;
		};

		//-------------------------------------------------------------------------------
		class GarbageCollectorImpl : public GarbageCollector
		{
		private:
			struct GcJob
			{
				RootMarker marker;
				CollectedHeap::MemList allocated;
				size_t allocatedSize;
				bool fullGc;

				GcJob() :
					marker(Collectable::YOUNG),
					allocatedSize(0),
					fullGc(false)
				{}

				explicit GcJob(const bool fullGc)
					: marker(fullGc ? Collectable::OLD : Collectable::YOUNG),
					allocatedSize(0),
					fullGc(fullGc)
				{}
			};

		public:
			GarbageCollectorImpl(const size_t numMutatorThreads, DataRootExplorer * rootExplorer, const GcConfig & config)
				: mConfig(config),
				mStopped(0),
				mThreads(numMutatorThreads),
				mRootExplorer(rootExplorer),
				mOldGenSize(0),
				mStop(false),
				mQuit(false),
				mCollectOld(false)
			{
				mCollectorThread = std::thread(std::bind(&GarbageCollectorImpl::collectorThreadLoop, this));
			}

			virtual ~GarbageCollectorImpl()
			{
				mQuit = true;
				mQueue.quit();
				mCollectorThread.join();
				mAllocated.clear_and_dispose([](Collectable * obj) { delete obj; });
			}

			void runGc() override
			{
				if (!mConfig.enabled())
				{
					return;
				}

				// Проверяем, не начал ли кто-нибудь другой сборку мусора.
				while (!mGcMutex.try_lock())
				{
					safePoint();
				}

				boost::timer::cpu_timer pauseTimer;

				{
					std::unique_lock<std::mutex> lock(mRunMutex);

					// Посылаем команду на остановку других потоков.
					mStop.store(true, std::memory_order_release);
					mStopped++;

					// Ждем, пока они остановятся.
					mRunCond.wait(lock, [this] { return mStopped == mThreads; });
					mStopped--;
				}

				std::unique_ptr<GcJob> job(new GcJob(mCollectOld));

				// Сканируем корни.
				mRootExplorer->markRoots(&job->marker);

				// Сбрасываем списке выделенной памяти во всех кучах.
				for (auto heap : mHeaps)
				{
					job->allocatedSize += heap->heapSize();
					//XXX buf added because temporary lvalue can't be passed to non const refference
					auto buf = heap->reset();
					job->allocated.splice(job->allocated.end(), buf);
				}

				// Добавляем задание на сборку мусора.
				mQueue.push(std::move(job));

				{
					std::unique_lock<std::mutex> lock(mRunMutex);

					// Возобновляем работу других потоков.
					mStop.store(false, std::memory_order_relaxed);
					mRunCond.notify_all();
				}

				if (mConfig.verbose())
				{
					std::cout
						<< "GC Pause. Time: " << boost::timer::format(pauseTimer.elapsed());
				}

				mGcMutex.unlock();
			}

			// Этот метод выполняется другими потоками для ожидании сканирования корней.
			void safePoint() override
			{
				if (mStop.load(std::memory_order_acquire) == 1)
				{
					std::unique_lock<std::mutex> lock(mRunMutex);

					mStopped++;
					mRunCond.notify_all();

					mRunCond.wait(lock, [this] { return mStop.load(std::memory_order_relaxed) == 0; });
					mStopped--;
				}
			}

			void registerHeap(CollectedHeap * heap) override
			{
				mHeaps.push_back(heap);
				heap->setLimit(mConfig.youngGenSize());
			}

		private:
			void collectorThreadLoop()
			{
				while (!mQuit)
				{
					auto deqJob = mQueue.pop();

					if (!deqJob.is_initialized())
					{
						break;
					}

					auto job = std::move(deqJob.get());

					boost::timer::cpu_timer gcTimer;

					// Маркируем корневые объекты.
					size_t aliveSize = 0;
					for (const auto object : job->marker.mRoots)
					{
						const auto root = object.first;
						if (!root->isMarked())
						{
							ObjectMarker::setMarked(root, 1);
							aliveSize += object.second;
						}
					}

					HeapMarker marker(job->marker, aliveSize);

					// Помечаем доступные вершины.
					auto count = marker.traceDataRecursively();

					if (job->fullGc)
					{
						job->allocated.splice(job->allocated.end(), mAllocated);
						job->allocatedSize += mOldGenSize;
						mOldGenSize = 0;
						mCollectOld = false;
					}

					// Очищаем память.
					job->allocated.remove_and_dispose_if([](const Collectable & obj) { return !obj.isMarked(); },
						[](Collectable * obj) {	delete obj;	});

					// Сбрасываем флаги.
					for (auto & object : job->allocated)
					{
						ObjectMarker::setObjectAge(&object, Collectable::OLD);
						ObjectMarker::setMarked(&object, 0);
					}

					mOldGenSize += marker.aliveSize();
					mAllocated.splice(mAllocated.end(), job->allocated);

					if (mConfig.verbose())
					{
						std::cout
							<< "GC time : " << boost::timer::format(gcTimer.elapsed())
							<< "Reclaimed: " << (job->allocatedSize - marker.aliveSize()) / (1024 * 1024) << " MiB. OldGen: "
							<< mOldGenSize / (1024 * 1024) << " MiB \n";
					}

					if (mOldGenSize > mConfig.oldGenSize())
					{
						std::cout << "\n\nERROR: out of memory\n";
						::exit(1);
					}

					if (mOldGenSize > mConfig.oldGenGCThreshold())
					{
						mCollectOld = true;
					}
				}
			}

		private:
			GcConfig mConfig;

			// Количество остановившихся потоков.
			size_t mStopped;

			// Количество потоков мутатора.
			size_t mThreads;

			std::mutex mGcMutex;
			std::mutex mRunMutex;
			std::condition_variable mRunCond;

			DataRootExplorer * mRootExplorer;
			std::vector<CollectedHeap *> mHeaps;
			size_t mOldGenSize;

			// Общие структуры данных.
			BlockingQueue<std::unique_ptr<GcJob>> mQueue;

			// Флаг, сигнализирующий о необходимости остановки.
			std::atomic<bool> mStop;

			bool mQuit;
			bool mCollectOld;

			// Структуры данных потока сборки мусора.
			std::thread mCollectorThread;
			CollectedHeap::MemList mAllocated;
		};

		//-------------------------------------------------------------------------------
		GarbageCollector * GarbageCollector::getCollector(const size_t numThreads, DataRootExplorer * rootExplorer, const GcConfig & config)
		{
			return new GarbageCollectorImpl(numThreads, rootExplorer, config);
		}

	}

	//-------------------------------------------------------------------------------
	void Runtime::ObjectMarker::setObjectAge(Collectable * object, int age)
	{
		object->meta.age = static_cast<Collectable::Age>(age);
	}

	//-------------------------------------------------------------------------------
	bool Runtime::ObjectMarker::checkAge(const Collectable * object, const int age)
	{
		return object->meta.age <= age;
	}

	void Runtime::ObjectMarker::setMarked(Collectable * object, const unsigned int flag)
	{
		object->meta.marked = flag;
	}
}
