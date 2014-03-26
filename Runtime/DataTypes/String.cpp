
#include "../Data.h"
#include "../String.h"

#include <cstring>
#include <cassert>

#include <boost/lexical_cast.hpp>

namespace FPTL {
namespace Runtime {

//-----------------------------------------------------------------------------

class StringOps : public Ops
{
	StringOps()
	{}

public:
	static StringOps * get()
	{
		static StringOps ops;
		return &ops;
	}

	virtual Ops * combine(const Ops * aOther) const
	{
		return (Ops *)aOther;
	}

	virtual Ops * withOps(const BooleanOps * aOps) const
	{
		throw invalidOperation("toBool");
	}

	virtual Ops * withOps(const IntegerOps * aOps) const
	{
		throw invalidOperation("toInt");
	}

	virtual Ops * withOps(const DoubleOps * aOps) const
	{
		throw invalidOperation("toDouble");
	}

	virtual TypeInfo * getType(const DataValue & aVal) const
	{
		static TypeInfo info("string");
		return &info;
	}

	// Преобразование типов.
	virtual int toInt(const DataValue & aVal) const
	{
		return boost::lexical_cast<int>(aVal.mString->str());
	}

	virtual double toDouble(const DataValue & aVal) const
	{
		return boost::lexical_cast<double>(aVal.mString->str());
	}

	virtual StringValue * toString(const DataValue & aVal) const
	{
		return aVal.mString;
	}

	// Арифметические функции.
	virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation("add");
	}

	virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation("sub");
	}

	virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation("mul");
	}

	virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation("div");
	}

	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation("mod");
	}

	virtual DataValue abs(const DataValue & aArg) const
	{
		throw invalidOperation("abs");
	}

	// Функции сравнения.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		auto lhs = aLhs.mString;
		auto rhs = aRhs.mString;
		return DataBuilders::createBoolean(
			lhs->length() == rhs->length() && std::equal(lhs->getChars(), lhs->getChars() + lhs->length(), rhs->getChars())
		);
	}

	virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const
	{
		auto lhs = aLhs.mString;
		auto rhs = aRhs.mString;
		return DataBuilders::createBoolean(
			std::lexicographical_compare(lhs->getChars(), lhs->getChars() + lhs->length(), rhs->getChars(), rhs->getChars() + rhs->length())
		);
	}

	virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const
	{
		auto lhs = aLhs.mString;
		auto rhs = aRhs.mString;
		return DataBuilders::createBoolean(
			std::lexicographical_compare(rhs->getChars(), rhs->getChars() + rhs->length(), lhs->getChars(), lhs->getChars() + lhs->length())
		);
	}

	virtual void mark(const DataValue & aVal, std::stack<Collectable *> & aMarkStack) const
	{
		aMarkStack.push(aVal.mString);
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		auto str = aVal.mString;
		std::copy(str->getChars(), str->getChars() + str->length(), std::ostreambuf_iterator<char>(aStream));
	}

private:
	std::exception invalidOperation(const char * aOpName) const
	{
		std::string msg = "invalid operation ";
		return std::runtime_error(msg + "'" + aOpName + "' on type string");
	}
};

struct StringData : public Collectable
{
	char * const value;
	const size_t length;

	StringData(size_t aLength) 
		: value((char *)(this) + sizeof(StringData)),
		length(aLength)
	{}

	virtual void mark(std::stack<Collectable *> & aMarkStack)
	{}

	virtual size_t size() const
	{
		return sizeof(*this) + length * sizeof(*value);
	}
};

//-----------------------------------------------------------------------------

char * StringValue::getChars() const
{
	return data->value + begin;
}

char * StringValue::contents() const
{
	return data->value;
}

int StringValue::length() const
{
	return end - begin;
}

void StringValue::mark(std::stack<Collectable *> & aMarkStack)
{
	aMarkStack.push(data);
}

size_t StringValue::size() const
{
	return sizeof(*this);
}

std::string StringValue::str() const
{
	return std::string(data->value + begin, data->value + end);
}

//-----------------------------------------------------------------------------

DataValue StringBuilder::create(SExecutionContext & aCtx, const std::string & aData)
{
	auto val = create(aCtx, aData.size());

	std::copy(aData.begin(), aData.end(), val.mString->getChars());

	return val;
}

DataValue StringBuilder::create(SExecutionContext & aCtx, int aSize)
{
	auto val = DataBuilders::createVal(StringOps::get());

	StringData * data = new (aCtx.alloc(sizeof(StringData) + aSize)) StringData(aSize);
	StringValue * str = new (aCtx.alloc(sizeof(StringValue))) StringValue();
	str->begin = 0;
	str->end = aSize;
	str->data = data;

	val.mString = str;
	return val;
}

DataValue StringBuilder::create(SExecutionContext & aCtx, const StringValue * aOther, int aBegin, int aEnd)
{
	StringValue * str = new (aCtx.alloc(sizeof(StringValue))) StringValue();
	str->data = aOther->data;
	str->begin = aBegin;
	str->end = aEnd;

	auto val = DataBuilders::createVal(StringOps::get());
	val.mString = str;
	return val;
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime
