#include <boost/format.hpp>

#include "Array.h"
#include "../GarbageCollector.h"
#include "../CollectedHeap.h"
#include <sstream>

namespace FPTL
{
namespace Runtime 
{
//-----------------------------------------------------------------------------
// Операции над массивами.
class ArrayOps : public BaseOps
{
public:
	static ArrayOps * get()
	{
		static ArrayOps ops;
		return &ops;
	}

	TypeInfo getType(const DataValue & aVal) const override
	{		
		return aVal.mArray->type;
	}
	
	// Добавлять сюда методы по мере добавления новых типов.
	Ops * combine(const Ops * aOther) const override
	{
		throw invalidOperation("combine");
	}

	Ops * withOps(class IntegerOps const * aOps) const override
	{
		throw invalidOperation("toInt");
	}

	Ops * withOps(class BooleanOps const * aOps) const override
	{
		throw invalidOperation("toBoolean");
	}

	Ops * withOps(class DoubleOps const * aOps) const override
	{
		throw invalidOperation("toDouble");
	}

	void mark(const DataValue & aVal, ObjectMarker * marker) const override
	{
		if (marker->markAlive(aVal.mArray, ArrayValue::byteSize(aVal.mArray->length)))
		{
			for (size_t i = 0; i < aVal.mArray->length; i++)
			{
				marker->addChild(&aVal.mArray->arrayData[i]);
			}
		}
	}

	// Вывод содержимого массива.
	void print(const DataValue & aVal, std::ostream & aStream) const override
	{
		aStream << "[";
		ArrayValue * arr = aVal.mArray;
		for (size_t i = 0; i < arr->length; ++i)
		{
			DataValue & val = arr->arrayData[i];
			val.getOps()->print(val, aStream);

			if (i < arr->length - 1)
			{
				aStream << ", ";
			}
		}		
		aStream << "]";
	}

private:
	static std::runtime_error invalidOperation(const std::string & name)
	{
		return std::runtime_error(boost::str(boost::format("Invalid operation on array: %1%.") % name));
	}
};

//-----------------------------------------------------------------------------
DataValue ArrayValue::create(SExecutionContext & ctx, size_t length, const DataValue & initial)
{
	if (length <= 0)
	{
		throw std::exception("Array length must be positive integer number.");
	}

	// Выделяем память в контролируемой куче под хранение массива.
	auto val = ctx.heap().alloc<ArrayValue>(
		[length, initial](void * m) { return new(m) ArrayValue(length, initial); },
		byteSize(length)
	);

	// Создаем массив и заполняем его начальным значением.
	val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();
	std::fill_n(val->arrayData, length, initial);

	DataValue res = DataBuilders::createVal(ArrayOps::get());
	res.mArray = val.ptr();
	return res;
}

void ArrayValue::arrayValueCheck(const DataValue & arr)
{
	if (arr.getOps() != ArrayOps::get())
	{
		throw notArrayValue();
	}
}

//-----------------------------------------------------------------------------
DataValue ArrayValue::get(const DataValue & arr, size_t pos)
{
	arrayValueCheck(arr);

	ArrayValue * trg = arr.mArray;

	if (pos >= trg->length)
	{
		throw outOfRange();
	}

	return trg->arrayData[pos];
}

//-----------------------------------------------------------------------------
void ArrayValue::set(DataValue & arr, size_t pos, const DataValue & val)
{
	arrayValueCheck(arr);

	ArrayValue * trg = arr.mArray;

	if (pos >= trg->length)
	{
		throw outOfRange();
	}

	const auto valType = val.getOps()->getType(val);
	const auto arrType = trg->ops->getType(trg->arrayData[0]);
	if (valType != arrType)
	{
		std::stringstream error;
		error << "cannot assign element of type " << valType << " to an array of type " << arrType << ".";
		throw std::runtime_error(error.str());
	}

	trg->arrayData[pos] = val;
}

size_t ArrayValue::byteSize(size_t length)
{
	return sizeof(ArrayValue) + sizeof(DataValue) * length;
}

size_t ArrayValue::getLen(const DataValue & arr)
{
	arrayValueCheck(arr);
	return arr.mArray->length;
}

DataValue ArrayValue::concat(SExecutionContext & ctx)
{
	for (size_t i = 0; i < ctx.argNum; ++i)
	{
		arrayValueCheck(ctx.getArg(i));
	}

	auto firstArr = ctx.getArg(0).mArray;
	const auto type = firstArr->ops->getType(firstArr->arrayData[0]);
	size_t len = firstArr->length;

	for (size_t i = 1; i < ctx.argNum; ++i)
	{
		const auto rArr = ctx.getArg(i).mArray;
		if (rArr->type != type)
		{
			std::stringstream error;
			error << "Cannot concat an array of type " << type << " with an array of type " << rArr->type;
			throw std::runtime_error(error.str());
		}
		len += rArr->length;
	}

	// Выделяем память в контролируемой куче под хранение массива.
	auto val = ctx.heap().alloc<ArrayValue>(
		[firstArr, len](void * m) { return new(m) ArrayValue(len, firstArr->arrayData[0]); },
		byteSize(len)
		);

	// Создаем массив и заполняем его.
	val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();
	size_t curPos = 0;
	for (size_t i = 0; i < ctx.argNum; ++i)
	{
		const auto& arr = ctx.getArg(i);
		memcpy(val->arrayData + curPos, arr.mArray->arrayData, arr.mArray->length * sizeof(ArrayValue));
		curPos += arr.mArray->length;
	}

	DataValue res = DataBuilders::createVal(ArrayOps::get());
	res.mArray = val.ptr();
	return res;
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime