#pragma once

#include "Utils/FormattedOutput.h"

namespace FPTL {
	namespace Runtime
	{
		struct EvalConfig
		{
			Utils::FormattedOutput output;
			size_t numCores;
			bool printInfo;
			bool printTime;
			bool proactiveEnabled;
			bool stackTrace;
			bool unsafeMode;
		};
	}
}