﻿#include <cassert>
#include "Types.h"
#include "Data.h"
#include "Functions.h"

#include <boost/functional/hash.hpp>

namespace FPTL { namespace Runtime {

bool TypeInfo::matchType(const TypeInfo * aTypeInfo, const TypeInfo * aRef, TParametersMap & aParametersMap)
{
	if (aRef->TypeName[0] == '\'')
	{
		// Типовой параметр может быть заменен любым типом.
		// Проверяем, чтобы один и тот же типовой параметр не был ассоциирован с разными типами.

		TParametersMap::iterator it = aParametersMap.find(aRef->TypeName);

		if (it != aParametersMap.end())
		{
			TParametersMap parameterMap;

			if (!matchType(aTypeInfo, it->second, parameterMap))
			{
				return false;
			}
		}

		aParametersMap.insert(std::make_pair(aRef->TypeName, const_cast<TypeInfo *>(aTypeInfo)));
			
		return true;
	}
	else
	{
		if (aRef->TypeName == aTypeInfo->TypeName)
		{
			// Отключил проверку параметров, т.к. в конкретном экземпляре ADT-значения она не сохраняется (Java-style).
			/*if (aTypeInfo->Parameters.empty())
			{
				// Тип не имеет параметров или был создан пустым конструктором.
				return true;
			}

			// Производим проверку параметров, если они есть.
			for (auto it = aRef->Parameters.begin(); it != aRef->Parameters.end(); ++it)
			{
				if (!matchType(&aTypeInfo->Parameters.at(it->first), &it->second, aParametersMap))
				{
					return false;
				}
			}*/

			return true;
		}
	}

	// Type mismatch.
	return false;
}

//----------------------------------------------------------------------------------------------
std::ostream & operator <<(std::ostream & aStream, const TypeInfo & aTypeInfo)
{
	aStream << aTypeInfo.TypeName;

	if (!aTypeInfo.Parameters.empty())
	{
		aStream << "[";

		std::for_each(aTypeInfo.Parameters.begin(), aTypeInfo.Parameters.end(),
			[&aStream](const std::pair<std::string, TypeInfo> & aRecord)
			{
				aStream << aRecord.first << "=" << aRecord.second;
			}
		);

		aStream << "]";
	}

	return aStream;
}

//----------------------------------------------------------------------------------------------

}} // FPTL::Runtime