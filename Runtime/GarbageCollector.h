#pragma once

namespace FPTL { namespace Runtime {

class Collectable;
class DataValue;
class CollectedHeap;
class DataRootExplorer;

class GarbageCollector
{
public:
	virtual void markAlive(Collectable * object, size_t size) = 0;

	virtual void addChild(const DataValue * child) = 0;

	virtual void runGc(CollectedHeap * heap) = 0;

	virtual void runIfNeed(CollectedHeap * heap) = 0;

	virtual void safePoint() = 0;

	static GarbageCollector * getCollector(int numThreads, DataRootExplorer * rootExplorer);
};

class DataRootExplorer
{
public:
	virtual void markRoots(GarbageCollector * collector) = 0;
};

}}