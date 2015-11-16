#pragma once

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

	virtual ~ObjectMarker() = 0
	{}

	static void setObjectAge(Collectable * object, int age);
	static bool checkAge(const Collectable * object, int age);
};

//-----------------------------------------------------------------------------
class GcConfig
{
	static const int DEFAULT_YOUNG_GEN_SIZE = 20 * 1024 * 1024;

public:
	GcConfig() :
		mEnabled(true),
		mYoungGenSize(DEFAULT_YOUNG_GEN_SIZE),
		mVerbose(false)
	{}

	void setEnabled(bool state)
	{ mEnabled = state; }

	void setYoungGenSize(size_t size)
	{ mYoungGenSize = size; }

	void setVerbose(bool enabled)
	{ mVerbose = enabled; }

	bool enabled() const
	{ return mEnabled; }

	size_t youngGenSize() const
	{ return mYoungGenSize; }

	bool verbose() const
	{ return mVerbose; }

private:
	size_t mYoungGenSize;
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

	virtual ~GarbageCollector() = 0
	{}

	static GarbageCollector * getCollector(int numMutatorThreads, DataRootExplorer * rootExplorer, const GcConfig & config);
};

//-----------------------------------------------------------------------------
class DataRootExplorer
{
public:
	virtual void markRoots(ObjectMarker * marker) = 0;
};

//-----------------------------------------------------------------------------

}}