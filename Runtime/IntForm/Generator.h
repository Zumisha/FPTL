#pragma once

#include "../FSchemeVisitor.h"

#include <tuple>
#include <map>
#include <unordered_map>

namespace FPTL {
namespace Runtime {

class InternalForm;
class GeneratorContext;

class GeneratorContext
{
	std::unordered_map<const FScheme *, const InternalForm *> mFunctions;

public:
	GeneratorContext()
	{}

	bool declareFun(const FScheme * scheme)
	{
		return mFunctions.insert({ scheme, nullptr }).second;
	}

	void defineFun(const FScheme * scheme, const InternalForm * body)
	{
		mFunctions[scheme] = body;
	}

	const InternalForm * getFun(const FScheme * scheme)
	{
		return mFunctions.at(scheme);
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

	static InternalForm * generate(FSchemeNode * node);

private:
	InternalForm * createSpan(FSchemeNode * node, InternalForm * mTail);

private:
	GeneratorContext mCtx;

	InternalForm * mTail;
	InternalForm * mResult;
};

}}
