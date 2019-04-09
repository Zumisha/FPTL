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

UndefinedValue DataBuilders::createUndefinedValue()
{
	return UndefinedValue(UndefinedValueOps::get());
}

}}