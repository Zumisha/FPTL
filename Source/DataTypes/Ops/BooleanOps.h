#pragma once

#include "BaseOps.h"
#include "../Values/Value.h"

namespace FPTL {
	namespace Runtime {

		// Implementation of operations on boolean values.
		class BooleanOps : public BaseOps
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("Bool");

			static BooleanOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value or this classes.
				static BooleanOps ops;
				return &ops;
			}

			static Value Create(const bool val = false)
			{
				auto res = Value(get());
				res.mBoolVal = val;
				return res;
			}

			static void ValueCheck(const Value & val)
			{
				if (val.ops != get())
				{
					throw std::runtime_error("Bool operation on not bool value.");
				}
			}

			TypeInfo Type(const Value& val) const override
			{
				(void)(val);
				return staticTypeInfo;
			}

			int64_t ToInt(const Value& val) const override { return val.mBoolVal; };

			double ToDouble(const Value& val) const override { return val.mBoolVal; };

			bool ToBool(const Value& val) const override { return val.mBoolVal; };

			bool Greater(const Value& left, const Value& right) const override
			{
				return (left.ToBool() > right.ToBool());
			}

			bool Equal(const Value& left, const Value& right) const override
			{
				return (left.ToBool() == right.ToBool());
			}

			bool Less(const Value& left, const Value& right) const override
			{
				return (left.ToBool() < right.ToBool());
			}

			// Вывод в поток.
			void Print(const Value& val, std::ostream & aStream) const override
			{
				aStream << val.ToBool();//? "true" : "false"
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				(void)(val);
				auto res = Value(get());
				aStream >> res.mBoolVal;
				return res;
			}
		};

	}
}
