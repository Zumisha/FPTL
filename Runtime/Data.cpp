#include <cassert>

#include "Data.h"
#include "Functions.h"

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
	invalidOperation();
	return nullptr;
}

Ops * BaseOps::withOps(StringOps const * aOther) const
{
	invalidOperation();
	return nullptr;
}

// Базисные функции.
DataValue BaseOps::add(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::sub(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::mul(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::div(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::mod(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::abs(const DataValue & aArg) const
{
	return invalidOperation();
}

// Функции сравнения.
DataValue BaseOps::equal(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::less(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

DataValue BaseOps::greater(const DataValue & aLhs, const DataValue & aRhs) const
{
	return invalidOperation();
}

// Функции преобразования.
int BaseOps::toInt(const DataValue & aVal) const
{
	invalidOperation();
	return 0;
}

double BaseOps::toDouble(const DataValue & aVal) const
{
	invalidOperation();
	return 0.0;
}

StringValue * BaseOps::toString(const DataValue & aVal) const
{
	invalidOperation();
	return nullptr;
}

void BaseOps::mark(const DataValue & aVal, ObjectMarker * marker) const
{
}

DataValue BaseOps::invalidOperation() const
{
	std::stringstream error;
	error << "invalid operation on type " << *getType(DataValue());
	throw std::runtime_error(error.str());
}

//-----------------------------------------------------------------------------

// Классы операций над типами данных.
class IntegerOps : public BaseOps
{
	IntegerOps()
	{}

public:
	static IntegerOps * get()
	{
		static IntegerOps ops;
		return &ops;
	}

	virtual Ops * combine(const Ops * aOther) const
	{
		return aOther->withOps(this);
	}

	virtual Ops * withOps(const IntegerOps * aOps) const
	{
		return get();
	}

	virtual Ops * withOps(const BooleanOps * aOps) const
	{
		invalidOperation();
		return nullptr;
	}

	virtual Ops * withOps(const DoubleOps * aOps) const
	{
		// FIXME: сделать возвращаемое значение const.
		return (Ops *)aOps;
	}

	virtual TypeInfo * getType(const DataValue &) const
	{
		static TypeInfo info("integer");
		return &info;
	}

	// Преобразования типов.
	virtual int toInt(const DataValue & aVal) const
	{
		return aVal.mIntVal;
	}

	virtual double toDouble(const DataValue & aVal) const
	{
		return (double)aVal.mIntVal;
	}

	// Базисные функции.
	virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createInt(aLhs.mIntVal + aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createInt(aLhs.mIntVal - aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createInt(aLhs.mIntVal * aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const
	{
		// TODO: деление на 0.
		return DataBuilders::createInt(aLhs.mIntVal / aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const
	{
		// TODO: деление на 0.
		return DataBuilders::createInt(aLhs.mIntVal % aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue abs(const DataValue & aArg) const
	{
		return DataBuilders::createInt(std::abs(aArg.mIntVal));
	}

	// Функции сравнения.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.mIntVal == aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.mIntVal < aRhs.getOps()->toInt(aRhs));
	}

	virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.mIntVal > aRhs.getOps()->toInt(aRhs));
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		aStream << aVal.mIntVal;
	}
};

class DoubleOps : public BaseOps
{
	DoubleOps()
	{}

public:
	static DoubleOps * get()
	{
		static DoubleOps ops;
		return &ops;
	}

	virtual Ops * combine(const Ops * aOther) const
	{
		return aOther->withOps(this);
	}

	virtual Ops * withOps(const IntegerOps * aOther) const
	{
		return get();
	}

	virtual Ops * withOps(const BooleanOps * aOther) const
	{
		invalidOperation();
		return nullptr;
	}

	virtual Ops * withOps(const DoubleOps * aOther) const
	{
		return get();
	}

	virtual TypeInfo * getType(const DataValue &) const
	{
		static TypeInfo info("double");
		return &info;
	}

	// Функции преобразования.
	virtual int toInt(const DataValue & aVal) const
	{
		return (int)aVal.mDoubleVal;
	}

	virtual double toDouble(const DataValue & aVal) const
	{
		return aVal.mDoubleVal;
	}

	// Базисные функции.
	virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) + aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) - aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) * aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) / aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createDouble(fmod(aLhs.getOps()->toDouble(aLhs), aRhs.getOps()->toDouble(aRhs)));
	}

	virtual DataValue abs(const DataValue & aArg) const
	{
		return DataBuilders::createDouble(std::abs(aArg.mDoubleVal));
	}

	// Функции сравнения.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) == aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) < aRhs.getOps()->toDouble(aRhs));
	}

	virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) > aRhs.getOps()->toDouble(aRhs));
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		aStream << aVal.mDoubleVal;
	}
};

class BooleanOps : public BaseOps
{
	BooleanOps()
	{}

public:
	static BooleanOps * get()
	{
		static BooleanOps ops;
		return &ops;
	}

	virtual Ops * combine(const Ops * aOther) const
	{
		return aOther->withOps(this);
	}

	virtual Ops * withOps(const IntegerOps * aOps) const
	{
		invalidOperation();
		return nullptr;
	}

	virtual Ops * withOps(const BooleanOps * aOps) const
	{
		return get();
	}

	virtual Ops * withOps(const DoubleOps * aOps) const
	{
		invalidOperation();
		return nullptr;
	}

	virtual TypeInfo * getType(const DataValue &) const
	{
		static TypeInfo info("boolean");
		return &info;
	}

	// Функции сравнения. Оба аргумента обязаны быть типа boolean.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(aLhs.mIntVal == aRhs.mIntVal);
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		aStream << (aVal.mIntVal ? "true" : "false");
	}
};

class UndefinedValueOps : public BaseOps
{
	UndefinedValueOps()
	{}

public:
	static UndefinedValueOps * get()
	{
		static UndefinedValueOps ops;
		return &ops;
	}

	virtual Ops * combine(const Ops * aOther) const
	{
		return get();
	}

	virtual Ops * withOps(const BooleanOps * aOps) const
	{
		return get();
	}

	virtual Ops * withOps(const IntegerOps * aOps) const
	{
		return get();
	}

	virtual Ops * withOps(const DoubleOps * aOps) const
	{
		return get();
	}

	virtual TypeInfo * getType(const DataValue &) const
	{
		static TypeInfo info("undefined");
		return &info;
	}

	// Функция сравнения со значением true определена.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		return DataBuilders::createBoolean(false);
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		aStream << "undefined";
	}
};

//-----------------------------------------------------------------------------
DataValue DataBuilders::createVal(Ops * aOps)
{
	DataValue val(aOps);
	return val;
}


DataValue DataBuilders::createInt(int aVal)
{
	DataValue val(IntegerOps::get());
	val.mIntVal = aVal;
	return val;
}

DataValue DataBuilders::createDouble(double aVal)
{
	DataValue val(DoubleOps::get());
	val.mDoubleVal = aVal;
	return val;
}

DataValue DataBuilders::createBoolean(bool aVal)
{
	DataValue val(BooleanOps::get());
	val.mIntVal = aVal;
	return val;
}

UndefinedValue DataBuilders::createUndefinedValue()
{
	return UndefinedValue(UndefinedValueOps::get());
}

DataValue DataBuilders::createADT(const ADTValue & aADTVal, Ops * aOps)
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

static int test = doTest();

//-----------------------------------------------------------------------------

} // Runtime
} // FPTL