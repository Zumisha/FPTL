#include <ostream>
#include "Data.h"

namespace FPTL {
namespace Runtime {

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

	Ops * combine(const Ops * aOther) const override
	{
		return get();
	}

	Ops * withOps(const BooleanOps * aOps) const override
	{
		return get();
	}

	Ops * withOps(const IntegerOps * aOps) const override
	{
		return get();
	}

	Ops * withOps(const DoubleOps * aOps) const override
	{
		return get();
	}

	TypeInfo getType(const DataValue &aVal) const override
	{
		static TypeInfo info("undefined");
		return info;
	}

	// Функция сравнения со значением true определена.
	DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		return DataBuilders::createBoolean(false);
	}

	// Вывод в поток.
	void print(const DataValue & aVal, std::ostream & aStream) const override
	{
		aStream << "undefined";
	}
};

UndefinedValue DataBuilders::createUndefinedValue()
{
	return UndefinedValue(UndefinedValueOps::get());
}

}}