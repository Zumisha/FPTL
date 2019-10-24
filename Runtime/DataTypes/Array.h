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
	const TypeInfo type;

	DataValue * arrayData;

	ArrayValue(const size_t aLength, const DataValue & initial)
		: ops(initial.getOps()), length(aLength), type(CreateType(initial)), arrayData(nullptr)
	{
	}

	// Конструктор массива.
	static DataValue create(SExecutionContext & ctx, size_t length, const DataValue & initial);

	// Получение элемента массива.
	static DataValue get(const DataValue & arr, size_t pos);

	// Установка значения элемента массива.
	static void set(DataValue & arr, size_t pos, const DataValue & val);

	static size_t getLen(const DataValue & arr);

	static DataValue concat(SExecutionContext & ctx);

	static DataValue copy(SExecutionContext & ctx, const DataValue & arr);

	static DataValue dot(SExecutionContext & ctx, const DataValue & arr1, const DataValue & arr2);

	static void arrayValueCheck(const DataValue & arr);

	static void fromString(DataValue & arr, std::istream & aStream);

private:
	static TypeInfo CreateType(const DataValue & initial)
	{
		const auto elType = initial.getOps()->getType(initial);
		TypeInfo info("array", elType);
		return info;
	}

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