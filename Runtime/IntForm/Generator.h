#pragma once

#include "../FSchemeVisitor.h"
#include "InternalForm.h"

#include <unordered_map>
#include <iterator>
#include <algorithm>

namespace FPTL {
namespace Runtime {

class InternalForm;
class FunctionalProgram;

class GeneratorContext
{
	std::unordered_map<const FScheme *, IfPtr> mFunctions;
	std::unordered_map<RecFn *, const FScheme *> mCalls;

public:
	GeneratorContext()
	{}

	bool declareFun(const FScheme * scheme)
	{
		return mFunctions.insert({ scheme, IfPtr() }).second;
	}

	void defineFun(const FScheme * scheme, const IfPtr & body)
	{
		mFunctions[scheme] = body;
	}

	std::shared_ptr<const InternalForm> getFun(const FScheme * scheme)
	{
		return mFunctions.at(scheme);
	}

	void addRec(const FScheme * scheme, RecFn * fn)
	{
		mCalls[fn] = scheme;
	}

	void resolveRec()
	{
		for (auto rec : mCalls)
		{
			rec.first->mFn = mFunctions.at(rec.second).get();
		}
	}

	void getFunctions(std::unordered_map<std::string, IfPtr> & functions)
	{
		std::transform(mFunctions.begin(), mFunctions.end(), std::inserter(functions, functions.end()),
			[](auto entry) { return std::make_pair(entry.first->name(), entry.second); });
	}
};

class Generator : public FSchemeVisitor
{
public:
	Generator();

	virtual void visit(const FFunctionNode * aNode);
	virtual void visit(const FParallelNode * aNode);
	virtual void visit(const FSequentialNode * aNode);
	virtual void visit(const FConditionNode * aNode);
	virtual void visit(const FScheme * aScheme);
	virtual void visit(const FTakeNode * aNode);
	virtual void visit(const FConstantNode * aNode);

	static FunctionalProgram * generate(FSchemeNode * node);

private:
	IfPtr createSpan(FSchemeNode * node, const IfPtr & mTail);

private:
	GeneratorContext mCtx;

	IfPtr mTail;
	IfPtr mResult;
};

}}
