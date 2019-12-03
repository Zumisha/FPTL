#pragma once

#include <sstream>

#include "Ops.h"
#include "../Values/Value.h"

namespace FPTL {
	namespace Runtime {

		// Basic implementation of basic operations (undefined). 
		// In order not to process invalid operations in operations of each type.
		class BaseOps : public Ops
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("Undefined");

			static BaseOps* get()
			{
				// It breaks if there are errors in the Ops, Value or this classes or cyclic dependence.
				static BaseOps ops;
				return &ops;
			}

			static Value Create()
			{
				// It breaks if there are errors in the Ops, Value or this classes or cyclic dependence.
				return Value(get());
			}

			void Delete(const Value& val) const override {
				(void)(val);
			}

			void makeUndefined(Value& val) const override
			{
				val.ops = get();
				val.mOtherVal = nullptr;
			}

			TypeInfo Type(const Value& val) const override
			{
				(void)(val);
				return staticTypeInfo;
			}

			bool Greater(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return false;
			}

			bool Equal(const Value& left, const Value& right) const override
			{
				return left.Type() == right.Type();
			}

			bool Less(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return false;
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				(void)(aStream);
				InvalidOperation(val.Type()); 
				return Create();
			}

			void Print(const Value& val, std::ostream & aStream) const override
			{
				aStream << val.Type();
			}

			void* Copy(const Value& val) const override
			{
				return val.mOtherVal;
			}

			size_t Length(const Value& val) const override
			{
				InvalidOperation(val.Type()); 
				return 0;
			}

			bool ToBool(const Value& val) const override
			{
				InvalidOperation(val.Type()); 
				return false;
			}

			int64_t ToInt(const Value& val) const override
			{
				InvalidOperation(val.Type()); 
				return 0;
			}

			double ToDouble(const Value& val) const override
			{
				InvalidOperation(val.Type()); 
				return 0;
			}

			Value Add(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return Create();
			}

			Value Sub(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return Create();
			}

			Value Mul(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return Create();
			}

			Value Div(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return Create();
			}

			Value Mod(const Value& left, const Value& right) const override
			{
				InvalidOperation(left.Type(), right.Type()); 
				return Create();
			}

			Value& GetRef(const Value& val, const size_t index) override
			{
				InvalidOperation(val.Type()); 
				return GetRef(val, index);
			}

			Value Abs(const Value& val) const override
			{
				InvalidOperation(val.Type()); 
				return Create();
			};

		private:
			static void InvalidOperation(const TypeInfo& valType)
			{
				std::stringstream error;
				error << "Invalid operation on type " << valType << ".";
				throw std::runtime_error(error.str());
			}

			static void InvalidOperation(const TypeInfo& firstType, const TypeInfo& secondType)
			{
				std::stringstream error;
				error << "Invalid operation on types " << firstType << " and " << secondType << ".";
				throw std::runtime_error(error.str());
			}
		};
	}
}
