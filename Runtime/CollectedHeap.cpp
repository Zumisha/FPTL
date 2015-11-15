#include "CollectedHeap.h"
#include "GarbageCollector.h"

#include <functional>
#include <iterator>

namespace FPTL { namespace Runtime {

CollectedHeap::CollectedHeap(GarbageCollector * collector)
	: mAllocatedSize(0),
	mGarbageSize(0),
	mCollector(collector),
	mMaxHeapSize(20 * 1024*1024),
	mGcCount(0)
{
	mCollector->registerHeap(this);

	disposer = [](Collectable * obj) { 
		delete obj;
	};
}

CollectedHeap::~CollectedHeap()
{
	// Очищаем всю выделенную память.
	mGarbage.clear_and_dispose(disposer);
	mAllocated.clear_and_dispose(disposer);
}

void CollectedHeap::updateStats(size_t sizeAlive)
{
	mGarbageSize = mAllocatedSize - sizeAlive;
	mAllocatedSize = sizeAlive;
}

int CollectedHeap::heapSize() const
{
	return mAllocatedSize + mGarbageSize;
}

CollectedHeap::MemList CollectedHeap::reset()
{
	MemList allocated;
	allocated.swap(mAllocated);
	mAllocatedSize = 0;
	return allocated;
}

void CollectedHeap::checkFreeSpace(size_t size)
{
	if (mAllocatedSize + size > mMaxHeapSize)
	{
		mCollector->runGc(this);
		mGcCount++;
	}
}

void CollectedHeap::sweepObject(Collectable * object)
{
	mGarbage.erase_and_dispose(mGarbage.iterator_to(*object), disposer);
}

void CollectedHeap::registerObject(Collectable * object, size_t size)
{
	object->age = Collectable::YOUNG;
	mAllocated.push_front(*object);
	mAllocatedSize += size;
}

}}
