#pragma once

#include <boost/intrusive/slist.hpp>

#include "Context.h"
#include "GcAwarePtr.h"

namespace FPTL {
namespace Runtime {

class GarbageCollector;

//-------------------------------------------------------------------------------

// Интерфейс объектов с автоматическим управлением памятью.
// Все наследника этого класса обязаны иметь тривиальный деструктор.
class Collectable : public boost::intrusive::slist_base_hook<>
{
	friend class CollectedHeap;
	friend class ObjectMarker;

public:
	enum Age
	{
		YOUNG = 0,
		OLD = 1
	};

private:
	struct MetaInfo
	{
		Age age : 30;
		unsigned int marked : 2;
	};

	MetaInfo meta;

public:
	Collectable()
		: meta({ YOUNG, 0 })
	{}

	bool isMarked() const
	{
		return meta.marked == 1;
	}
};

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
