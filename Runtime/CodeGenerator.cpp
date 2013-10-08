#include <cstddef>

#include "CodeGenerator.h"
#include "FScheme.h"

namespace FPTL {
namespace Runtime {

CodeGenerationVisitor::~CodeGenerationVisitor()
{
}

void CodeGenerationVisitor::visit(const FFunctionNode * aNode)
{
	// Генерируем вызов функции.
	AsmJit::GPVar node(mCompiler.newGP());
	mCompiler.mov(node, (sysint_t)aNode);

	AsmJit::ECall * context = mCompiler.call(&FFunctionNode::call);
	context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder2<AsmJit::Void, FFunctionNode *, SExecutionContext *>());
	context->setArgument(0, node);
	context->setArgument(1, mCompiler.argGP(0));
}

void CodeGenerationVisitor::visit(const FParallelNode * aNode)
{
	const sysint_t dataOffset = offsetof(SExecutionContext, Data);

	if (aNode->left()->isLong() && aNode->right()->isLong())
	{
		// Порождаем левую подзадачу.
		AsmJit::GPVar leftResultVar(mCompiler.newGP());
		mCompiler.mov(leftResultVar, AsmJit::Imm(0));

		{
			AsmJit::GPVar scheme(mCompiler.newGP());
			mCompiler.mov(scheme, AsmJit::Imm((sysint_t)aNode->left()));

			AsmJit::GPVar resultAddress(mCompiler.newGP());
			mCompiler.spill(leftResultVar);
			mCompiler.lea(resultAddress, leftResultVar.m());

			AsmJit::GPVar fork(mCompiler.newGP());

			auto context = mCompiler.call(&SExecutionContext::doFork);
			context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder3<SExecutionContext *, SExecutionContext *, FSchemeNode *, DataElement * volatile *>());
			context->setArgument(0, mCompiler.argGP(0));
			context->setArgument(1, scheme);
			context->setArgument(2, resultAddress);
			context->setReturn(fork);
		}

		// Порождаем правую подзадачу.
		AsmJit::GPVar rightResultVar(mCompiler.newGP());
		mCompiler.mov(rightResultVar, AsmJit::Imm(0));

		{
			AsmJit::GPVar scheme(mCompiler.newGP());
			mCompiler.mov(scheme, AsmJit::Imm((sysint_t)aNode->right()));

			AsmJit::GPVar resultAddress(mCompiler.newGP());
			mCompiler.spill(rightResultVar);
			mCompiler.lea(resultAddress, rightResultVar.m());

			AsmJit::GPVar fork(mCompiler.newGP());

			auto context = mCompiler.call(&SExecutionContext::doFork);
			context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder3<SExecutionContext *, SExecutionContext *, FSchemeNode *, DataElement * volatile *>());
			context->setArgument(0, mCompiler.argGP(0));
			context->setArgument(1, scheme);
			context->setArgument(2, resultAddress);
			context->setReturn(fork);
		}

		// Создаем цикл ожидания результата.
		AsmJit::Label repeat = mCompiler.newLabel();
		AsmJit::Label exitLoop = mCompiler.newLabel();
		AsmJit::Label loop = mCompiler.newLabel();

		mCompiler.bind(repeat);
		mCompiler.cmp(leftResultVar, AsmJit::Imm(0));
		mCompiler.je(loop);
		mCompiler.cmp(rightResultVar, AsmJit::Imm(0));
		mCompiler.jne(exitLoop);

		mCompiler.bind(loop);

		// Вызываем yield.
		auto context = mCompiler.call(&SExecutionContext::doYield);
		context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<AsmJit::Void, SExecutionContext *>());
		context->setArgument(0, mCompiler.argGP(0));

		mCompiler.jmp(repeat);

		mCompiler.bind(exitLoop);

		// Cклеиваем результат.
		AsmJit::GPVar right(mCompiler.newGP());
		mCompiler.mov(right, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));

		AsmJit::GPVar output(mCompiler.newGP());

		context = mCompiler.call(&DataElement::concat);
		context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder2<DataElement *, DataElement *, DataElement *>());
		context->setArgument(0, leftResultVar);
		context->setArgument(1, rightResultVar);
		context->setReturn(output);

		mCompiler.mov(AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset), output);
	}
	else
	{
		AsmJit::GPVar input(mCompiler.newGP());
		mCompiler.mov(input, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));

		// Вычисляем левый операнд.
		aNode->left()->accept(this);

		AsmJit::GPVar left(mCompiler.newGP());
		mCompiler.mov(left, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));
		mCompiler.mov(AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset), input);

		// Вычисляем правый операнд.
		aNode->right()->accept(this);

		AsmJit::GPVar right(mCompiler.newGP());
		mCompiler.mov(right, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));

		// Склеиваем результат.
		AsmJit::ECall * context = mCompiler.call(&DataElement::concat);
		context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder2<DataElement *, DataElement *, DataElement *>());
		context->setArgument(0, left);
		context->setArgument(1, right);
		context->setReturn(input);

		mCompiler.mov(AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset), input);
	}
}

void CodeGenerationVisitor::visit(const FSequentialNode * aNode)
{
	aNode->first()->accept(this);

	aNode->second()->accept(this);
}

void CodeGenerationVisitor::visit(const FConditionNode * aNode)
{
	const sysint_t dataOffset = offsetof(SExecutionContext, Data);

	// Запоминаем входные данные.
	AsmJit::GPVar input(mCompiler.newGP());
	mCompiler.mov(input, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));

	// Генерируем код, вычисляющий условние.
	aNode->condition()->accept(this);

	// Получаем указатель на вычисленный результат.
	AsmJit::GPVar cond(mCompiler.newGP());
	mCompiler.mov(cond, AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset));

	// Восстанавляем указатель на входные данные.
	mCompiler.mov(AsmJit::sysint_ptr(mCompiler.argGP(0), dataOffset), input);

	AsmJit::Label falseBranch = mCompiler.newLabel();

	AsmJit::Imm undefinedConst((sysint_t)UndefinedValue::instance());
	mCompiler.cmp(cond, undefinedConst);

	mCompiler.je(falseBranch);

	AsmJit::Imm falseConst((sysint_t)BooleanData::getFalse());
	mCompiler.cmp(cond, falseConst);

	mCompiler.je(falseBranch);

	// Генерируем then-ветку.
	aNode->trueBranch()->accept(this);

	AsmJit::Label end = mCompiler.newLabel();
	mCompiler.jmp(end);

	mCompiler.bind(falseBranch);

	// Генерируем else-ветку.
	aNode->falseBranch()->accept(this);

	mCompiler.bind(end);
}

void CodeGenerationVisitor::visit(const FScheme * aScheme)
{
	// Генерируем вызов функции, производящей выполнение кода схемы.
	AsmJit::GPVar address(mCompiler.newGP());
	mCompiler.mov(address, AsmJit::Imm((sysint_t)aScheme->firstNode()));

	AsmJit::ECall * context = mCompiler.call(AsmJit::sysint_ptr(address, offsetof(FSchemeNode, mCompiledProc)));
	context->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<AsmJit::Void, SExecutionContext *>());
	context->setArgument(0, mCompiler.argGP(0));
}

void * CodeGenerationVisitor::generateCode(const FSchemeNode * aSchemeNode)
{
	CodeGenerationVisitor generator;

	generator.mCompiler.newFunction(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<AsmJit::Void, SExecutionContext *>());

	// Генерируем код схемы.
	aSchemeNode->accept(&generator);

	generator.mCompiler.endFunction();

	return generator.mCompiler.make();
}

//-----------------------------------------------------------------------------
FSchemeNode::TCompiledProc FSchemeNode::createJITStub()
{
	AsmJit::Compiler compiler;

	compiler.newFunction(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<AsmJit::Void, SExecutionContext *>());

	// Кэшируем this.
	AsmJit::GPVar node(compiler.newGP());
	compiler.mov(node, AsmJit::Imm((sysint_t)this));

	// Компилируем код.
	AsmJit::GPVar proc(compiler.newGP());

	CodeGenerationVisitor generator;

	AsmJit::ECall * generate = compiler.call(&CodeGenerationVisitor::generateCode);
	generate->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<void *, FSchemeNode *>());
	generate->setArgument(0, node);
	generate->setReturn(proc);

	// Подменяем адрес на скомпилированный код.
	compiler.mov(AsmJit::sysint_ptr(node, offsetof(FSchemeNode, mCompiledProc)), proc);

	// Запускаем его.
	AsmJit::ECall * call = compiler.call(proc);
	call->setPrototype(AsmJit::CALL_CONV_DEFAULT, AsmJit::FunctionBuilder1<AsmJit::Void, SExecutionContext *>());
	call->setArgument(0, compiler.argGP(0));

	compiler.endFunction();

	return AsmJit::function_cast<TCompiledProc>(compiler.make());
}

}}