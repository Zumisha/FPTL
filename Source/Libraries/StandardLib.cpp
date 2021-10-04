#include <iostream>
#include <regex>
#include <filesystem>
#include <string>

#include <boost/thread/mutex.hpp>

#include "StandardLib.h"
#include "FunctionLibrary.h"
#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/StringOps.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {
			
			void TupleLength(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createInt(static_cast<long long>(aCtx.argNum)));
			}

			void Print(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				ss.precision(std::numeric_limits<double>::max_digits10);
				aCtx.print(ss);
				std::cout << ss.rdbuf();
			}

			void PrintLine(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				ss.precision(std::numeric_limits<double>::max_digits10);
				aCtx.print(ss);
				ss << "\n";
				std::cout << ss.rdbuf();
			}

			void RawPrint(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				ss.precision(std::numeric_limits<double>::max_digits10);
				aCtx.rawPrint(ss);
				std::cout << ss.rdbuf();
			}

			void PrintType(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				aCtx.printTypes(ss);
				std::cout << ss.rdbuf();
			}

			// Преобразование в вещественное число.
			void ToInteger(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

				aCtx.push(DataBuilders::createInt(arg.getOps()->toInt(arg)));
			}

			// Преобразование в целое число.
			void ToDouble(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

				aCtx.push(DataBuilders::createDouble(arg.getOps()->toDouble(arg)));
			}

			void Add(SExecutionContext& aCtx)
			{
				const auto& first = aCtx.getArg(0);
				const auto* const firstOps = first.getOps();

				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					BaseOps::opsCheck(firstOps, aCtx.getArg(i));
				}

				aCtx.push(firstOps->add(aCtx, aCtx.firstArg(), aCtx.lastArg()));
			}

			void Sub(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				BaseOps::opsCheck(lhs.getOps(), rhs);

				aCtx.push(lhs.getOps()->sub(lhs, rhs));
			}

			void Mul(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				BaseOps::opsCheck(lhs.getOps(), rhs);

				aCtx.push(lhs.getOps()->mul(lhs, rhs));
			}

			void Div(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				BaseOps::opsCheck(lhs.getOps(), rhs);

				aCtx.push(lhs.getOps()->div(lhs, rhs));
			}

			void Mod(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				BaseOps::opsCheck(lhs.getOps(), rhs);

				aCtx.push(lhs.getOps()->mod(lhs, rhs));
			}

			void Abs(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(arg.getOps()->abs(arg));
			}
		} // anonymous namespace

		const std::map<std::string, std::pair<TFunction, bool>> functions =
		{
			{ "tupleLen", std::make_pair(&TupleLength, false) },
			
			{ "toInt", std::make_pair(&ToInteger, false) },
			{ "toReal", std::make_pair(&ToDouble, false) },
			
			{ "print", std::make_pair(&Print, false) },
			{ "printLine", std::make_pair(&PrintLine, false) },
			{ "rawPrint", std::make_pair(&RawPrint, false) },
			{ "printType", std::make_pair(&PrintType, false) },
			
			{ "add", std::make_pair(&Add, false) },
			{ "sub", std::make_pair(&Sub, false) },
			{ "mul", std::make_pair(&Mul, false) },
			{ "div", std::make_pair(&Div, false) },
			{ "mod", std::make_pair(&Mod, false) },
			{ "abs", std::make_pair(&Abs, false) },
		};

		void StandardLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
