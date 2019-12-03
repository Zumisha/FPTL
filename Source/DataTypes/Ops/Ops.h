#pragma once

#include <istream>

#include "DataTypes/TypeInfo.h"

namespace FPTL {
	namespace Runtime {
		class Value;

		// Abstract basic operations class. 
		// Needed for successful class binding at compile time.
		// Because Ops uses Value, and Value uses Ops.
		class Ops
		{
		public:
			virtual ~Ops() = default;

			virtual void Delete(const Value& val) const = 0;
			virtual void makeUndefined(Value& val) const = 0;
			virtual TypeInfo Type(const Value& val) const = 0;
			virtual bool Greater(const Value& left, const Value& right) const = 0;
			virtual bool Equal(const Value& left, const Value& right) const = 0;
			virtual bool Less(const Value& left, const Value& right) const = 0;
			virtual Value Read(const Value& val, std::istream & aStream) const = 0;
			virtual void Print(const Value& val, std::ostream & aStream) const = 0;
			virtual void* Copy(const Value& val) const = 0;
			virtual size_t Length(const Value& val) const = 0;
			virtual bool ToBool(const Value& val) const = 0;
			virtual int64_t ToInt(const Value& val) const = 0;
			virtual double ToDouble(const Value& val) const = 0;
			virtual Value Add(const Value& left, const Value& right) const = 0;
			virtual Value Sub(const Value& left, const Value& right) const = 0;
			virtual Value Mul(const Value& left, const Value& right) const = 0;
			virtual Value Div(const Value& left, const Value& right) const = 0;
			virtual Value Mod(const Value& left, const Value& right) const = 0;
			virtual Value& GetRef(const Value& val, size_t index) = 0;
			virtual Value Abs(const Value& val) const = 0;
		};
	}
}