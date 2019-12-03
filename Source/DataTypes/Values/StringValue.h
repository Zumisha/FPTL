#pragma once

#include <utility>
#include <iostream>

#include "Value.h"

namespace FPTL {
	namespace Runtime {
		class StringValue
		{
		public:
			std::string mVal;

			StringValue() = default;

			explicit StringValue(const size_t aSize)
			{
				mVal.reserve(aSize);
			}

			explicit StringValue(std::string aData) : mVal(std::move(aData)) {}
		};
	}
}