#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>

namespace FPTL {
namespace Parser {

struct TypeInfo
{
	std::string name;
	std::map<std::string, TypeInfo> parameters;

	TypeInfo(const std::string & aName) : name(aName)
	{}

	bool operator == (const TypeInfo & aOther) const
	{
		return name == aOther.name && parameters == aOther.parameters;
	}

	std::string toString() const
	{
		std::string result = name;

		if (!parameters.empty())
		{
			result += "[";
			for (auto p = parameters.begin(); p != parameters.end(); ++p)
			{
				result += p->second.toString() + ",";
			}
			result.pop_back();
			result += "]";
		}

		return result;
	}
};

class TTuple : public std::vector<TypeInfo>
{
public:
	TTuple()
	{}
	TTuple(size_t aSize, const TypeInfo & aInfo) : std::vector<TypeInfo>(aSize, aInfo)
	{}

	std::string toString() const
	{
		std::string result;

		if (!empty())
		{
			for (auto e = begin(); e != end(); ++e)
			{
				result += e->toString() + "*";
			}
			result.pop_back();
		}
		else
		{
			result = "<undefined>";
		}

		return result;
	}

	TTuple operator +(const TTuple & aOther) const
	{
		TTuple result = *this;
		result.insert(result.end(), aOther.begin(), aOther.end());
		return result;
	}
};

}}
