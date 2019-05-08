#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

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

	virtual TypeInfo getType(const DataValue &) const
	{
		static TypeInfo info("int");
		return info;
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
		const int Right = aRhs.getOps()->toInt(aRhs);
		if (Right == 0) throw std::overflow_error("Divide by zero");
		return DataBuilders::createInt(aLhs.mIntVal / Right);
	}

	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const
	{
		const int Right = aRhs.getOps()->toInt(aRhs);
		if (Right == 0) throw std::overflow_error("Divide by zero");
		return DataBuilders::createInt(aLhs.mIntVal % Right);
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

DataValue DataBuilders::createInt(int aVal)
{
	DataValue val(IntegerOps::get());
	val.mIntVal = aVal;
	return val;
}

}}
