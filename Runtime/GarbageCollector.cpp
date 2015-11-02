#include "GarbageCollector.h"
#include "CollectedHeap.h"

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>

namespace FPTL {
namespace Runtime {

class GarbageCollectorImpl : public GarbageCollector
{
public:
	GarbageCollectorImpl(int numThreads, DataRootExplorer * rootExplorer)
		: mStopped(0),
		mThreads(numThreads),
		mStop(0),
		mRootExplorer(rootExplorer),
		mCollectedHeap(nullptr)
	{}

	virtual void markAlive(Collectable * object, size_t size)
	{
		if (mCollectedHeap->isMyObject(object))
		{
			mCollectedHeap->moveObject(object);
		}
	}

	virtual void addChild(const DataValue * child)
	{
		mMarkStack.push_back(child);
	}

	virtual void runIfNeed(CollectedHeap * heap)
	{
		assert(false);
	}

	virtual void runGc(CollectedHeap * heap)
	{
		// Проверяем, не начал ли кто-нибудь другой сборку мусора.
		while (!mGcMutex.try_lock())
		{
			safePoint();
		}

		mCollectedHeap = heap;

		{
			std::unique_lock<std::mutex> lock(mRunMutex);

			// Посылаем команду на остановку других потоков.
			mStop.store(1, std::memory_order_release);
			mStopped++;

			// Ждем, пока они остановятся.
			mRunCond.wait(lock, [this] { return mStopped == mThreads; });
			mStopped--;
		}

		reset();

		// Сканируем корни.
		mRootExplorer->markRoots(this);

		{
			std::unique_lock<std::mutex> lock(mRunMutex);

			// Возобновляем работу других потоков.
			mStop.store(0, std::memory_order_relaxed);
			mRunCond.notify_all();
		}

		// Продолжаем сборку мусора.
		traceDataRecursively();
		mCollectedHeap->switchHeap();
		mCollectedHeap = nullptr;
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
	
private:
	void traceDataRecursively()
	{
		while (!mMarkStack.empty())
		{
			const DataValue * val = mMarkStack.back();
			mMarkStack.pop_back();

			val->getOps()->mark(*val, this);
		}
	}

	void reset()
	{
		mSizeAlive = 0;
	}

private:
	std::atomic<int> mStop;
	
	int mStopped;
	int mThreads;

	std::mutex mGcMutex;

	std::mutex mRunMutex;
	std::condition_variable mRunCond;

	DataRootExplorer * mRootExplorer;

	std::vector<const DataValue *> mMarkStack;
	size_t mSizeAlive;
	CollectedHeap * mCollectedHeap;
};

GarbageCollector * GarbageCollector::getCollector(int numThreads, DataRootExplorer * rootExplorer)
{
	return new GarbageCollectorImpl(numThreads, rootExplorer);
}

}}
