#include <regex>
#include <string>

#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/StringOps.h"
#include "DataTypes/Ops/BooleanOps.h"
#include "LogicLib.h"

#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			void Not(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

#if fptlDebugBuild
				if (arg.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(arg.getOps()->getType(arg), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(!arg.getOps()->toInt(arg)));
			}

			void And(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), __func__);
				if (rhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) * rhs.getOps()->toInt(rhs))));
			}

			void Or(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), __func__);
				if (rhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) + rhs.getOps()->toInt(rhs))));
			}

			void Xor(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), __func__);
				if (rhs.getOps() != BooleanOps::get())
					throw BaseOps::invalidOperation(rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) ^ rhs.getOps()->toInt(rhs))));
			}

			void equal(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(lhs.getOps()->equal(lhs, rhs)));
			}

			void notEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(!lhs.getOps()->equal(lhs, rhs)));
			}

			void greater(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(lhs.getOps()->greater(lhs, rhs)));
			}

			void greaterOrEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(!lhs.getOps()->less(lhs, rhs)));
			}

			void less(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(lhs.getOps()->less(lhs, rhs)));
			}

			void lessOrEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

#if fptlDebugBuild
				if (lhs.getOps() != rhs.getOps())
					throw BaseOps::invalidOperation(lhs.getOps()->getType(lhs), rhs.getOps()->getType(rhs), __func__);
#endif

				aCtx.push(DataBuilders::createBoolean(!lhs.getOps()->greater(lhs, rhs)));
			}
		} // anonymous namespace

		const std::map<std::string, TFunction> functions =
		{
			{"not", &Not},
			{"and", &And},
			{"or", &Or },
			{"xor", &Xor },
			{"equal", &equal},
			{"nequal", &notEqual},
			{"greater", &greater},
			{"gequal", &greaterOrEqual},
			{"less", &less},
			{"lequal", &lessOrEqual}
		};

		void LogicLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
