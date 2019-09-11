#pragma once

#include <string>
#include <ostream>
#include <utility>
#include <vector>
#include <unordered_map>

namespace FPTL { namespace Runtime {

//------------------------------------------------------------------------------------------
struct TypeInfo
{
	std::string typeName;
	std::vector<TypeInfo> typeParameters;
	// Тк количество типовых параметров редко превышает 2,
	// линейный поиск по массиву будет быстрее,
	// чем доступ к элементу в дереве или хеш-таблице.

	TypeInfo() = default;
	explicit TypeInfo(std::string aTypeName) : typeName(std::move(aTypeName)) {}
	TypeInfo(std::string aTypeName, const TypeInfo& aParameter) : typeName(std::move(aTypeName)), typeParameters(std::vector<TypeInfo>{aParameter}) {}
	TypeInfo(std::string aTypeName, std::vector<TypeInfo> aParameters) : typeName(std::move(aTypeName)), typeParameters(std::move(aParameters)) {}
	
	static bool matchType(const TypeInfo aTypeInfo, const TypeInfo * aRef, std::unordered_map<std::string, struct TypeInfo> & aParametersMap);
	friend std::ostream & operator <<(std::ostream& aStream, const TypeInfo& aTypeInfo);
	friend bool operator ==(const TypeInfo& lTypeInfo, const TypeInfo& rTypeInfo);
	friend bool operator !=(const TypeInfo& lTypeInfo, const TypeInfo& rTypeInfo);

	void addParameter(const TypeInfo& aParam)
	{
		typeParameters.push_back(aParam);
	}
};

}} // FPTL::Runtime
