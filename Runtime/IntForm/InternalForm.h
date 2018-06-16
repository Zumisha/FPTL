#pragma once

#include "../Functions.h"

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace FPTL {
namespace Runtime {

struct SExecutionContext;

//-----------------------------------------------------------------------------
class InternalForm
{
public:
	virtual ~InternalForm()
	{}

	virtual void exec(SExecutionContext & ctx) const = 0;
};

typedef std::shared_ptr<const InternalForm> IfPtr;

//-----------------------------------------------------------------------------
class ParFork : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

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

	ParJoin(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqBegin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	SeqBegin(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqEnd : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	SeqEnd(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class SeqAdvance : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	SeqAdvance(const IfPtr & next)
		: mNext(next)
	{}

	IfPtr mNext;
};

class CondStart : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	CondStart(const IfPtr & cond)
		: mCond(cond)
	{}

	IfPtr mCond;
};

class CondChoose : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	CondChoose(const IfPtr & thenBr, const IfPtr & elseBr)
		: mThen(thenBr), mElse(elseBr)
	{}

	IfPtr mThen;
	IfPtr mElse;
};

class CondFork : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	CondFork(const IfPtr & cond, const IfPtr & thenBr, const IfPtr & elseBr)
		: mCond(cond), mThen(thenBr), mElse(elseBr)
	{}

	IfPtr mCond;
	IfPtr mThen;
	IfPtr mElse;
};

class CondJoin : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;
	CondJoin(const IfPtr & Branch)
		: mNext(Branch)
	{}

	IfPtr mCond;
	IfPtr mNext;
};

class RecFn : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	RecFn(const IfPtr & next, const std::string & name)
		: mFn(nullptr),
		mNext(next),
		mName(name)
	{}

	const InternalForm * mFn;
	IfPtr mNext;
	std::string mName;
};

class Ret : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

	Ret()
	{}
};

class BasicFn : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

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
	virtual void exec(SExecutionContext & ctx) const;

	GetArg(const IfPtr & next, int argNum)
		: mNext(next), mArgNum(argNum)
	{}

	IfPtr mNext;
	const int mArgNum;
};

class Constant : public InternalForm
{
public:
	virtual void exec(SExecutionContext & ctx) const;

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
	virtual void exec(SExecutionContext & ctx) const;
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
