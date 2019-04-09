#pragma once

// Types.h - внтутреннее представление информации о типах в FPTL.

#include <vector>
#include <ostream>
#include <unordered_map>
#include <boost/bind.hpp>

#include "../../Parser/Nodes.h"

namespace FPTL { namespace Runtime {

typedef std::unordered_map<std::string, struct TypeInfo *> TParametersMap;

//------------------------------------------------------------------------------------------
// Информация о типе. Не требует сборки мусора, т.к. каждая структура храниться в TypeInfoRegistry.
struct TypeInfo
{
	std::string TypeName;

	std::unordered_map<std::string, TypeInfo> Parameters;

	TypeInfo()
	{}
	TypeInfo(const std::string & aTypeName) : TypeName(aTypeName)
	{}
	TypeInfo(const std::string & aTypeName, const TParametersMap & aParameters) : TypeName(aTypeName)
	{
		for (auto i = aParameters.begin(); i != aParameters.end(); ++i)
		{
			Parameters.insert(std::make_pair(i->first, *i->second));
		}
	}

	// Производит проверку составного типа aTypeInfo c эталоном aRef.
	static bool matchType(const TypeInfo * aTypeInfo, const TypeInfo * aRef, TParametersMap & aParametersMap);

	// Вывод типовой информации.
	friend std::ostream & operator <<(std::ostream & aStream, const TypeInfo & aTypeInfo);

	void addParameter(const std::string & aName, const TypeInfo & aParam)
	{
		Parameters.insert(std::make_pair(aName, aParam));
	}

	TypeInfo getParameter(const std::string & aName)
	{
		return Parameters.at(aName);
	}
};

typedef std::vector<TypeInfo> TTypeList;

//------------------------------------------------------------------------------------------

}} // FPTL::Runtime
