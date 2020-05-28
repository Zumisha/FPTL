#include <sstream>
#include <queue>
#include <boost/format.hpp>
#include <algorithm>

#include "ArrayOps.h"
#include "GC/GarbageCollector.h"
#include "UndefinedOps.h"

namespace FPTL
{
	namespace Runtime
	{
			void ArrayOps::mark(const DataValue & aVal, ObjectMarker * marker) const
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
			void  ArrayOps::print(const DataValue & aVal, std::ostream & aStream) const
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

				size_t i = 0;
				aStream << "[";
				for (; i < std::min(arr->length, 5llu); ++i)
				{
					if (i > 0)
					{
						aStream << delimiter;
					}
					
					DataValue & val = arr->arrayData[i];
					val.getOps()->print(val, aStream);
				}
				if (arr->length - i > 5)
				{
					i = arr->length - 5;
					aStream << delimiter << "... ";
				}
				for (; i < arr->length; ++i)
				{
					aStream << delimiter;
					
					DataValue & val = arr->arrayData[i];
					val.getOps()->print(val, aStream);
				}
				aStream << "]";
			}

			void  ArrayOps::write(const DataValue & aVal, std::ostream & aStream) const
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

			DataValue ArrayOps::read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const
			{
				auto* const arrVal = aVal.mArray;
				for (size_t i = 0; i < arrVal->length; ++i)
				{
					arrVal->arrayData[i] = arrVal->arrayData[i].getOps()->read(arrVal->arrayData[i], aCtx, aStream);
				}
				return aVal;
			}

		//-----------------------------------------------------------------------------
		DataValue ArrayValue::create(SExecutionContext & ctx, size_t length, const DataValue& initial)
		{
			if (((SIZE_MAX - sizeof(ArrayValue)) / length) < sizeof(initial))
				throw std::runtime_error(overflowSizeMsg(length, std::string(initial.getOps()->getType(initial))));

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
				throw BaseOps::invalidOperation(arr.getOps()->getType(arr), "toArray");
			}
		}

		//-----------------------------------------------------------------------------
		DataValue ArrayValue::get(const DataValue & arr, size_t pos)
		{
			return arr.mArray->arrayData[pos];
		}

		//-----------------------------------------------------------------------------
		void ArrayValue::set(const DataValue & arr, const size_t pos, const DataValue & val)
		{
			ArrayValue * trg = arr.mArray;

			if (pos >= trg->length)
			{
				throw std::runtime_error(badIndexMsg(trg->length, pos));
			}

			const auto valType = val.getOps()->getType(val);
			const auto arrType = trg->ops->getType(trg->arrayData[0]);
			if (valType != arrType)
			{
				std::stringstream error;
				error << "cannot assign element of type " << valType << " to an array of type " << arrType << ".";
				throw std::runtime_error(assignErrMsg(std::string(valType), std::string(arrType)));
			}

			trg->arrayData[pos] = val;
		}

		size_t ArrayValue::getLen(const DataValue & arr)
		{
			return arr.mArray->length;
		}
	}
}
