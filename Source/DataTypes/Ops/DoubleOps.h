#pragma once

#include <istream>
#include <cmath>

#include "Macros.h"
#include "BaseOps.h"
#include "../Values/Value.h"

namespace FPTL {
	namespace Runtime {

		// Implementation of operations on boolean values.
		class DoubleOps : public BaseOps
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("Double");

			static DoubleOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value or this  classes.
				static DoubleOps ops;
				return &ops;
			}

			static Value Create(const double val = 0)
			{
				auto res = Value(get());
				res.mDoubleVal = val;
				return res;
			}

			static void ValueCheck(const Value & val)
			{
				if (val.ops != get())
				{
					throw std::runtime_error("Double operation on not double value.");
				}
			}

			TypeInfo Type(const Value& val) const override
			{
				(void)(val);
				return staticTypeInfo;
			}

			int64_t ToInt(const Value& val) const override { return static_cast<int64_t>(val.mDoubleVal); };

			double ToDouble(const Value& val) const override { return val.mDoubleVal; };

			bool ToBool(const Value& val) const override { return val.mDoubleVal; };

			bool Greater(const Value& left, const Value& right) const override
			{
				return (left.ToDouble() > right.ToDouble());
			}

			bool Equal(const Value& left, const Value& right) const override
			{
				return (left.ToDouble() == right.ToDouble());
			}

			bool Less(const Value& left, const Value& right) const override
			{
				return (left.ToDouble() < right.ToDouble());
			}

			// Вывод в поток.
			void Print(const Value& val, std::ostream & aStream) const override
			{
				aStream << val.ToDouble();
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				(void)(val);
				auto res = Value(get());
				aStream >> res.mDoubleVal;
				return res;
			}

			Value Add(const Value& left, const Value& right) const override
			{
				return Create(left.ToDouble() + right.ToDouble());
			}

			Value Sub(const Value& left, const Value& right) const override
			{
				return Create(left.ToDouble() - right.ToDouble());
			}

			Value Mul(const Value& left, const Value& right) const override
			{
				return Create(left.ToDouble() * right.ToDouble());
			}

			Value Div(const Value& left, const Value& right) const override
			{
				const double rightVal = right.ToDouble();
#if fptlDebugBuild
				if (rightVal == 0) throw std::overflow_error("Divide by zero");
#endif
				return Create(left.ToDouble() / rightVal);
			}

			Value Abs(const Value& val) const override
			{
				return Create(std::abs(val.ToDouble()));
			}
		};

	}
}
