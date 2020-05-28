#pragma once

#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		class ArrayLib : public FunctionLibrary
		{
		public:
			ArrayLib() = delete;
			static void Register();
		};

	}
}
