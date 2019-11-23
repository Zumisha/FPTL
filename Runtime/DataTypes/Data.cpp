#include <cassert>
#include <sstream>

#include "Data.h"

namespace FPTL {
namespace Runtime {

//------------------------------------------------------------------------------
const Ops * DataValue::getOps() const
{
	return mOps;
}

DataValue::DataValue()
	: mOps(nullptr)
{
}

DataValue::DataValue(const Ops * aOps)
	: mOps(aOps)
{
}

//-----------------------------------------------------------------------------
Ops * BaseOps::withOps(const Ops * aOther) const
{
	invalidOperation(getType(DataValue()));
	return nullptr;
}

Ops * BaseOps::withOps(StringOps const * aOther) const
{
	invalidOperation(getType(DataValue()));
	return nullptr;
}

// Базисные функции.
DataValue BaseOps::add(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::sub(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::mul(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::div(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::mod(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::abs(const DataValue & aVal) const
{
	return invalidOperation(aVal.getOps()->getType(aVal));
}

// Функции сравнения.
DataValue BaseOps::equal(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::less(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

DataValue BaseOps::greater(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation(aRhs.getOps()->getType(aRhs));
}

// Функции преобразования.
long long BaseOps::toInt(const DataValue & aVal) const
{
	invalidOperation(aVal.getOps()->getType(aVal));
	return 0;
}

double BaseOps::toDouble(const DataValue & aVal) const
{
	invalidOperation(aVal.getOps()->getType(aVal));
	return 0.0;
}

StringValue * BaseOps::toString(const DataValue & aVal) const
{
	invalidOperation(aVal.getOps()->getType(aVal));
	return nullptr;
}

void BaseOps::write(const class DataValue& aVal, std::ostream& aStream) const
{
	invalidOperation(aVal.getOps()->getType(aVal));	
}

DataValue BaseOps::read(std::istream & aStream) const
{
	invalidOperation(this->getType(*reinterpret_cast<DataValue const*>(this)));
	return DataValue();
}

void BaseOps::mark(const DataValue & aVal, ObjectMarker * marker) const
{
}

DataValue BaseOps::invalidOperation(const TypeInfo & valType)
{
	std::stringstream error;
	error << "invalid operation on type " << valType << ".";
	throw std::runtime_error(error.str());
}

//-----------------------------------------------------------------------------

DataValue DataBuilders::createVal(Ops * aOps)
{
	DataValue val(aOps);
	return val;
}

DataValue DataBuilders::createADT(ADTValue* aADTVal, Ops * aOps)
{
	DataValue val(aOps);
	val.mADT = aADTVal;
	return val;
}

int doTest()
{
	auto v1 = DataBuilders::createInt(10);
	auto v2 = DataBuilders::createInt(20);

	// Тест целочисленных операций.
	assert(v1.getOps());

	assert(v1.getOps()->add(v1, v2).mIntVal == 30);
	assert(v1.getOps()->sub(v1, v2).mIntVal == -10);
	assert(v1.getOps()->mul(v1, v2).mIntVal == 200);
	assert(v2.getOps()->div(v2, v1).mIntVal == 2);
	assert(v1.getOps()->mod(v1, v2).mIntVal == 10);

	assert(v1.getOps()->abs(DataBuilders::createInt(-10)).mIntVal >= 0);

	assert(v1.getOps()->equal(v1, v1).mIntVal);
	assert(v1.getOps()->less(v1, v2).mIntVal);
	assert(v2.getOps()->greater(v2, v1).mIntVal);

	// Тест операций с плавающей точкой.
	auto v3 = DataBuilders::createDouble(10.0);
	auto v4 = DataBuilders::createDouble(20.0);

	assert(v3.getOps());

	assert(v3.getOps()->add(v3, v4).mDoubleVal == 30.0);
	assert(v3.getOps()->sub(v3, v4).mDoubleVal == -10.0);
	assert(v3.getOps()->mul(v3, v4).mDoubleVal == 200.0);
	assert(v4.getOps()->div(v4, v3).mDoubleVal == 2.0);
	assert(v3.getOps()->mod(v3, v4).mDoubleVal == 10.0);

	assert(v1.getOps()->equal(v1, v1).mIntVal);
	assert(v1.getOps()->less(v1, v2).mIntVal);
	assert(v2.getOps()->greater(v2, v1).mIntVal);

	assert(v3.getOps()->abs(DataBuilders::createDouble(-10.0)).mDoubleVal >= 0);

	// Тест смешанных операций.
	assert(v1.getOps()->combine(v4.getOps())->add(v1, v4).mDoubleVal == 30.0);
	assert(v1.getOps()->combine(v4.getOps())->sub(v1, v4).mDoubleVal == -10.0);
	assert(v4.getOps()->combine(v1.getOps())->mul(v1, v4).mDoubleVal == 200.0);
	assert(v1.getOps()->combine(v4.getOps())->div(v4, v1).mDoubleVal == 2.0);
	assert(v4.getOps()->combine(v1.getOps())->mod(v1, v4).mDoubleVal == 10.0);

	assert(v1.getOps()->combine(v3.getOps())->equal(v1, v3).mIntVal);
	assert(v1.getOps()->combine(v4.getOps())->less(v1, v4).mIntVal);
	assert(v4.getOps()->combine(v1.getOps())->greater(v4, v1).mIntVal);

	// Тест значение "неопределенность".
	auto uv = DataBuilders::createUndefinedValue();
	assert(!uv.getOps()->equal(uv, DataBuilders::createBoolean(true)).mIntVal);
	assert(!uv.getOps()->equal(uv, DataBuilders::createBoolean(false)).mIntVal);

	assert(!v1.getOps()->combine(uv.getOps())->equal(v1, uv).mIntVal);
	assert(!uv.getOps()->combine(v1.getOps())->equal(uv, v1).mIntVal);

	return -1;
}

#ifdef _DEBUG
static int test = doTest();
#endif

//-----------------------------------------------------------------------------

} // Runtime
} // FPTL