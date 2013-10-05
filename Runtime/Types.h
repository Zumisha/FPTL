#pragma once

// Types.h - внтутреннее представление информации о типах в FPTL.

//
// Основная идея.
// 
// У каждого типа данных иммется своя структура TypeInfo.
// Для каждого конструктора содержится реестр возможных типов, к которым может быть применен данные конструктор.
// Изначально реестр пуст.
// Если при выполнении конструктора над кортежем типа T, тип T имеется в реестре, то он возвращается в качестве типа объекта, созданного конструктором.
// Если Т в реестре не содержится, то производится полная типовая проверка, и он либо добавляется в реестр, либо генерируется исключение.
//

#include "../Parser/Nodes.h"
#include <vector>
#include <algorithm>
#include <ostream>
#include <ext/hash_map>
#include <boost/bind.hpp>

namespace FPTL { namespace Runtime {

typedef std::hash_map<std::string, struct TypeInfo *> TParametersMap;

//------------------------------------------------------------------------------------------
// Информация о типе. Не требует сборки мусора, т.к. каждая структура храниться в TypeInfoRegistry.
struct TypeInfo
{
	std::string TypeName;

	std::hash_map<std::string, TypeInfo> Parameters;

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
};

typedef std::vector<TypeInfo> TTypeList;

//------------------------------------------------------------------------------------------

}} // FPTL::Runtime
