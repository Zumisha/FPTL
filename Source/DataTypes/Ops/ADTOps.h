#pragma once

#include "BaseOps.h"
#include "DataTypes/Values/Value.h"
#include "DataTypes/Values/ADTValue.h"


namespace FPTL
{
	namespace Runtime
	{
		// Implementation of operations on abstract data types (ADT) values (boxed tuple).
		class ADTOps : public BaseOps
		{
			// TODO: определить функции Equal, Length
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("ADT");

			static ADTOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, ADTValue or this classes.
				static ADTOps ops;
				return &ops;
			}
					   
			static Value Create(const Constructor * ctor, const std::vector<Value>& values)
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, ADTValue or this classes.
				auto res = Value(get());
				res.mOtherVal = new ADTValue(ctor, values);
				return res;
			}
			static Value Create(const ADTValue & other)
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, ADTValue or this classes.
				auto res = Value(get());
				res.mOtherVal = new ADTValue(other);
				return res;
			}

			void Delete(const Value& val) const override
			{
				delete GetVal(val);
			}

			static ADTValue* GetVal(const Value& val)
			{
				return static_cast<ADTValue*>(val.mOtherVal);
			}

			static void ValueCheck(const Value & val)
			{
				if (val.Type().typeName != staticTypeInfo.typeName)
				{
					throw std::runtime_error("ADT operation on not ADT value.");
				}
			}

			TypeInfo Type(const Value& val) const override
			{
				return GetVal(val)->ctor->targetType();
			}

			void* Copy(const Value& val) const override
			{
				const auto& adtVal = GetVal(val);
				return new ADTValue(adtVal->ctor, adtVal->values);
			}

			void Print(const Value& val, std::ostream & aStream) const override
			{
				const auto adtVal = GetVal(val);
				const size_t arity = adtVal->ctor->arity();

				if (arity > 0)
				{
					aStream << "(";

					for (size_t i = 0; i < arity; ++i)
					{
						adtVal->values[i].Print(aStream);

						if (i + 1 < arity)
						{
							aStream << "*";
						}
					}

					aStream << ").";
				}

				aStream << adtVal->ctor->name();
			}
		};
	}
}
