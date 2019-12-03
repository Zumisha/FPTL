#pragma once

#include "BaseOps.h"
#include "../Values/Value.h"
#include "../Values/ArrayValue.h"

namespace FPTL {
	namespace Runtime {

		// Implementation of operations on array values.
		class ArrayOps : public BaseOps
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("Array");

			static ArrayOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, ArrayValue or this classes.
				static ArrayOps ops;
				return &ops;
			}

			static Value Create(const size_t aLength, const Value& initial)
			{
				auto res = Value(get());
				res.mOtherVal = new ArrayValue(aLength, initial, InitType(initial));
				return res;
			}

			static Value Create(const std::vector<Value>& val)
			{
				auto res = Value(get());
				res.mOtherVal = new ArrayValue(val, InitType(val[0]));
				return res;
			}

			void Delete(const Value& val) const override
			{
				delete GetVal(val);
			}

			static ArrayValue* GetVal(const Value& val)
			{
				return static_cast<ArrayValue*>(val.mOtherVal);
			}

			static void IndexCheck(const Value & val, const int64_t index)
			{
				if (index < 0 || static_cast<size_t>(index) >= val.Length())
				{
					throw std::invalid_argument("Array index is out of range!");
				}
			}

			static void SizeCheck(const int64_t size)
			{
				if (size <= 0)
				{
					throw std::invalid_argument("The size of the array must be greater than zero!");
				}
			}

			static void ValueCheck(const Value & arr)
			{
				if (arr.ops != get())
				{
					throw std::runtime_error("Array operation on not array value.");
				}
			}

			TypeInfo Type(const Value& val) const override { return GetVal(val)->type;}

			size_t Length(const Value& val) const override { return GetVal(val)->mVal.size(); }

			void* Copy(const Value& val) const override
			{
				const auto& arrVal = GetVal(val);
				return new ArrayValue(arrVal->mVal, arrVal->type);
			}
		
			void Print(const Value& val, std::ostream & aStream) const override
			{
				ArrayValue* arrVal = GetVal(val);
				const std::string delimiter = (arrVal->mVal[0].ops == get()) ? "\n" : " ";

				aStream << "[";
				for (size_t i = 0; i < arrVal->mVal.size(); ++i)
				{
					const auto& elVal = arrVal->mVal[i];
					elVal.Print(aStream);

					if (i < arrVal->mVal.size() - 1) aStream << delimiter;
				}
				aStream << "]";
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				ArrayValue* arrVal = GetVal(val);
				std::vector<Value> res = arrVal->mVal;
				for (auto& el : res)
				{
					el = std::move(el.Read(aStream));
				}
				return Create(res);
			}

			Value& GetRef(const Value& val, const size_t index) override { return GetVal(val)->mVal[index]; }

		private:
			static TypeInfo InitType(const Value& initial)
			{
				const TypeInfo& elType = initial.Type();
				TypeInfo info(staticTypeInfo);
				info.addParameter(elType);
				return info;
			}
		};
	}
}