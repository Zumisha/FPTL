#include "InternalForm.h"
#include "DataTypes/Ops/StringOps.h"
#include "Evaluator/Run.h"
#include "Evaluator/Context.h"
#include "Macros.h"
#include "Parser/Support.h"

namespace FPTL
{
	namespace Runtime
	{
		void ParFork::exec(SExecutionContext & ctx) const
		{
			const auto fork = dynamic_cast<IFExecutionContext &>(ctx).spawn(mRight.get());

			ctx.evaluator()->addForkJob(fork);

			mLeft->exec(ctx);
		}

		void ParFork::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mLeft);
		}

		void ParJoin::exec(SExecutionContext & ctx) const
		{
			ctx.join();
			mNext->exec(ctx);
		}

		void ParJoin::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void SeqBegin::exec(SExecutionContext & ctx) const
		{
			// Запоминаем предыдущие параметры.
			ctx.controlStack.emplace_back(ctx.argPos, ctx.stack.size(), ctx.argNum, ctx.arity);
			ctx.arity = 0;

			mNext->exec(ctx);
		}

		void SeqBegin::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void SeqEnd::exec(SExecutionContext & ctx) const
		{
			const auto &cv = ctx.controlStack.back();
			ctx.controlStack.pop_back();

			// Сворачиваем стек.
			ctx.unwind(cv.ArgPos, cv.OutArity, cv.Size);
			ctx.argNum = cv.InArity;

			mNext->exec(ctx);
		}

		void SeqEnd::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void SeqAdvance::exec(SExecutionContext & ctx) const
		{
			ctx.advance();

			mNext->exec(ctx);
		}

		void SeqAdvance::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void CondStart::exec(SExecutionContext & ctx) const
		{
			ctx.controlStack.emplace_back(ctx.arity);

			if (mThen)
			{
				auto fork = dynamic_cast<IFExecutionContext &>(ctx).spawn(mThen.get());
				fork->NewProactiveLevel = true;
				fork->Proactive = true;
				ctx.evaluator()->addForkJob(fork);
			}

			if (mElse)
			{
				auto fork = dynamic_cast<IFExecutionContext &>(ctx).spawn(mElse.get());
				fork->NewProactiveLevel = true;
				fork->Proactive = true;
				ctx.evaluator()->addForkJob(fork);
			}

			mCond->exec(ctx);
		}

		void CondStart::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mCond);
		}

		const DataValue falseConst = DataBuilders::createBoolean(false);
		const DataValue undefined = DataBuilders::createUndefinedValue();

		void CondChoose::exec(SExecutionContext & ctx) const
		{
			const auto arity = ctx.controlStack.back().OutArity;
			ctx.controlStack.pop_back();

			// Берём сверху стека 1 аргумент - результат вычисления предиката.
			const auto& cond = ctx.stack.back();
			bool isUndefined = false;

			const size_t numArgs = ctx.arity - arity;
			for (size_t i = 0; i < numArgs; ++i)
			{
				DataValue & arg = ctx.stack.back();

				// Проверяем, содержится ли в кортеже неопределенное значение w для реализации семантики w*a = a*w = w.
				if (arg.getOps() == undefined.getOps())
				{
					isUndefined = true;
				}

				ctx.stack.pop_back();
			}
			ctx.arity = arity;

			// Проверка условия.
			if (numArgs > 0 && (isUndefined || (cond.getOps() == falseConst.getOps() && !cond.mIntVal)))
			{
				if (!mThen) // Если ненужная ветвь длинная - отменяем её вычисление.
					ctx.evaluator()->cancelFromPendingEnd(1 + !mElse);
				if (mElse) // Если верная ветвь короткая - начинаем её вычислять.
					mElse->exec(ctx);
				else
				{
					ctx.join();
					mNext->exec(ctx);
				}
			}
			else
			{
				if (!mElse) // Если ненужная ветвь длинная - отменяем её вычисление.
					ctx.evaluator()->cancelFromPendingEnd();
				if (mThen) // Если верная ветвь короткая - начинаем её вычислять.
					mThen->exec(ctx);
				else
				{
					ctx.join();
					mNext->exec(ctx);
				}
			}
		}

		void CondChoose::zeroing(SExecutionContext & ctx)
		{
			if (mThen)
			{
				cancel(ctx, mThen);
			}
			if (mElse)
			{
				cancel(ctx, mElse);
			}
			cancel(ctx, mNext);
		}

		void RecFn::exec(SExecutionContext & ctx) const
		{
			ctx.controlStack.emplace_back(mNext.get());

			mFn->exec(ctx);
		}

		void RecFn::zeroing(SExecutionContext & ctx)
		{
		}

		void Ret::exec(SExecutionContext & ctx) const
		{
			const auto next = ctx.controlStack.back().Ptr;
			ctx.controlStack.pop_back();

			next->exec(ctx);
		}

		void Ret::zeroing(SExecutionContext & ctx)
		{
		}

		void BasicFn::exec(SExecutionContext & ctx) const
		{
			// Поскольку при вызове базисной функции необходимо обработать исключение, проивзодим вызов
			// через метод-трамплин, чтобы не повлиять на оптимизацию компилятором хвостовой рекурсии.
#if fptlDebugBuild
			callFn(ctx);
#else
			mFn(ctx);
#endif
			mNext->exec(ctx);
		}

		void printErrTuple(std::ostream& error, const SExecutionContext & ctx)
		{
			error << "Input tuple type: ";
			ctx.printTypes(error);
			error << std::endl << "Input tuple: ";
			ctx.print(error);
			error << std::endl;
		}

		void BasicFn::callFn(SExecutionContext & ctx) const
		{
			try
			{
				mFn(ctx);
			}
			catch (std::exception& thrown)
			{
				std::stringstream error;
				Parser::Support::printError(error, mPos.first, mPos.second, thrown.what());
				error << "In function \"" << mName << "\"" << std::endl;
				printErrTuple(error, ctx);
				throw std::runtime_error(error.str());
			}
		}

		void BasicFn::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void GetArg::exec(SExecutionContext & ctx) const
		{
			size_t argNum;
			if (mArgNum < 0) argNum = ctx.argNum + mArgNum;
			else argNum = mArgNum - 1;
#if(fptlDebugBuild)
			ctx.push(TryGetArg(ctx, argNum));
#else
			ctx.push(ctx.getArg(argNum));
#endif
			mNext->exec(ctx);
		}

		const DataValue& GetArg::TryGetArg(const SExecutionContext& ctx, const size_t argNum) const
		{
			try
			{
				return ctx.getArg(argNum);
			}
			catch (std::exception & thrown)
			{
				std::stringstream error;
				Parser::Support::printError(error, mPos.first, mPos.second, thrown.what());
				printErrTuple(error, ctx);
				throw std::runtime_error(error.str());
			}
		}


		void GetArg::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void Constant::exec(SExecutionContext & ctx) const
		{
			ctx.push(mData);

			mNext->exec(ctx);
		}

		void Constant::pushString(SExecutionContext & ctx, const std::string & str)
		{
			ctx.push(StringBuilder::create(ctx, str));
		}

		void Constant::zeroing(SExecutionContext & ctx)
		{
			cancel(ctx, mNext);
		}

		void EndOp::exec(SExecutionContext & ctx) const
		{
		}

		void EndOp::zeroing(SExecutionContext & ctx)
		{
		}
	}
}
