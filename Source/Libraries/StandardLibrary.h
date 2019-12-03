#pragma once

#include "FunctionLibrary.h"

namespace FPTL 
{
	namespace Runtime 
	{
		class StandardLibrary : public FunctionLibrary
		{
		public:
			StandardLibrary();
			static const std::map<std::string, TFunction> mFunctions;
		};

	}
}
