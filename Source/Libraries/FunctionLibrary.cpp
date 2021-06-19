#include <utility>

#include "DataTypes/Ops/Ops.h"
#include "FunctionLibrary.h"

namespace FPTL::Runtime
{
		void FunctionLibrary::addFunction(const std::string& aFunctionName, const TypedFunction& aFunction)
		{
			auto funcs = mFunctions.find(aFunctionName);
			if (funcs == mFunctions.end())
			{
				std::vector<const TypedFunction> vect;
				vect.push_back(aFunction);
				mFunctions.insert(std::make_pair(aFunctionName, vect));
			}
			else
			{
				funcs->second.push_back(aFunction);
			}
		}

		void FunctionLibrary::addFunctions(const std::map<const std::string, std::vector<const TypedFunction>>& aFunctions)
		{
			for (const auto& funcsPair : aFunctions)
			{
				auto funcs = mFunctions.find(funcsPair.first);
				if (funcs == mFunctions.end())
				{
					mFunctions.insert(std::make_pair(funcsPair.first, funcsPair.second));
				}
				else
				{
					funcs->second.insert(funcs->second.end(), funcsPair.second.begin(), funcsPair.second.end());
				}
			}
		}

		const std::vector<const TypedFunction>* FunctionLibrary::getFunctions(const std::string& aFunctionName)
		{
			if (mFunctions.find(aFunctionName) != mFunctions.end())
			{
				return &mFunctions.at(aFunctionName);
			}
			else
			{
				throw std::exception("function not found in library");
			}
		}

		std::vector<const std::string> FunctionLibrary::getAllFunctionNames()
		{
			std::vector<const std::string> result;

			result.reserve(mFunctions.size());
			for (const auto& aElem : mFunctions)
			{
				result.push_back(aElem.first);
			}

			return result;
		}
}
