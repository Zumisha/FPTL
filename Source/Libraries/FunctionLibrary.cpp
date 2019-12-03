#include <utility>

#include "FunctionLibrary.h"
#include "DataTypes/Ops/BaseOps.h"

namespace FPTL {
	namespace Runtime {
		FunctionLibrary::FunctionLibrary(std::string aLibraryName)
			: mLibraryName(std::move(aLibraryName))
		{
		}

		void FunctionLibrary::addFunction(const std::string & aFunctionName, const TFunction & aFunction)
		{
			mFunctions.insert(std::make_pair(aFunctionName, aFunction));
		}

		void FunctionLibrary::addFunctions(std::map<std::string, TFunction> functions)
		{
			mFunctions.insert(functions.begin(), functions.end());
		}

		TFunction FunctionLibrary::getFunction(const std::string & aFunctionName) const
		{
			if (mFunctions.find(aFunctionName) != mFunctions.end())
			{
				return mFunctions.at(aFunctionName);
			}
			else
			{
				//assert(false); // Функция не найдена в библиотеке.

				// Возвращаем "пустышку".
				return [](SExecutionContext & aCtx) {
					aCtx.push(BaseOps::Create());
				};
			}
		}

		std::vector<std::string> FunctionLibrary::getFunctionNames() const
		{
			std::vector<std::string> result;

			for (const auto& aElem : mFunctions)
			{
				result.push_back(aElem.first);
			}

			return result;
		}

		std::string FunctionLibrary::getName() const
		{
			return mLibraryName;
		}

		//-------------------------------------------------------------------------------

	} // Runtime
} // FPTL