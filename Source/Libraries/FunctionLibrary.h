#pragma once

#include <string>
#include <map>
#include <functional>

#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		typedef std::function<void(SExecutionContext &)> TFunction;

		// Библиотека функций.
		class FunctionLibrary
		{
		public:
			explicit FunctionLibrary(std::string aLibraryName);

			void addFunction(const std::string & aFunctionName, const TFunction & aFunction);

			void addFunctions(std::map<std::string, TFunction> functions);

			std::vector<std::string> getFunctionNames() const;

			TFunction getFunction(const std::string & aFunctionName) const;

			std::string getName() const;

		private:
			std::string mLibraryName;
			std::map<std::string, TFunction> mFunctions;
		};
	}
}
