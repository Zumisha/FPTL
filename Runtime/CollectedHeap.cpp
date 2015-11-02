#include "CollectedHeap.h"

#include <functional>
#include <iterator>

namespace FPTL { namespace Runtime {

CollectedHeap::CollectedHeap(GarbageCollector * collector)
	: mAllocatedSize(0),
	mGarbageSize(0),
	mCollector(collector)
{
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

bool CollectedHeap::isMyObject(const Collectable * object) const
{
	return object->myHeap == this;
}

void CollectedHeap::moveObject(Collectable * object)
{
	mAllocated.erase(mAllocated.iterator_to(*object));
	mAlive.push_back(*object);
}

void CollectedHeap::switchHeap()
{
	mGarbage.splice(mGarbage.end(), mAllocated);
	mAllocated.swap(mAlive);
}

void CollectedHeap::sweepObject(Collectable * object)
{
	mGarbage.erase_and_dispose(mGarbage.iterator_to(*object), disposer);
}

void CollectedHeap::registerObject(Collectable * object, size_t size)
{
	object->myHeap = this;
	mAllocated.push_back(*object);
	mAllocatedSize += size;
}

}}
