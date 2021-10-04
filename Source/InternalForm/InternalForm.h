﻿#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <utility>

#include "Libraries/FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{

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

			explicit ParJoin(IfPtr next) : mNext(std::move(next)) {}

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

			RecFn(IfPtr next, std::string name) :
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

		protected:
			void virtual callFn(SExecutionContext & ctx) const;

			IfPtr mNext;
			const std::string mName;
			std::pair<size_t, size_t> mPos;
			const TFunction mFn;
		};

		class UnsafeBasicFn : public BasicFn
		{
		public:
			UnsafeBasicFn(const IfPtr& next, const std::string& name, const std::pair<size_t, size_t>& pos, const TFunction& fn)
			: BasicFn(next, name, pos, fn) {}

		protected:
			void callFn(SExecutionContext & ctx) const override;
		};

		class TraceErrBasicFn : public BasicFn
		{
		public:
			TraceErrBasicFn(const IfPtr& next, const std::string& name, const std::pair<size_t, size_t>& pos, const TFunction& fn)
				: BasicFn(next, name, pos, fn) {}

		protected:
			void callFn(SExecutionContext & ctx) const override;
		};

		class GetArg : public InternalForm
		{
		public:
			void exec(SExecutionContext & ctx) const override;
			void zeroing(SExecutionContext & ctx) override;

			GetArg(IfPtr next, const int64_t from, const int64_t to, std::pair<size_t, size_t> pos)
				: mNext(std::move(next)), mFrom(from), mTo(to), mPos(std::move(pos))
			{}
		protected:
			void virtual TryGetArg(SExecutionContext& ctx, const size_t from, const size_t to) const;

			IfPtr mNext;
			int64_t mFrom;
			int64_t mTo;
			std::pair<size_t, size_t> mPos;
		};

		class UnsafeGetArg : public GetArg
		{
		public:
			UnsafeGetArg(const IfPtr& next, const int64_t from, const int64_t to, const std::pair<size_t, size_t>& pos)
				: GetArg(next, from, to, pos) {}

		protected:
			void TryGetArg(SExecutionContext & ctx, const size_t from, const size_t to) const override;
		};

		class TraceErrGetArg : public GetArg
		{
		public:
			TraceErrGetArg(const IfPtr& next, const int64_t from, const int64_t to, const std::pair<size_t, size_t>& pos)
				: GetArg(next, from, to, pos) {}

		protected:
			void TryGetArg(SExecutionContext & ctx, const size_t from, const size_t to) const override;
		};

		class Constant : public InternalForm
		{
		public:
			void exec(SExecutionContext & ctx) const override;
			void zeroing(SExecutionContext & ctx) override;
			Constant(IfPtr next, const DataValue & data) : mNext(std::move(next)), mData(data) {}
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
			explicit FunctionalProgram(IfPtr main) : mMain(std::move(main)) {}
			IfPtr main() const { return mMain; }

		private:
			// Здесь обязателен multimap, т.к. определения одной и той же функции может встречаться
			// несколько раз с разными параметрами (для функционалов).
			std::unordered_multimap<std::string, IfPtr> mDefinitions;
			IfPtr mMain;
		};
	}
}
