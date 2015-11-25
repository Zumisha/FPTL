#include "CollectedHeap.h"
#include "GarbageCollector.h"

#include <functional>
#include <iterator>

namespace FPTL { namespace Runtime {

//-----------------------------------------------------------------------------
CollectedHeap::CollectedHeap(GarbageCollector * collector)
	: mAllocatedSize(0),
	mCollector(collector),
	mMaxHeapSize(std::numeric_limits<size_t>::max())
{
	mCollector->registerHeap(this);

	disposer = [](Collectable * obj) { 
		delete obj;
	};
}

CollectedHeap::~CollectedHeap()
{
	// ������� ��� ���������� ������.
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

void CollectedHeap::setLimit(size_t size)
{
	mMaxHeapSize = size;
}

void CollectedHeap::checkFreeSpace(size_t size)
{
	if (mAllocatedSize + size > mMaxHeapSize)
	{
		mCollector->runGc();
	}
}

void CollectedHeap::registerObject(Collectable * object, size_t size)
{
	mAllocated.push_front(*object);
	mAllocatedSize += size;
}

//-----------------------------------------------------------------------------

}}