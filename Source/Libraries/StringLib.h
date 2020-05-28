#pragma once

#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		class StringLib : public FunctionLibrary
		{
		public:
			StringLib() = delete;
			static void Register();
		};

	}
}
