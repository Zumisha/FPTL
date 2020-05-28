#pragma once

#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		class TimeLib : public FunctionLibrary
		{
		public:
			TimeLib() = delete;
			static void Register();
		};

	}
}
