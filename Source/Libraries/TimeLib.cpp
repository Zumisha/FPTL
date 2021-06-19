#include <chrono>
#include <string>

#include "TimeLib.h"
#include "FunctionLibrary.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/TimeOps.h"

namespace FPTL::Runtime
{
		namespace {
			void GetCurrentTime(SExecutionContext& aCtx)
			{
				const auto time = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
				aCtx.push(DataBuilders::createTime(time.time_since_epoch().count()));
			}			
		} // anonymous namespace

		const std::map<std::string, std::pair<TFunction, bool>> functions =
		{
			{ "getCurrentTime", std::make_pair(&GetCurrentTime, false) },
		};

		void TimeLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
}
