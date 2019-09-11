#pragma once

#include <unordered_set>

#include "FSchemeVisitor.h"

namespace FPTL {
namespace Runtime {

class NodeDeleter : public FSchemeVisitor
{
public:
	void visit(const FFunctionNode * aNode) override;
	void visit(const FParallelNode * aNode) override;
	void visit(const FSequentialNode * aNode) override;
	void visit(const FConditionNode * aNode) override;
	void visit(const FScheme * aScheme) override;
	void visit(const FTakeNode * aNode) override;
	void visit(const FConstantNode * aNode) override;

	void releaseGraph(const FSchemeNode * node);

private:
	void process(const FSchemeNode * node);

	std::unordered_set<const FSchemeNode*> visited;
};

}}