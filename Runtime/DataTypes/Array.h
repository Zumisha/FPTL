#pragma once

#include "Data.h"
#include "../Context.h"
#include "Runtime/CollectedHeap.h"

namespace FPTL
{
namespace Runtime
{

//-----------------------------------------------------------------------------
// Внутреннее представление массива.
struct ArrayValue : public Collectable
{
	const Ops * ops;
	const size_t length;

	DataValue * arrayData;

	ArrayValue(const Ops * aOps, const int aLength)
		: ops(aOps), length(aLength)
	{
	}

	// Конструктор массива.
	static DataValue create(SExecutionContext & ctx, int size, const DataValue & initial);

	// Получение элемента массива.
	static DataValue get(const DataValue & arr, int pos);

	// Установка значения элемента массива.
	static void set(DataValue & arr, int pos, const DataValue & val);

	static size_t byteSize(int length);

	static size_t getLen(const DataValue & arr);

	static DataValue concat(SExecutionContext & ctx);

	static void arrayValueCheck(const DataValue & arr);

private:
	static std::runtime_error outOfRange()
	{
		return std::runtime_error("Array index is out of range.");
	}
	static std::runtime_error notArrayValue()
	{
		return std::runtime_error("Invalid operation on not array value.");
	}
};

}} // FPTL::Runtime