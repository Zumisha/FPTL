#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

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

	virtual TypeInfo getType(const DataValue &) const
	{
		static TypeInfo info("boolean");
		return info;
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

DataValue DataBuilders::createBoolean(bool aVal)
{
	DataValue val(BooleanOps::get());
	val.mIntVal = aVal;
	return val;
}

}}