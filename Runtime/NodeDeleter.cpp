#include "NodeDeleter.h"
#include "FScheme.h"

namespace FPTL {
namespace Runtime {

void NodeDeleter::process(const FSchemeNode * node)
{
	node->accept(this);
}

void NodeDeleter::visit(const FFunctionNode * node)
{
	visited.insert(node);
}

void NodeDeleter::visit(const FParallelNode * node)
{
	visited.insert(node);

	process(node->left());
	process(node->right());
}

void NodeDeleter::visit(const FSequentialNode * node)
{
	visited.insert(node);

	process(node->first());
	process(node->second());
}

void NodeDeleter::visit(const FConditionNode * node)
{
	visited.insert(node);

	process(node->condition());
	process(node->trueBranch());
	process(node->falseBranch());
}

void NodeDeleter::visit(const FScheme * scheme)
{
	if (visited.insert(scheme).second)
	{
		process(scheme->firstNode());
	}
}

void NodeDeleter::visit(const FTakeNode * node)
{
	visited.insert(node);
}

void NodeDeleter::visit(const FConstantNode * node)
{
	visited.insert(node);
}

void NodeDeleter::releaseGraph(const FSchemeNode * node)
{
	visited.clear();

	if (node)
	{
		process(node);
	}

	for (auto elem : visited)
	{
		delete elem;
	}
}

}}