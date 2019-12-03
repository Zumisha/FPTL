#pragma once

#include <unordered_map>
#include <iterator>
#include <algorithm>

#include "FScheme/FSchemeVisitor.h"
#include "InternalForm.h"

namespace FPTL {
namespace Runtime {

class InternalForm;
class FunctionalProgram;

class GeneratorContext
{
	std::unordered_map<const FScheme *, IfPtr> mFunctions;
	std::unordered_map<RecFn *, const FScheme *> mCalls;

public:
	GeneratorContext() = default;

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

	void getFunctions(std::unordered_multimap<std::string, IfPtr> & functions)
	{
		std::transform(mFunctions.begin(), mFunctions.end(), std::inserter(functions, functions.end()),
			[](auto entry) { return std::make_pair(entry.first->name(), entry.second); });
	}
};

class Generator : public FSchemeVisitor
{
public:
	Generator() = default;

	void visit(const FFunctionNode * node) override;
	void visit(const FParallelNode * node) override;
	void visit(const FSequentialNode * node) override;
	void visit(const FConditionNode * node) override;
	void visit(const FScheme * scheme) override;
	void visit(const FTakeNode * node) override;
	void visit(const FConstantNode * node) override;

	static FunctionalProgram * generate(FSchemeNode * node, const bool Proactive);

private:
	IfPtr createSpan(FSchemeNode * node, const IfPtr & tail);

	GeneratorContext mCtx;

	IfPtr mTail;
	IfPtr mResult;

	bool Proactive;
};

}}
