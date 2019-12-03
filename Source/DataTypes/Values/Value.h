#pragma once

#include <sstream>

#include "../TypeInfo.h"
#include "../Ops/Ops.h"

namespace FPTL {
	namespace Runtime {

		class BaseOps;

		// Universal data class.
		// Provides simple calls of basic operations.
		class Value
		{
		public:
			Ops* ops;
			union
			{
				bool mBoolVal;
				int64_t mIntVal;
				double mDoubleVal;
				void* mOtherVal = nullptr;
			}; // size = max of members size (8 bytes)

			Value();

			explicit Value(Ops* ops);

			Value(const Value& val);

			Value& operator=(const Value& val);

			Value(Value&& val) noexcept;

			Value& operator=(Value&& val) noexcept;

			~Value();

			TypeInfo Type() const;
			bool GreaterThan(const Value& other) const;
			bool EqualTo(const Value& other) const;
			bool LessThan(const Value& other) const;
			Value Read(std::istream& aStream) const;
			void Print(std::ostream& aStream) const;

			Value Copy() const;
			size_t Length() const;
			int64_t ToInt() const;
			double ToDouble() const;

			std::string ToString() const;
			bool ToBool() const;
			Value operator+(const Value& other) const;
			Value operator-(const Value& other) const;
			Value operator*(const Value& other) const;
			Value operator/(const Value& other) const;
			Value operator%(const Value& other) const;
			Value& operator[](const size_t index) const;
			Value Abs() const;
		};
	}
}
