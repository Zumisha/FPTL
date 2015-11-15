#pragma once

namespace FPTL { namespace Runtime {

class Collectable;
class DataValue;
class CollectedHeap;
class DataRootExplorer;

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

class GarbageCollector
{
public:
	virtual void runGc(CollectedHeap * heap) = 0;

	virtual void safePoint() = 0;

	virtual void registerHeap(CollectedHeap * heap) = 0;

	virtual ~GarbageCollector() = 0
	{}

	static GarbageCollector * getCollector(int numThreads, DataRootExplorer * rootExplorer);
};

class DataRootExplorer
{
public:
	virtual void markRoots(ObjectMarker * marker) = 0;
};

}}