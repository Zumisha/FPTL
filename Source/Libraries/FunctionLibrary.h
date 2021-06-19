#pragma once

#include <string>
#include <map>
#include <functional>


#include "DataTypes/TypedFunction.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		// Библиотека функций.
		class FunctionLibrary
		{
		public:
			FunctionLibrary() = delete;

			static void addFunction(const std::string& aFunctionName, const TypedFunction& aFunction);
			static void addFunctions(const std::map<const std::string, std::vector<const TypedFunction>>& functions);

			static std::vector<const std::string> getAllFunctionNames();
			static const std::vector<const TypedFunction>* getFunctions(const std::string& aFunctionName);

		private:
			static std::map<const std::string, std::vector<const TypedFunction>> mFunctions;
		};
	}
}
