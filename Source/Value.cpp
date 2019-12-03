#include "DataTypes/Values/Value.h"
#include "DataTypes/Ops/BaseOps.h"

namespace FPTL {
	namespace Runtime {
		Value::Value()
		{
			ops = nullptr;
		}

		Value::Value(Ops* ops) : ops(ops)
		{
		}

		Value::Value(const Value& val)
		{
			ops = val.ops;
			//mOtherVal = val.mOtherVal;
			mOtherVal = val.ops->Copy(val);
		}

		Value& Value::operator=(const Value& val)
		{
			ops = val.ops;
			//mOtherVal = val.mOtherVal;
			mOtherVal = val.ops->Copy(val);
			return *this;
		}

		Value::Value(Value&& val) noexcept
		{
			//std::swap(*this, val);
			//if (val.ops != nullptr)
			{
				ops = val.ops;
				// It will copy any union type
				mOtherVal = val.mOtherVal;
				val.ops = BaseOps::get();
				//val.ops->makeUndefined(val);
			}
		}

		Value& Value::operator=(Value&& val) noexcept
		{
			//if (val.ops != nullptr)
			{
				ops = val.ops;
				// It will copy any union type
				mOtherVal = val.mOtherVal;
				val.ops = BaseOps::get();
				//val.ops->makeUndefined(val);
			}
			return *this;
		}

		Value::~Value()
		{
			ops->Delete(*this);
		}

		TypeInfo Value::Type() const
		{
			return ops->Type(*this);
		}

		bool Value::GreaterThan(const Value& other) const
		{
			return ops->Greater(*this, other);
		}

		bool Value::EqualTo(const Value& other) const
		{
			return ops->Equal(*this, other);
		}

		bool Value::LessThan(const Value& other) const
		{
			return ops->Less(*this, other);
		}

		Value Value::Read(std::istream& aStream) const
		{
			return ops->Read(*this, aStream);
		}

		void Value::Print(std::ostream& aStream) const
		{
			ops->Print(*this, aStream);
		}

		Value Value::Copy() const
		{
			Value res = Value(ops);
			res.mOtherVal = ops->Copy(*this);
			return res;
		}

		size_t Value::Length() const
		{
			return ops->Length(*this);
		}

		int64_t Value::ToInt() const
		{
			return ops->ToInt(*this);
		}

		double Value::ToDouble() const
		{
			return ops->ToDouble(*this);
		}

		std::string Value::ToString() const
		{
			std::stringstream strStream;
			ops->Print(*this, strStream);
			return strStream.str();
		}

		bool Value::ToBool() const
		{
			return ops->ToBool(*this);
		}

		Value Value::operator+(const Value& other) const
		{
			return ops->Add(*this, other);
		}

		Value Value::operator-(const Value& other) const
		{
			return ops->Sub(*this, other);
		}

		Value Value::operator*(const Value& other) const
		{
			return ops->Mul(*this, other);
		}

		Value Value::operator/(const Value& other) const
		{
			return ops->Div(*this, other);
		}

		Value Value::operator%(const Value& other) const
		{
			return ops->Mod(*this, other);
		}

		Value& Value::operator[](const size_t index) const
		{
			return ops->GetRef(*this, index);
		}

		Value Value::Abs() const
		{
			return ops->Abs(*this);
		}
	}
}
