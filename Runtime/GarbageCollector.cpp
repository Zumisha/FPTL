#include "GarbageCollector.h"
#include "CollectedHeap.h"
#include "BlockingQueue.h"

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <functional>

#include <boost/timer/timer.hpp>

namespace FPTL {
namespace Runtime {

typedef std::vector<const DataValue *> MarkList;

//-------------------------------------------------------------------------------
class ObjectMarkerImpl : public ObjectMarker
{
public:
	ObjectMarkerImpl()
		: mAliveSize(0)
	{}

	virtual bool markAlive(Collectable * object, size_t size)
	{
		if (ObjectMarker::checkAge(object, Collectable::YOUNG))
		{
			ObjectMarker::setObjectAge(object, Collectable::OLD);
			mAliveSize += size;
			return true;
		}

		return false;
	}

	virtual void addChild(const DataValue * child)
	{
		mMarkStack.push_back(child);
	}

	size_t aliveSize() const
	{
		return mAliveSize;
	}

	int traceDataRecursively()
	{
		int count = 0;

		while (!mMarkStack.empty())
		{
			const DataValue * val = mMarkStack.back();
			mMarkStack.pop_back();

			val->getOps()->mark(*val, this);
			count++;
		}

		return count;
	}

private:
	size_t mAliveSize;
	MarkList mMarkStack;
};

//-------------------------------------------------------------------------------
class GarbageCollectorImpl : public GarbageCollector
{
private:
	struct GcJob
	{
		ObjectMarkerImpl marker;
		CollectedHeap::MemList allocated;
	};

public:
	GarbageCollectorImpl(int numThreads, DataRootExplorer * rootExplorer)
		: mStopped(0),
		mThreads(numThreads),
		mStop(0),
		mRootExplorer(rootExplorer),
		mQuit(false),
		mSizeAlive(0),
		mVerbose(false)
	{
		new (&mCollectorThread) std::thread(std::bind(&GarbageCollectorImpl::collectorThreadLoop, this));
	}

	virtual ~GarbageCollectorImpl()
	{
		mQuit = true;
		mQueue.quit();
		mCollectorThread.join();
		mAllocated.clear_and_dispose([](Collectable * obj) { delete obj; });
	}

	virtual void runGc(CollectedHeap * heap)
	{
		// Проверяем, не начал ли кто-нибудь другой сборку мусора.
		while (!mGcMutex.try_lock())
		{
			safePoint();
		}

		boost::timer::cpu_timer pauseTimer;

		{
			std::unique_lock<std::mutex> lock(mRunMutex);

			// Посылаем команду на остановку других потоков.
			mStop.store(1, std::memory_order_release);
			mStopped++;

			// Ждем, пока они остановятся.
			mRunCond.wait(lock, [this] { return mStopped == mThreads; });
			mStopped--;
		}

		GcJob * job = new GcJob();

		// Сканируем корни.
		mRootExplorer->markRoots(&job->marker);

		// Сбрасываем списке выделенной памяти во всех кучах.
		for (auto heap : mHeaps)
		{
			job->allocated.splice(job->allocated.end(), heap->reset());
		}

		// Добавляем задание на сборку мусора.
		mQueue.push(job);

		{
			std::unique_lock<std::mutex> lock(mRunMutex);

			// Возобновляем работу других потоков.
			mStop.store(0, std::memory_order_relaxed);
			mRunCond.notify_all();
		}

		//std::cout << "GC pause time : " << boost::timer::format(pauseTimer.elapsed()) << "\n";

		mGcMutex.unlock();
	}

	virtual void safePoint()
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

	virtual void registerHeap(CollectedHeap * heap)
	{
		mHeaps.push_back(heap);
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

			GcJob * job = deqJob.get();

			boost::timer::cpu_timer gcTimer;

			// Помечаем доступные вершины.
			int count = job->marker.traceDataRecursively();

			// Очищаем память.
			job->allocated.remove_and_dispose_if(
				[](const Collectable & obj)
				{ 
					return ObjectMarker::checkAge(&obj, Collectable::YOUNG);
				},
				[](Collectable * obj)
				{
					delete obj;
				}
			);

			mSizeAlive += job->marker.aliveSize();
			mAllocated.splice(mAllocated.end(), job->allocated);

			//std::cout << "GC time : " << boost::timer::format(gcTimer.elapsed()) << "\n";

			delete job;
		}
	}

private:
	bool mVerbose;

	std::atomic<int> mStop;
	int mStopped;
	int mThreads;
	std::mutex mGcMutex;
	std::mutex mRunMutex;
	std::condition_variable mRunCond;

	DataRootExplorer * mRootExplorer;
	std::vector<CollectedHeap *> mHeaps;
	size_t mSizeAlive;

	// Общие структуры данных.
	BlockingQueue<GcJob *> mQueue;
	bool mQuit;

	// Структуры данных потока сборки мусора.
	std::thread mCollectorThread;
	CollectedHeap::MemList mAllocated;
};

//-------------------------------------------------------------------------------
GarbageCollector * GarbageCollector::getCollector(int numThreads, DataRootExplorer * rootExplorer)
{
	return new GarbageCollectorImpl(numThreads, rootExplorer);
}

}

//-------------------------------------------------------------------------------
void Runtime::ObjectMarker::setObjectAge(Collectable * object, int age)
{
	object->age = static_cast<Collectable::Age>(age);
}

//-------------------------------------------------------------------------------
bool Runtime::ObjectMarker::checkAge(const Collectable * object, int age)
{
	return object->age == age;
}

}
