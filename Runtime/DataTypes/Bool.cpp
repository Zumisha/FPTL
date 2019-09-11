#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

class BooleanOps : public BaseOps
{
	BooleanOps() = default;

public:
	static BooleanOps * get()
	{
		static BooleanOps ops;
		return &ops;
	}

	Ops * combine(const Ops * aOther) const override
	{
		return aOther->withOps(this);
	}

	Ops * withOps(const IntegerOps * aOps) const override
	{
		invalidOperation();
		return nullptr;
	}

	Ops * withOps(const BooleanOps * aOps) const override
	{
		return get();
	}

	Ops * withOps(const DoubleOps * aOps) const override
	{
		invalidOperation();
		return nullptr;
	}

	TypeInfo getType(const DataValue &) const override
	{
		static TypeInfo info("boolean");
		return info;
	}

	// Функции сравнения. Оба аргумента обязаны быть типа boolean.
	DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createBoolean(aLhs.mIntVal == aRhs.mIntVal);
	}

	// Вывод в поток.
	void print(const DataValue & aVal, std::ostream & aStream) const override
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