#include <sstream>
#include <queue>
#include <boost/format.hpp>

#include "Array.h"
#include "../GarbageCollector.h"

namespace FPTL {
namespace Runtime {
//-----------------------------------------------------------------------------
// Операции над массивами.
class ArrayOps : public BaseOps
{
	ArrayOps() = default;

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
		if (marker->markAlive(aVal.mArray, sizeof(ArrayValue) + sizeof(aVal.mArray->arrayData[0]) * aVal.mArray->length))
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
		ArrayValue * arr = aVal.mArray;

		std::string delimiter;
		if (arr->arrayData[0].getOps() == ArrayOps::get())
		{
			delimiter = ",\n";
		}
		else
		{
			delimiter = ", ";
		}

		aStream << "[";
		for (size_t i = 0; i < arr->length; ++i)
		{
			DataValue & val = arr->arrayData[i];
			val.getOps()->print(val, aStream);

			if (i < arr->length - 1)
			{
				aStream << delimiter;
			}
		}		
		aStream << "]";
	}

	void write(const DataValue & aVal, std::ostream & aStream) const override
	{
		ArrayValue::arrayValueCheck(aVal);

		ArrayValue * arrVal = aVal.mArray;
		for (size_t i = 0; i < arrVal->length; ++i)
		{
			arrVal->arrayData[0].getOps()->write(arrVal->arrayData[i], aStream);
			if (i < arrVal->length - 1)
			{
				aStream << " ";
			}
		}
	}

	DataValue read(std::istream & aStream) const override
	{
		throw invalidOperation("read");
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
	// Выделяем память в контролируемой куче под хранение массива.
	auto val = ctx.heap().alloc<ArrayValue>(
		[length, initial](void * m) { return new(m) ArrayValue(length, initial); },
		sizeof(ArrayValue) + sizeof(initial) * length);

	// Создаем массив и заполняем его начальным значением.
	val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();
	if (initial.getOps() == ArrayOps::get())
	{
		val->arrayData[0] = initial;
		for (size_t i = 1; i < length; ++i)
		{
			val->arrayData[i] = copy(ctx, initial);
		}
	}
	else
	{
		std::fill_n(val->arrayData, length, initial);		
	}

	DataValue res = DataBuilders::createVal(ArrayOps::get());
	res.mArray = val.ptr();
	return res;
}


DataValue ArrayValue::copy(SExecutionContext & ctx, const DataValue & arr)
{
	// Выделяем память в контролируемой куче под хранение массива.
	auto val = ctx.heap().alloc<ArrayValue>(
		[arr](void * m) { return new(m) ArrayValue(arr.mArray->length, arr.mArray->arrayData[0]); },
		sizeof(ArrayValue) + sizeof(arr.mArray->arrayData[0]) * arr.mArray->length);

	val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();

	if (arr.mArray->arrayData[0].getOps() == ArrayOps::get())
	{
		for (size_t i = 0; i < arr.mArray->length; ++i)
		{
			val->arrayData[i] = copy(ctx, arr.mArray->arrayData[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < arr.mArray->length; ++i)
		{
			val->arrayData[i] = arr.mArray->arrayData[i];
		}
	}

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

DataValue ArrayValue::dot(SExecutionContext & ctx, const DataValue & arr1, const DataValue & arr2)
{
	ArrayValue * arr1Val = arr1.mArray;
	ArrayValue * arr2Val = arr2.mArray;

	const auto arr1Type = arr1Val->type;
	const auto arr2Type = arr2Val->type;

	if (arr1Type != arr2Type)
	{
		std::stringstream error;
		error << "Cannot find dot product of an array of type " << arr1Type << " and an array of type " << arr2Type;
		throw std::runtime_error(error.str());
	}

	const auto arr1Len = arr1Val->length;
	const auto arr2Len = arr2Val->length;

	if (arr1Len != arr2Len)
	{
		std::stringstream error;
		error << "Cannot find dot product of an array of size " << arr1Len << " and an array of size " << arr2Len;
		throw std::runtime_error(error.str());
	}

	class DataValueComparator
	{
	public:
		bool operator() (const DataValue& p1, const DataValue& p2) const
		{
			return p1.getOps()->greater(p1, p2).mIntVal;
		}
	};

	std::priority_queue < DataValue, std::vector<DataValue>, DataValueComparator > pq;

	for (size_t i = 0; i < arr1Len; ++i)
	{
		pq.push(arr1Val->arrayData[i].getOps()->sub(arr1Val->arrayData[i], arr2Val->arrayData[i]));
	}

	while (pq.size()>1)
	{
		auto res = pq.top();
		pq.pop();
		res = res.getOps()->add(res, pq.top());
		pq.pop();
		pq.push(res);
	}

	return pq.top();
}

//-----------------------------------------------------------------------------
DataValue ArrayValue::get(const DataValue & arr, size_t pos)
{
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

size_t ArrayValue::getLen(const DataValue & arr)
{
	return arr.mArray->length;
}

DataValue ArrayValue::concat(SExecutionContext & ctx)
{
	for (size_t i = 0; i < ctx.argNum; ++i)
	{
		arrayValueCheck(ctx.getArg(i));
	}

	auto firstArr = ctx.getArg(0).mArray;
	const auto type = firstArr->type;
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
		sizeof(ArrayValue) + sizeof(firstArr->arrayData[0]) * len);

	// Создаем массив и заполняем его.
	val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();
	size_t curPos = 0;
	for (size_t i = 0; i < ctx.argNum; ++i)
	{
		const auto& arr = ctx.getArg(i);
		for (size_t j = 0; j < arr.mArray->length; ++j)
		{
			val->arrayData[curPos+j] = arr.mArray->arrayData[j];
		}
		curPos += arr.mArray->length;
	}

	DataValue res = DataBuilders::createVal(ArrayOps::get());
	res.mArray = val.ptr();
	return res;
}

void ArrayValue::fromString(DataValue & arr, std::istream &aStream)
{
	const auto arrVal = arr.mArray;
	for (size_t i = 0; i < arrVal->length; ++i)
	{
		if (arrVal->arrayData[i].getOps() == ArrayOps::get())
		{
			fromString(arrVal->arrayData[i], aStream);
		}
		else
		{
			arrVal->arrayData[i] = arrVal->arrayData[i].getOps()->read(aStream);
		}
	}
}

//-----------------------------------------------------------------------------

}} // FPTL::Runtime