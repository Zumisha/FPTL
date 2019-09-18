#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

class DoubleOps : public BaseOps
{
	DoubleOps()	= default;

public:
	static DoubleOps * get()
	{
		static DoubleOps ops;
		return &ops;
	}

	Ops * combine(const Ops * aOther) const override
	{
		return aOther->withOps(this);
	}

	Ops * withOps(const IntegerOps * aOther) const override
	{
		return get();
	}

	Ops * withOps(const BooleanOps * aOther) const override
	{
		invalidOperation(getType(DataValue()));
		return nullptr;
	}

	Ops * withOps(const DoubleOps * aOther) const override
	{
		return get();
	}

	TypeInfo getType(const DataValue &aVal) const override
	{
		static TypeInfo info("double");
		return info;
	}

	// Функции преобразования.
	long long toInt(const DataValue & aVal) const override
	{
		return static_cast<long long>(aVal.mDoubleVal);
	}

	double toDouble(const DataValue & aVal) const override
	{
		return aVal.mDoubleVal;
	}

	// Базисные функции.
	DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) + aRhs.getOps()->toDouble(aRhs));
	}

	DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) - aRhs.getOps()->toDouble(aRhs));
	}

	DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) * aRhs.getOps()->toDouble(aRhs));
	}

	DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createDouble(aLhs.getOps()->toDouble(aLhs) / aRhs.getOps()->toDouble(aRhs));
	}

	DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createDouble(fmod(aLhs.getOps()->toDouble(aLhs), aRhs.getOps()->toDouble(aRhs)));
	}

	DataValue abs(const DataValue & aArg) const override
	{
		return DataBuilders::createDouble(std::abs(aArg.mDoubleVal));
	}

	// Функции сравнения.
	DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) == aRhs.getOps()->toDouble(aRhs));
	}

	DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) < aRhs.getOps()->toDouble(aRhs));
	}

	DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createBoolean(aLhs.getOps()->toDouble(aLhs) > aRhs.getOps()->toDouble(aRhs));
	}

	// Вывод в поток.
	void print(const DataValue & aVal, std::ostream & aStream) const override
	{
		aStream << aVal.mDoubleVal;
	}

	void write(const DataValue & aVal, std::ostream & aStream) const override
	{
		aStream << aVal.mDoubleVal;
	}

	DataValue read(std::istream & aStream) const override
	{
		DataValue val(get());
		aStream >> val.mDoubleVal;
		return val;
	}
};

DataValue DataBuilders::createDouble(const double aVal)
{
	DataValue val(DoubleOps::get());
	val.mDoubleVal = aVal;
	return val;
}

}}
