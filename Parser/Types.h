#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <boost/unordered_map.hpp>

namespace FPTL {
namespace Parser {
/*
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
> class my_unordered_map: public std::unordered_map<Key, T, Hash, KeyEqual, Allocator>
*/
struct TypeInfo
{
	std::string name;
	boost::unordered_map<std::string, TypeInfo> parameters;

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
