#pragma once

#include "Macros.h"
#include "BaseOps.h"
#include "../Values/Value.h"

namespace FPTL {
	namespace Runtime {

		// Implementation of operations on integer values.
		class IntegerOps : public BaseOps
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("Int");

			static IntegerOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value or this classes.
				static IntegerOps ops;
				return &ops;
			}

			static Value Create(const int64_t val = 0)
			{
				auto res = Value(get());
				res.mIntVal = val;
				return res;
			}

			static void ValueCheck(const Value & val)
			{
				if (val.ops != get())
				{
					throw std::runtime_error("Int operation on not int value.");
				}
			}

			TypeInfo Type(const Value& val) const override
			{
				(void)(val);
				return staticTypeInfo;
			}

			int64_t ToInt(const Value& val) const override { return val.mIntVal; };

			double ToDouble(const Value& val) const override { return static_cast<double>(val.mIntVal); };

			bool ToBool(const Value& val) const override { return val.mIntVal; };

			bool Greater(const Value& left, const Value& right) const override
			{
				return (left.ToInt() > right.ToInt());
			}

			bool Equal(const Value& left, const Value& right) const override
			{
				return (left.ToInt() == right.ToInt());
			}

			bool Less(const Value& left, const Value& right) const override
			{
				return (left.ToInt() < right.ToInt());
			}

			// Вывод в поток.
			void Print(const Value& val, std::ostream & aStream) const override
			{
				aStream << val.ToInt();
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				(void)(val);
				auto res = Value(get());
				aStream >> res.mIntVal;
				return res;
			}

			Value Add(const Value& left, const Value& right) const override
			{
				return Create(left.ToInt() + right.ToInt());
			}

			Value Sub(const Value& left, const Value& right) const override
			{
				return Create(left.ToInt() - right.ToInt());
			}

			Value Mul(const Value& left, const Value& right) const override
			{
				return Create(left.ToInt() * right.ToInt());
			}

			Value Div(const Value& left, const Value& right) const override
			{
				const int64_t rightInt = right.ToInt();
#if fptlDebugBuild
				if (rightInt == 0) throw std::overflow_error("Divide by zero");
#endif
				return Create(left.ToInt() / rightInt);
			}

			Value Mod(const Value& left, const Value& right) const override
			{
				const int64_t rightInt = right.ToInt();
#if fptlDebugBuild
				if (rightInt == 0) throw std::overflow_error("Divide by zero");
#endif
				return Create(left.ToInt() % rightInt);
			}

			Value Abs(const Value& val) const override
			{
				return Create(std::abs(val.ToInt()));
			}
		};

	}
}
