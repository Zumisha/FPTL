#pragma once

#include "CollectedHeap.h"

namespace FPTL {
namespace Runtime {

class CollectedHeap;

template <typename T> class GcAwarePtr
{
public:
	GcAwarePtr(T * ptr, CollectedHeap * heap, size_t size)
		: mPtr(ptr),
		mHeap(heap),
		mSize(size)
	{}

	GcAwarePtr operator=(const GcAwarePtr &) = delete;

	~GcAwarePtr();

	T * operator ->()
	{
		return mPtr;
	}

	T & operator *()
	{
		return *mPtr;
	}

	T * ptr()
	{
		return mPtr;
	}


private:
	T * mPtr;
	CollectedHeap * mHeap;
	size_t mSize;
};

}}