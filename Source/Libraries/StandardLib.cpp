﻿#include <iostream>
#include <regex>
#include <experimental/filesystem>
#include <string>

#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

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
			void Id(SExecutionContext & aCtx)
			{
				// Копируем данные аргументы от начала фрейма.
				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					aCtx.push(aCtx.getArg(i));
				}
			}

			void TupleLength(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createInt(static_cast<long long>(aCtx.argNum)));
			}

			void Print(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				aCtx.print(ss);
				std::cout << ss.rdbuf();
			}

			void PrintLine(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				aCtx.print(ss);
				ss << "\n";
				std::cout << ss.rdbuf();
			}

			void RawPrint(const SExecutionContext & aCtx)
			{
				std::stringstream ss;
				aCtx.rawPrint(ss);
				std::cout << ss.rdbuf();
			}

			void PrintType(const SExecutionContext & aCtx)
			{
				static boost::mutex outputMutex;
				boost::lock_guard<boost::mutex> guard(outputMutex);

				aCtx.printTypes(std::cout);
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

#if fptlDebugBuild
				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					BaseOps::opsCheck(firstOps, aCtx.getArg(i));
				}
#endif

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

		const std::map<std::string, TFunction> functions =
		{
			// Работа с кортежем.
			{"id", &Id},
			{"tupleLen", &TupleLength},

			// Преобразования типов.
			{"toInt", &ToInteger},
			{"toReal", &ToDouble},

			// Ввод / вывод.
			{"print", &Print},
			{"printLine", &PrintLine},
			{"rawPrint", &RawPrint},
			{"printType", &PrintType},
			
			{"add",&Add},
			{"sub", &Sub},
			{"mul", &Mul},
			{"div", &Div},
			{"mod", &Mod},
			{"abs", &Abs}
		};

		void StandardLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}