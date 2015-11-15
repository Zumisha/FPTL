#pragma once

#include <boost/intrusive/slist.hpp>

#include "Context.h"

namespace FPTL {
namespace Runtime {

class GarbageCollector;

//-------------------------------------------------------------------------------
class CollectedHeap
{
public:
	typedef boost::intrusive::slist<Collectable> MemList;

	CollectedHeap(GarbageCollector * collector);

	~CollectedHeap();

	template<typename T>
	T * allocate(size_t size)
	{
		checkFreeSpace(size);
		void * memory = operator new(size);
		T * object = new (memory) T;
		registerObject(object, size);
		return object;
	}

	template<typename T>
	T * allocate(std::function<T *(void *)> constructor, size_t size)
	{
		checkFreeSpace(size);
		void * memory = operator new(size);
		T * object = constructor(memory);
		registerObject(object, size);
		return object;
	}

	void updateStats(size_t sizeAlive);

	int heapSize() const;

	MemList reset();

private:
	void checkFreeSpace(size_t size);

	void sweepObject(Collectable * object);

	void registerObject(Collectable * object, size_t size);

private:
	MemList mAllocated;
	MemList mAlive;
	MemList mGarbage;
	size_t mAllocatedSize;
	size_t mGarbageSize;
	size_t mMaxHeapSize;
	std::function<void(Collectable *)> disposer;
	GarbageCollector * mCollector;
	int mGcCount;
};


}
}