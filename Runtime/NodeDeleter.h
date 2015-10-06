#pragma once

#include <unordered_set>

#include "FSchemeVisitor.h"

namespace FPTL {
namespace Runtime {

class NodeDeleter : public FSchemeVisitor
{
public:
	virtual void visit(const FFunctionNode * aNode);
	virtual void visit(const FParallelNode * aNode);
	virtual void visit(const FSequentialNode * aNode);
	virtual void visit(const FConditionNode * aNode);
	virtual void visit(const FScheme * aScheme);
	virtual void visit(const FTakeNode * aNode);
	virtual void visit(const FConstantNode * aNode);

	void releaseGraph(const FSchemeNode * node);

private:
	void process(const FSchemeNode * node);

	std::unordered_set<const FSchemeNode*> visited;
};

}}