#pragma once

#include "Data.h"
#include "Context.h"

namespace FPTL
{
namespace Runtime
{

//-----------------------------------------------------------------------------
// Внутреннее представление массива.
struct ArrayValue : public Collectable
{
	const Ops * ops;
	const int length;

	DataValue * arrayData;

	ArrayValue(const Ops * aOps, const int aLength)
		: ops(aOps), length(aLength)
	{
	}

	virtual void mark(std::stack<Collectable *> & aMarkStack)
	{
		for (int i = 0; i < length; ++i)
		{
			ops->mark(arrayData[i], aMarkStack);
		}
	}

	virtual size_t size() const
	{
		return 0;
	}

	// Конструктор массива.
	static DataValue create(SExecutionContext & ctx, int size, const DataValue & initial);

	// Получение элемента массива.
	static DataValue get(const DataValue & arr, int pos);

	// Установка значения элемента массива.
	static void set(DataValue & arr, int pos, const DataValue & val);

private:
	static std::runtime_error outOfRange()
	{
		return std::runtime_error("Array index is out of range.");
	}
};

}} // FPTL::Runtime