#pragma once

#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		class FileLib : public FunctionLibrary
		{
		public:
			FileLib() = delete;
			static void Register();
		};

	}
}
