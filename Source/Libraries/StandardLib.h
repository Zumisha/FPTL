#pragma once

#include "FunctionLibrary.h"

namespace FPTL 
{
	namespace Runtime 
	{
		class StandardLib
		{
		public:
			StandardLib() = delete;
			static void Register();
		};

	}
}
