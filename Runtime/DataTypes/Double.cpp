#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

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

DataValue DataBuilders::createDouble(double aVal)
{
	DataValue val(DoubleOps::get());
	val.mDoubleVal = aVal;
	return val;
}

}}
