#pragma once

#include <boost/intrusive/list.hpp>

#include "Context.h"

namespace FPTL {
namespace Runtime {

class GarbageCollector;

class CollectedHeap
{
public:
	CollectedHeap(GarbageCollector * collector);

	~CollectedHeap();

	template<typename T>
	T * allocate(size_t size)
	{
		void * memory = operator new(size);
		T * object = new (memory) T;
		registerObject(object, size);
		return object;
	}

	template<typename T>
	T * allocate(std::function<T *(void *)> constructor, size_t size)
	{
		void * memory = operator new(size);
		T * object = constructor(memory);
		registerObject(object, size);
		return object;
	}

	bool isMyObject(const Collectable * object) const;

	void moveObject(Collectable * object);

	void switchHeap();

private:
	void sweepObject(Collectable * object);

	void registerObject(Collectable * object, size_t size);

private:
	boost::intrusive::list<Collectable> mAllocated;
	boost::intrusive::list<Collectable> mAlive;
	boost::intrusive::list<Collectable> mGarbage;
	size_t mAllocatedSize;
	size_t mGarbageSize;
	std::function<void(Collectable *)> disposer;
	GarbageCollector * mCollector;
};


}
}