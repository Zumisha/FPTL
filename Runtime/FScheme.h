// FScheme.h - описание функциональной схемы.

#ifndef FSCHEME_H
#define FSCHEME_H

#include <iostream>
#include <sstream>
#include <set>

#include "Functions.h"
#include "Context.h"

namespace FPTL {
namespace Runtime {

class FSchemeNode;
class FSchemeVisitor;
struct SExecutionContext;

//---------------------------------------------------------------------------------------------
// Абстрактный узел функциональный схемы.
class FSchemeNode //: public gc
{
public:

	FSchemeNode(bool aIsLong);
	virtual ~FSchemeNode() {}

	virtual void execute(SExecutionContext & aCtx) const = 0;

	virtual void accept(FSchemeVisitor * aVisitor) const = 0;

	bool isLong() const { return mIsLong; }

	typedef void (*TCompiledProc)(SExecutionContext * aCtx);

private:
	/// Создает заглушку, которая запускает JIT-компилятор, если код для узла не был сгенерирован.
	TCompiledProc createJITStub();

private:
	bool mIsLong;

public:
	/// Скомпилированная в рантайме версия execute.
	TCompiledProc mCompiledProc;
};

//---------------------------------------------------------------------------------------------
class FParallelNode : public FSchemeNode
{
public:

	FParallelNode(FSchemeNode * aLeft, FSchemeNode * aRight);

	virtual void execute(SExecutionContext & aCtx) const;

	virtual void accept(FSchemeVisitor * aVisitor) const;

	FSchemeNode * left() const { return mLeft; }
	FSchemeNode * right() const { return mRight; }

private:

	// Дочерние элементы блока, могут выполняться параллельно.
	FSchemeNode * mLeft;
	FSchemeNode * mRight;
};

//---------------------------------------------------------------------------------------------
// Узел, инкапсулирующий вызов встроенной функции или схемы.
class FFunctionNode : public FSchemeNode
{
public:

	template <typename F>
	FFunctionNode(const F & aFunction) : FSchemeNode(false), mFunction(aFunction)
	{}

	template <typename F>
	FFunctionNode(const F & aFunction, const std::string & aName, short aLine, short aCol)
		: FSchemeNode(false),
		  mFunction(aFunction),
		  mName(aName.c_str()),
		  mColumn(aCol),
		  mLine(aLine)
	{}

	virtual void execute(SExecutionContext & aCtx) const;

	virtual void accept(FSchemeVisitor * aVisitor) const;

	static void call(const FFunctionNode * aNode, SExecutionContext * aCtx);

private:

	std::function<void(SExecutionContext &)> mFunction;

	// Имя функции и позиция в тексте программы.
	std::basic_string<char>  mName;
	short mLine;
	short mColumn;
};

//---------------------------------------------------------------------------------------------
class FSequentialNode : public FSchemeNode
{
public:

	FSequentialNode(FSchemeNode * aFirst, FSchemeNode * aSecond);

	virtual void execute(SExecutionContext & aCtx) const;

	virtual void accept(FSchemeVisitor * aVisitor) const;

	FSchemeNode * first() const { return mFirst; }
	FSchemeNode * second() const { return mSecond; }

private:

	FSchemeNode * mFirst;
	FSchemeNode * mSecond;
};

//---------------------------------------------------------------------------------------------
class FConditionNode : public FSchemeNode
{
public:

	FConditionNode(FSchemeNode * aCondition, FSchemeNode * aTrueBranch, FSchemeNode * aFalseBranch);

	virtual void execute(SExecutionContext & aCtx) const;

	virtual void accept(FSchemeVisitor * aVisitor) const;

	FSchemeNode * condition() const { return mCondition; }
	FSchemeNode * trueBranch() const { return mTrueBranch; }
	FSchemeNode * falseBranch() const { return mFalseBranch; }

private:

	FSchemeNode * mCondition;
	FSchemeNode * mTrueBranch;
	FSchemeNode * mFalseBranch;
};

//---------------------------------------------------------------------------------------------
// Функциональная схема.
class FScheme : public FSchemeNode
{
public:

	FScheme(FSchemeNode * aFirstNode);

	virtual void execute(SExecutionContext & aCtx) const;

	virtual void accept(FSchemeVisitor * aVisitor) const;

	void setFirstNode(FSchemeNode * aFirstNode) { mFirstNode = aFirstNode; }

	FSchemeNode * firstNode() const { return mFirstNode; }

private:

	FSchemeNode * mFirstNode;
};

} // Runtime
} // FPTL

#endif