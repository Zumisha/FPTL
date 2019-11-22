#pragma once

#include <stddef.h> //size_t

namespace FPTL { namespace Runtime {

class Collectable;
class DataValue;
class CollectedHeap;
class DataRootExplorer;

//-----------------------------------------------------------------------------
class ObjectMarker
{
public:
	virtual bool markAlive(Collectable * object, size_t size) = 0;

	virtual void addChild(const DataValue * child) = 0;

	virtual ~ObjectMarker() = 0;

	static void setObjectAge(Collectable * object, int age);
	static bool checkAge(const Collectable * object, int age);
	static void setMarked(Collectable * object, unsigned int flag);
};

//-----------------------------------------------------------------------------
class GcConfig
{
	static const int DEFAULT_YOUNG_GEN_SIZE = 20 * 1024 * 1024;

public:
	GcConfig() :
		mYoungGenSize(DEFAULT_YOUNG_GEN_SIZE),
		mOldGenSize(5 * DEFAULT_YOUNG_GEN_SIZE),
		mOldGenThreshold(mOldGenSize * static_cast<size_t>(0.75)),
		mEnabled(true),
		mVerbose(false)
	{}

	void setEnabled(bool state)
	{ mEnabled = state; }

	void setYoungGenSize(size_t size)
	{ mYoungGenSize = size; }

	void setVerbose(bool enabled)
	{ mVerbose = enabled; }

	void setOldGenSize(size_t size)
	{ mOldGenSize = size; }

	bool enabled() const
	{ return mEnabled; }

	size_t youngGenSize() const
	{ return mYoungGenSize; }

	size_t oldGenSize() const
	{ return mOldGenSize; }

	bool verbose() const
	{ return mVerbose; }

	void setOldGenThreshold(double ratio)
	{ mOldGenThreshold = mOldGenSize * static_cast<size_t>(ratio); }

	size_t oldGenGCThreshold() const
	{ return mOldGenThreshold; }

private:
	size_t mYoungGenSize;
	size_t mOldGenSize;
	size_t mOldGenThreshold;
	bool mEnabled;
	bool mVerbose;
};

//-----------------------------------------------------------------------------
class GarbageCollector
{
public:
	virtual void runGc() = 0;

	virtual void safePoint() = 0;

	virtual void registerHeap(CollectedHeap * heap) = 0;

	virtual ~GarbageCollector() = default;

	static GarbageCollector * getCollector(size_t numMutatorThreads, DataRootExplorer * rootExplorer, const GcConfig & config);
};

//-----------------------------------------------------------------------------
class DataRootExplorer
{
public:
	virtual ~DataRootExplorer() = default;
	virtual void markRoots(ObjectMarker * marker) = 0;
};

//-----------------------------------------------------------------------------

}}
