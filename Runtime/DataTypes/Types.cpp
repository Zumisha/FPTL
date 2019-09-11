#include "Types.h"
#include <unordered_map>

namespace FPTL { namespace Runtime {

bool TypeInfo::matchType(const TypeInfo aTypeInfo, const TypeInfo * aRef, std::unordered_map<std::string, struct TypeInfo> & aParametersMap)
{
	if (aRef->typeName[0] == '\'')
	{
		// Типовой параметр может быть заменен любым типом.
		// Проверяем, чтобы один и тот же типовой параметр не был ассоциирован с разными типами.

		auto it = aParametersMap.find(aRef->typeName);

		if (it != aParametersMap.end())
		{
			std::unordered_map<std::string, struct TypeInfo> parameterMap;

			if (!matchType(aTypeInfo, &it->second, parameterMap))
			{
				return false;
			}
		}

		aParametersMap.insert(std::make_pair(aRef->typeName, aTypeInfo));

		return true;
	}
	if (aRef->typeName == aTypeInfo.typeName)
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
	// Type mismatch.
	return false;
}

std::ostream & operator <<(std::ostream & aStream, const TypeInfo & aTypeInfo)
{
	aStream << aTypeInfo.typeName;
	if (!aTypeInfo.typeParameters.empty())
	{
		aStream << "[";
		const auto size = aTypeInfo.typeParameters.size();
		size_t i = 0;
		for (const auto& param : aTypeInfo.typeParameters)
		{
			aStream << param;
			if (i + 1 < size)
			{
				aStream << ", ";
			}
			++i;
		}
		aStream << "]";
	}

	return aStream;
}

bool operator==(const TypeInfo& lTypeInfo, const TypeInfo& rTypeInfo)
{
	if (lTypeInfo.typeName != rTypeInfo.typeName) return false;
	if (lTypeInfo.typeParameters.size() != rTypeInfo.typeParameters.size()) return false;
	for (size_t i = 0; i < lTypeInfo.typeParameters.size(); ++i)
	{
		if (rTypeInfo.typeParameters[i] != lTypeInfo.typeParameters[i]) return false;
	}
	return true;
}

bool operator!=(const TypeInfo& lTypeInfo, const TypeInfo& rTypeInfo)
{
	return !(lTypeInfo == rTypeInfo);
}

}} // FPTL::Runtime