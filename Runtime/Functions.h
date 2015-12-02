#pragma once

#include <list>
#include <string>
#include <map>
#include <functional>

#include "Context.h"

namespace FPTL { namespace Runtime {

//-------------------------------------------------------------------------------
// TODO: сделать отдельный интерфейс конструктора.
class Constructor
{
public:

	Constructor(const std::string & aConstructorName,
		const std::string & aTypeName,
		const TTypeList & aRefType,
		const std::vector<std::string> & aParameters
	);
	virtual ~Constructor();

	virtual void execConstructor(SExecutionContext & aCtx) const;
	virtual void execDestructor(SExecutionContext & aCtx) const;

	std::string name() const { return mConstructorName; }
	TTypeList type() const { return mReferenceType; }
	TypeInfo * targetType() const { return const_cast<TypeInfo *>(&mTargetType); }
	int arity() const { return static_cast<int>(mReferenceType.size()); }

protected:

	std::string mConstructorName;
	std::string mTypeName;

	// Эталонный тип.
	TTypeList mReferenceType;

	// Создаваемый тип данных.
	TypeInfo mTargetType;
};

//-------------------------------------------------------------------------------
// Конструктор без параметров.
class EmptyConstructor : public Constructor
{
public:

	EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName);

	virtual void execConstructor(SExecutionContext & aCtx) const;

private:
	TypeInfo mTypeInfo;
};

//-------------------------------------------------------------------------------
typedef std::function<void (SExecutionContext &)> TFunction;


//-------------------------------------------------------------------------------
// Библиотека функций.
class FunctionLibrary
{
public:
	FunctionLibrary(const std::string & aLibraryName);

	void addFunction(const std::string & aFunctionName, const TFunction & aFunction);

	std::vector<std::string> getFunctionNames() const;

	TFunction getFunction(const std::string & aName) const;

	std::string getName() const;

private:
	std::string mLibraryName;
	std::map<std::string, TFunction> mFunctions;
};

//-------------------------------------------------------------------------------

} // Runtine
} // FPTL
