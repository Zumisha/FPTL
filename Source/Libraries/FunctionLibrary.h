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
			FunctionLibrary() = delete;

			static void addFunction(const std::string& aFunctionName, const TFunction& aFunction);
			static void addFunctions(std::map<std::string, TFunction> functions);

			static std::vector<std::string> getFunctionNames();
			static TFunction getFunction(const std::string & aFunctionName);

		private:
			// ToDo: type to functions
			static std::map<std::string, TFunction> mFunctions;
		};
	}
}
