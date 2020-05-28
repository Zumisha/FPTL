#include <chrono>
#include <string>

#include "TimeLib.h"
#include "FunctionLibrary.h"
#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/TimeOps.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {
			void GetCurrentTime(SExecutionContext& aCtx)
			{
				const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				aCtx.push(DataBuilders::createTime(time));
			}			
		} // anonymous namespace

		const std::map<std::string, TFunction> functions =
		{
			{"getCurrentTime", &GetCurrentTime}
		};

		void TimeLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
