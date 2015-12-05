#pragma once

#include <string>

namespace FPTL {
namespace Runtime {

struct SExecutionContext;

class InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) = 0;
};

class ParFork : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	ParFork(const InternalForm * left, const InternalForm * right)
		: mLeft(left), mRight(right)
	{}

	const InternalForm * mLeft;
	const InternalForm * mRight;
};

class ParJoin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	ParJoin(const InternalForm * next)
		: mNext(next)
	{}

	const InternalForm * mNext;
};

class SeqBegin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	SeqBegin(const InternalForm * next)
		: mNext(next)
	{}

	const InternalForm * mNext;
};

class SeqEnd : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	SeqEnd(const InternalForm * next)
		: mNext(next)
	{}

	const InternalForm * mNext;
};

class SeqAdvance : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	SeqAdvance(const InternalForm * next)
		: mNext(next)
	{}

	const InternalForm * mNext;
};

class CondStart : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	CondStart(const InternalForm * cond)
		: mCond(cond)
	{}

	const InternalForm * mCond;
};

class CondChoose : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	CondChoose(const InternalForm * thenBr, const InternalForm * elseBr)
		: mThen(thenBr), mElse(elseBr)
	{}

	const InternalForm * mThen;
	const InternalForm * mElse;
};

class RecFn : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	RecFn(const InternalForm * fn, const InternalForm * next, const std::string & name)
		: mFn(fn),
		mNext(next),
		mName(name)
	{}

	const InternalForm * mFn;
	const InternalForm * mNext;
	std::string mName;
};

class Ret : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	Ret()
	{}
};

class BasicFn : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);

	BasicFn(const InternalForm * next, const std::string & name)
		: mNext(next), mName(name)
	{}

	const InternalForm * mNext;
	const std::string mName;
};

class EndOp : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx);
};

}}
