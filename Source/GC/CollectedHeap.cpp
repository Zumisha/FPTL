#include <functional>

#include "CollectedHeap.h"
#include "GarbageCollector.h"

namespace FPTL::Runtime {
	CollectedHeap::CollectedHeap(GarbageCollector * collector)
		: mAllocatedSize(0),
		  mMaxHeapSize(std::numeric_limits<size_t>::max()),
		  mCollector(collector)
	{
		mCollector->registerHeap(this);

		disposer = [](const Collectable * obj) {
			delete obj;
		};
	}

	CollectedHeap::~CollectedHeap()
	{
		mAllocated.clear_and_dispose(disposer);
	}

	size_t CollectedHeap::heapSize() const
	{
		return mAllocatedSize;
	}

	CollectedHeap::MemList CollectedHeap::reset()
	{
		MemList allocated;
		allocated.swap(mAllocated);
		mAllocatedSize = 0;
		return allocated;
	}

	void CollectedHeap::setLimit(const size_t size)
	{
		mMaxHeapSize = size;
	}

	void CollectedHeap::checkFreeSpace(const size_t size) const {
		if (mAllocatedSize + size > mMaxHeapSize)
		{
			mCollector->runGc();
		}
	}

	void CollectedHeap::registerObject(Collectable * object, const size_t size)
	{
		mAllocated.push_front(*object);
		mAllocatedSize += size;
	}
}
