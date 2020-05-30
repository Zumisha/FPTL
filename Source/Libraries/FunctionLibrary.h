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

			static void addFunction(const std::string& aFunctionName, const TFunction& aFunction, const bool isLong);
			static void addFunctions(std::map<std::string, std::pair<TFunction, bool>> functions);

			static std::vector<std::string> getFunctionNames();
			static std::pair<TFunction, bool> getFunction(const std::string & aFunctionName);

		private:
			// ToDo: type to functions
			static std::map<std::string, std::pair<TFunction, bool>> mFunctions;
		};
	}
}
