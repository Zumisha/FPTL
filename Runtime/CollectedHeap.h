#pragma once

#include <boost/intrusive/slist.hpp>

#include "Context.h"
#include "GcAwarePtr.h"

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

	template <typename T> GcAwarePtr<T> alloc(size_t size);
	template <typename T> GcAwarePtr<T> alloc(std::function<T *(void *)> constructor, size_t size);

	size_t heapSize() const;

	MemList reset();

	void setLimit(size_t size);

	void registerObject(Collectable * object, size_t size);

private:
	void checkFreeSpace(size_t size);

private:
	MemList mAllocated;
	size_t mAllocatedSize;
	size_t mMaxHeapSize;
	std::function<void(Collectable *)> disposer;
	GarbageCollector * mCollector;
};

//-----------------------------------------------------------------------------

template<typename T>
inline GcAwarePtr<T> CollectedHeap::alloc(size_t size)
{
	checkFreeSpace(size);
	void * memory = operator new(size);
	T * object = new (memory) T;
	return GcAwarePtr<T>(object, this, size);
}

template<typename T>
inline GcAwarePtr<T> CollectedHeap::alloc(std::function<T*(void*)> constructor, size_t size)
{
	checkFreeSpace(size);
	void * memory = operator new(size);
	T * object = constructor(memory);
	return GcAwarePtr<T>(object, this, size);
}

//-----------------------------------------------------------------------------

template<typename T> GcAwarePtr<T>::~GcAwarePtr()
{
	mHeap->registerObject(mPtr, mSize);
}


}}