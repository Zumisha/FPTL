#include <utility>

#include "DataTypes/Ops/Ops.h"
#include "FunctionLibrary.h"

namespace FPTL
{
	namespace Runtime
	{
		void FunctionLibrary::addFunction(const std::string & aFunctionName, const TFunction & aFunction, const bool isLong)
		{
			mFunctions.insert(std::make_pair(aFunctionName, std::make_pair(aFunction, isLong)));
		}

		void FunctionLibrary::addFunctions(std::map<std::string, std::pair<TFunction, bool>> functions)
		{
			mFunctions.insert(functions.begin(), functions.end());
		}

		std::pair<TFunction, bool> FunctionLibrary::getFunction(const std::string & aFunctionName)
		{
			if (mFunctions.find(aFunctionName) != mFunctions.end())
			{
				return mFunctions.at(aFunctionName);
			}
			else
			{
				//assert(false); // Функция не найдена в библиотеке.
				// Возвращаем "пустышку".
				return std::make_pair(
					[](SExecutionContext & aCtx) {
					aCtx.push(DataBuilders::createUndefinedValue());},
					false);
			}
		}

		std::vector<std::string> FunctionLibrary::getFunctionNames()
		{
			std::vector<std::string> result;

			result.reserve(mFunctions.size());
			for (const auto& aElem : mFunctions)
			{
				result.push_back(aElem.first);
			}

			return result;
		}
	}
}
