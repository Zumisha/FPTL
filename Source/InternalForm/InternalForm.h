#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <utility>

#include "Libraries/FunctionLibrary.h"
#include "DataTypes/Values/Value.h"
#include "Evaluator/Context.h"

namespace FPTL {
namespace Runtime {

typedef std::shared_ptr<InternalForm> IfPtr;
//-----------------------------------------------------------------------------
class InternalForm
{
public:
	virtual ~InternalForm() = default;

	virtual void exec(SExecutionContext & ctx) const = 0;
	virtual void zeroing(SExecutionContext & ctx) = 0;

	static void cancel(SExecutionContext & ctx, IfPtr child)
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

	ParFork(IfPtr left, IfPtr right) : mLeft(std::move(left)), mRight(std::move(right)) {}

	IfPtr mLeft;
	IfPtr mRight;
};

class ParJoin : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	explicit ParJoin(IfPtr next)	: mNext(std::move(next)) {}

	IfPtr mNext;
};

class SeqBegin : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	explicit SeqBegin(IfPtr next) : mNext(std::move(next)) {}

	IfPtr mNext;
};

class SeqEnd : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	explicit SeqEnd(IfPtr next) : mNext(std::move(next)) {}

	IfPtr mNext;
};

class SeqAdvance : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	explicit SeqAdvance(IfPtr next) : mNext(std::move(next)) {}

	IfPtr mNext;
};

class CondStart : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	CondStart(IfPtr cond, IfPtr thenBr, IfPtr elseBr) : 
		mCond(std::move(cond)), 
		mThen(std::move(thenBr)), 
		mElse(std::move(elseBr)) 
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

	CondChoose(IfPtr thenBr, IfPtr elseBr, IfPtr next) : 
		mThen(std::move(thenBr)), 
		mElse(std::move(elseBr)), 
		mNext(std::move(next))
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

	RecFn(IfPtr next, std::string name)	: 
		mFn(nullptr),
		mNext(std::move(next)),
		mName(std::move(name))
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

	Ret() = default;
};

class BasicFn : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	BasicFn(IfPtr next, std::string name, std::pair<size_t, size_t> pos, TFunction fn) : 
		mNext(std::move(next)), 
		mName(std::move(name)), 
		mPos(std::move(pos)), 
		mFn(std::move(fn))
	{}

private:
	void callFn(SExecutionContext & ctx) const;

	IfPtr mNext;
	const std::string mName;
	std::pair<size_t, size_t> mPos;
	const TFunction mFn;
};

class GetArg : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;

	GetArg(IfPtr next, const long long argNum, std::pair<size_t, size_t> pos)
		: mNext(std::move(next)), mArgNum(argNum), mPos(std::move(pos))
	{}
private:
	const Value& TryGetArg(const SExecutionContext& ctx, size_t argNum) const;

	IfPtr mNext;
	long long mArgNum;
	std::pair<size_t, size_t> mPos;
};

class Constant : public InternalForm
{
public:
	void exec(SExecutionContext & ctx) const override;
	void zeroing(SExecutionContext & ctx) override;
	Constant(IfPtr next, Value data) : mNext(std::move(next)), mData(std::move(data)) {}

	IfPtr mNext;
	Value mData;
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
	explicit FunctionalProgram(IfPtr main) : mMain(std::move(main)) {}
	IfPtr main() const { return mMain; }

private:
	// Здесь обязателен multimap, т.к. определения одной и той же функции может встречаться
	// несколько раз с разными параметрами (для функционалов).
	std::unordered_multimap<std::string, IfPtr> mDefinitions;
	IfPtr mMain;
};

//-----------------------------------------------------------------------------

}}
