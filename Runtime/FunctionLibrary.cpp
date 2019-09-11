#include "DataTypes/Data.h"
#include "FunctionLibrary.h"

namespace FPTL {
	namespace Runtime {
		FunctionLibrary::FunctionLibrary(const std::string & aLibraryName)
			: mLibraryName(aLibraryName)
		{
		}

		void FunctionLibrary::addFunction(const std::string & aFunctionName, const TFunction & aFunction)
		{
			mFunctions.insert(std::make_pair(aFunctionName, aFunction));
		}

		void FunctionLibrary::addFunctions(std::map<std::string, TFunction> Functions)
		{
			mFunctions.insert(Functions.begin(), Functions.end());
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
					aCtx.push(DataBuilders::createUndefinedValue());
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