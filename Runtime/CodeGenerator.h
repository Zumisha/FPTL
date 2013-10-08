// CodeGenerator.h - JIT-генерация кода по функциональной схеме.

#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "FSchemeVisitor.h"
#include "AsmJit.h"

namespace FPTL {
namespace Runtime {

class CodeGenerationVisitor : public FSchemeVisitor
{
public:
	virtual ~CodeGenerationVisitor();

	virtual void visit(const FFunctionNode * aNode);
	virtual void visit(const FConditionNode * aNode);
	virtual void visit(const FParallelNode * aNode);
	virtual void visit(const FSequentialNode * aNode);
	virtual void visit(const FScheme * aScheme);

	static void * generateCode(const class FSchemeNode * aScheme);

private:
	void createConstant();

	AsmJit::Compiler mCompiler;
};

}}

#endif