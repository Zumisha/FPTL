#pragma once

#include <string>
#include <utility>

#include <boost/lexical_cast.hpp>

#include "BaseOps.h"
#include "../Values/Value.h"
#include "../Values/StringValue.h"

namespace FPTL {
	namespace Runtime {

		// Implementation of operations on string values.
		class StringOps : public BaseOps
		{
		public:
			inline static const TypeInfo staticTypeInfo = TypeInfo("String");

			static StringOps* get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, StringValue or this classes.
				static StringOps ops;
				return &ops;
			}

			static Value Create()
			{
				auto res = Value(get());
				res.mOtherVal = new StringValue();
				return res;
			}

			static Value Create(const size_t aSize)
			{
				auto res = Value(get());
				res.mOtherVal = new StringValue(aSize);
				return res;
			}

			static Value Create(const std::string& aData)
			{
				auto res = Value(get());
				res.mOtherVal = new StringValue(aData);
				return res;
			}

			void Delete(const Value& val) const override
			{
				const auto str = static_cast<StringValue*>(val.mOtherVal);
				delete str;
			}

			static void ValueCheck(const Value & val)
			{
				if (val.ops != get())
				{
					throw std::runtime_error("String operation on not string value.");
				}
			}

			TypeInfo Type(const Value& val) const override
			{
				(void)(val);
				return staticTypeInfo;
			}

			bool Greater(const Value& left, const Value& right) const override
			{
				const std::string& lStr = static_cast<StringValue*>(left.mOtherVal)->mVal;
				const std::string& rStr = static_cast<StringValue*>(right.mOtherVal)->mVal;
				return (lStr > rStr);
			}

			bool Equal(const Value& left, const Value& right) const override
			{
				const std::string& lStr = static_cast<StringValue*>(left.mOtherVal)->mVal;
				const std::string& rStr = static_cast<StringValue*>(right.mOtherVal)->mVal;
				return (lStr == rStr);
			}

			bool Less(const Value& left, const Value& right) const override
			{
				const std::string& lStr = static_cast<StringValue*>(left.mOtherVal)->mVal;
				const std::string& rStr = static_cast<StringValue*>(right.mOtherVal)->mVal;
				return (lStr < rStr);
			}

			Value Read(const Value& val, std::istream & aStream) const override
			{
				(void)(val);
				std::string str;
				aStream >> str;
				return Create(str);
			}

			// Вывод в поток.
			void Print(const Value& val, std::ostream & aStream) const override
			{
				aStream << static_cast<StringValue*>(val.mOtherVal)->mVal;
			}

			void* Copy(const Value& val) const override { return new StringValue(std::string(static_cast<StringValue*>(val.mOtherVal)->mVal)); }

			size_t Length(const Value& val) const override { return static_cast<StringValue*>(val.mOtherVal)->mVal.size(); }
		};

	}
}
