// Класс для организации обхода стуктурированной функциональной схемы.

#ifndef FSCHEMEVISITOR_H
#define FSCHEMEVISITOR_H

namespace FPTL {
namespace Runtime {

class FSchemeNode;
class FFunctionNode;
class FParallelNode;
class FSequentialNode;
class FConditionNode;
class FScheme;

class FSchemeVisitor
{
public:
	virtual void visit(const FFunctionNode * aNode) = 0;
	virtual void visit(const FParallelNode * aNode) = 0;
	virtual void visit(const FSequentialNode * aNode) = 0;
	virtual void visit(const FConditionNode * aNode) = 0;
	virtual void visit(const FScheme * aScheme) = 0;

	virtual ~FSchemeVisitor() {};
};

}}

#endif