#include "DataTypes/Values/ArrayValue.h"
#include "DataTypes/Ops/ArrayOps.h"

namespace FPTL
{
	namespace Runtime
	{
		DataValue ArrayValue::create(SExecutionContext & ctx, size_t length, const DataValue& initial)
		{
			// Выделяем память в контролируемой куче под хранение массива.
			auto val = ctx.heap().alloc<ArrayValue>(
				[length, initial](void* m) { return new(m) ArrayValue(length, initial); },
				sizeof(ArrayValue) + sizeof(initial) * length);

			// Создаем массив и заполняем его начальным значением.
			val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();

			if (initial.getOps() == ArrayOps::get())
			{
				val->arrayData[0] = initial;
				for (size_t i = 1; i < length; ++i)
				{
					val->arrayData[i] = ArrayValue::copy(ctx, initial);
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

		DataValue ArrayValue::uncheckedGet(const DataValue & arr, size_t pos)
		{
			return arr.mArray->arrayData[pos];
		}

		void ArrayValue::uncheckedSet(const DataValue & arr, const size_t pos, const DataValue & val)
		{
			arr.mArray->arrayData[pos] = val;
		}

		size_t ArrayValue::getLen(const DataValue & arr)
		{
			return arr.mArray->length;
		}

		TypeInfo ArrayValue::CreateType(const DataValue& initial)
		{
			const auto elType = initial.getOps()->getType(initial);
			TypeInfo info(ArrayOps::typeName, elType);
			return info;
		}
	}
}
