#pragma once

#include "../Functions.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace FPTL {
namespace Runtime {

struct SExecutionContext;

typedef std::shared_ptr<InternalForm> IfPtr;
//-----------------------------------------------------------------------------
class InternalForm
{
public:
	virtual ~InternalForm()
	{}

	virtual void exec(SExecutionContext & ctx) const = 0;
	virtual void zeroing(SExecutionContext & ctx) = 0;
	void cancel(SExecutionContext & ctx, IfPtr child)
	{
		ctx.exchangedNodes.push_back(child);
		child = ctx.endIfPtr;
		ctx.exchangedNodes.back()->zeroing(ctx);
	}
};
//-----------------------------------------------------------------------------
class ParFork : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	ParFork(const IfPtr & left, const IfPtr & right)
		: mLeft(left), mRight(right)
	{}

	IfPtr mLeft;
	IfPtr mRight;
};

class ParJoin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	virtual void zeroing(SExecutionContext & ctx);

	ParJoin(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqBegin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	virtual void zeroing(SExecutionContext & ctx);

	SeqBegin(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqEnd : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	virtual void zeroing(SExecutionContext & ctx);

	SeqEnd(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqAdvance : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	virtual void zeroing(SExecutionContext & ctx);

	SeqAdvance(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class CondStart : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	virtual void zeroing(SExecutionContext & ctx);

	CondStart(const IfPtr & cond, const IfPtr & thenBr, const IfPtr & elseBr)
		: mCond(cond), mThen(thenBr), mElse(elseBr)
	{}

	IfPtr mCond;
	IfPtr mThen;
	IfPtr mElse;
};

class CondChoose : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	CondChoose(const IfPtr & thenBr, const IfPtr & elseBr, const IfPtr & next)
		: mThen(thenBr), mElse(elseBr), mNext(next)
	{}

	IfPtr mThen;
	IfPtr mElse;
	IfPtr mNext;
};

class RecFn : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	RecFn(const IfPtr & next, const std::string & name)
		: mFn(nullptr),
		mNext(next),
		mName(name)
	{}

	InternalForm * mFn;
	IfPtr mNext;
	std::string mName;
};

class Ret : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	Ret()
	{}
};

class BasicFn : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	BasicFn(const IfPtr & next, const std::string & name, const std::pair<int, int> & pos, const TFunction & fn)
		: mNext(next), mName(name), mPos(pos), mFn(fn)
	{}

private:
	void callFn(SExecutionContext & ctx) const;

	IfPtr mNext;
	const std::string mName;
	std::pair<int, int> mPos;
	const TFunction mFn;
};

class GetArg : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	GetArg(const IfPtr & next, const int argNum)
		: mNext(next), mArgNum(argNum)
	{}

	IfPtr mNext;
	int mArgNum;
};

class Constant : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;

	Constant(const IfPtr & next, const DataValue & data)
		: mNext(next), mData(data)
	{}

	static void pushString(SExecutionContext & ctx, const std::string & str);

	IfPtr mNext;
	DataValue mData;
};

class EndOp : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;

	void zeroing(SExecutionContext & ctx) override;
};
//-----------------------------------------------------------------------------
class FunctionalProgram
{
	friend class Generator;

public:
	FunctionalProgram(const IfPtr & main)
		: mMain(main)
	{}

	IfPtr main() const
	{ return mMain; }

private:
	// Здесь обязателен multimap, т.к. определения одной и той же функции может встречаться
	// несколько раз с разными параметрами (для функционалов).
	std::unordered_multimap<std::string, IfPtr> mDefinitions;

	IfPtr mMain;
};

//-----------------------------------------------------------------------------

}}