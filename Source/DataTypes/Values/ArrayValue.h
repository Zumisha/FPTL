#pragma once
#include "Value.h"
#include <utility>

namespace FPTL {
	namespace Runtime {
		class ArrayOps;

		class ArrayValue
		{
		public:
			const TypeInfo type;
			std::vector<Value> mVal{};

			ArrayValue(const size_t aLength, const Value& initial, TypeInfo type) : type(std::move(type))
			{	
				mVal.reserve(aLength);
				for (size_t i = 0; i < aLength; ++i)
				{
					mVal.push_back(initial.Copy());
				}
			}

			explicit ArrayValue(const std::vector<Value>& val, TypeInfo type) : type(std::move(type))
			{
				mVal.reserve(val.size());
				for (const auto& el : val)
				{
					mVal.push_back(el.Copy());
				}
			}
		};
	}
}
