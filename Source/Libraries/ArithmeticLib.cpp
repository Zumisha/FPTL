#define _USE_MATH_DEFINES

#include <cstdlib>
#include <regex>
#include <random>
#include <cmath>
#include <string>

#include "ArithmeticLib.h"

#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Генерирует случайное вещественное число в диапазоне от 0 до 1.
			void rand(SExecutionContext & aCtx)
			{
				static thread_local std::random_device rd;
				static thread_local std::mt19937_64 gen(rd());
				static std::uniform_real_distribution realDistrib;
				aCtx.push(DataBuilders::createDouble(realDistrib(gen)));
			}

			void sqrt(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::sqrt(arg.getOps()->toDouble(arg))));
			}

			void sin(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::sin(arg.getOps()->toDouble(arg))));
			}

			void cos(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::cos(arg.getOps()->toDouble(arg))));
			}

			void tan(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::tan(arg.getOps()->toDouble(arg))));
			}

			void asin(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::asin(arg.getOps()->toDouble(arg))));
			}

			void atan(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::atan(arg.getOps()->toDouble(arg))));
			}

			void round(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::floor(arg.getOps()->toDouble(arg) + 0.5)));
			}

			void log(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::log(arg.getOps()->toDouble(arg))));
			}

			void exp(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::exp(arg.getOps()->toDouble(arg))));
			}

			void loadPi(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createDouble(M_PI));
			}

			void loadE(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createDouble(M_E));
			}
		} // anonymous namespace

		const std::map<std::string, TFunction> functions =
		{
			// Арифметические.
			{"sqrt", &sqrt},
			{"exp", &exp},
			{"ln", &log},
			{"round", &round},
			{"sin", &sin},
			{"cos", &cos},
			{"tan", &tan},
			{"asin", &asin},
			{"atan", &atan},
			{"Pi", &loadPi},
			{"E", &loadE},
			{"rand", &rand}
		};

		void ArithmeticLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
