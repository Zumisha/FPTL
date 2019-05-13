#pragma once

#include <string>
#include <map>
#include <functional>

#include "Context.h"

namespace FPTL { namespace Runtime {

typedef std::function<void (SExecutionContext &)> TFunction;

// Библиотека функций.
class FunctionLibrary
{
public:
	FunctionLibrary(const std::string & aLibraryName);

	void addFunction(const std::string & aFunctionName, const TFunction & aFunction);

	void addFunctions(std::map<std::string, TFunction> Functions);

	std::vector<std::string> getFunctionNames() const;

	TFunction getFunction(const std::string & aName) const;

	std::string getName() const;

private:
	std::string mLibraryName;
	std::map<std::string, TFunction> mFunctions;
};

} // Runtine
} // FPTL