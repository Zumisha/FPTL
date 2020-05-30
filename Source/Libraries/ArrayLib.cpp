#include <regex>
#include <random>
#include <string>

#include "ArrayLib.h"

#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/ArrayOps.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "DataTypes/Ops/StringOps.h"
#include "Utils/FileStreamHelper.h"
#include "DataTypes/Values/DataValue.h"
#include "DataTypes/Values/ArrayValue.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Создание массива.
			void CreateArray(SExecutionContext & aCtx)
			{
				const DataValue& sizeVal = aCtx.getArg(0);
				const DataValue& initialVal = aCtx.getArg(1);

				BaseOps::opsCheck(IntegerOps::get(), sizeVal);

				const int64_t intSize = sizeVal.getOps()->toInt(sizeVal);

				ArrayValue::nonPositiveSizeCheck(intSize);
				
				aCtx.push(ArrayValue::create(aCtx, static_cast<size_t>(intSize), initialVal));
			}

			// Чтение элемента из массива.
			void GetArrayElement(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);
				const DataValue& posVal = aCtx.getArg(1);

				BaseOps::opsCheck(ArrayOps::get(), arrVal);
				BaseOps::opsCheck(IntegerOps::get(), posVal);
				
				const int64_t intPos = posVal.getOps()->toInt(posVal);

				const size_t pos = ArrayValue::checkIndex(arrVal.mArray->length, intPos);

				aCtx.push(ArrayValue::uncheckedGet(arrVal, pos));
			}

			// Запись элемента в массив.
			void SetArrayElement(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);
				const DataValue& posVal = aCtx.getArg(1);
				const DataValue& val = aCtx.getArg(2);

				BaseOps::opsCheck(ArrayOps::get(), arrVal);
				BaseOps::opsCheck(IntegerOps::get(), posVal);
				BaseOps::typeCheck(arrVal.mArray->arrayData[0], val);
				
				const int64_t intPos = posVal.getOps()->toInt(posVal);
				const size_t pos = ArrayValue::checkIndex(arrVal.mArray->length, intPos);

				ArrayValue::uncheckedSet(const_cast<DataValue &>(arrVal), pos, val);

				aCtx.push(arrVal);
			}

			void GetArrayLength(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);

				BaseOps::opsCheck(ArrayOps::get(), arrVal);
				
				aCtx.push(DataBuilders::createInt(ArrayValue::getLen(arrVal)));
			}

			void ArrayConcat(SExecutionContext & aCtx)
			{
				const DataValue& first = aCtx.getArg(0);				
				
#if fptlDebugBuild
				BaseOps::opsCheck(ArrayOps::get(), first);
				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					BaseOps::typeCheck(first, aCtx.getArg(i));
				}
#endif

				const ArrayValue* firstArr = first.mArray;
				
				size_t len = firstArr->length;
				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					len += aCtx.getArg(i).mArray->length;
				}

				// Выделяем память в контролируемой куче под хранение массива.
				auto val = aCtx.heap().alloc<ArrayValue>(
					[firstArr, len](void* m) { return new(m) ArrayValue(len, firstArr->arrayData[0]); },
					sizeof(ArrayValue) + sizeof(firstArr->arrayData[0]) * len);
				// Создаем массив и заполняем его.
				val->arrayData = new (reinterpret_cast<char *>(val.ptr()) + sizeof(ArrayValue)) DataValue();
				
				size_t curPos = 0;
				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					const DataValue& arr = aCtx.getArg(i);
					for (size_t j = 0; j < arr.mArray->length; ++j)
					{
						val->arrayData[curPos + j] = arr.mArray->arrayData[j];
					}
					curPos += arr.mArray->length;
				}

				DataValue res = DataBuilders::createVal(ArrayOps::get());
				res.mArray = val.ptr();
				aCtx.push(res);
			}

			void ArraySum(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);

				BaseOps::opsCheck(ArrayOps::get(), arrVal);

				ArrayValue* arr = arrVal.mArray;

				const DataValue sum = arr->arrayData[0].getOps()->add(aCtx, arr->arrayData, arr->last());

				aCtx.push(sum);
			}

			void ArrayMax(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);

				BaseOps::opsCheck(ArrayOps::get(), arrVal);

				const ArrayValue* arr = arrVal.mArray;
				const size_t len = arr->length;

				const auto* const ops = arr->arrayData[0].getOps();
				auto max = arr->arrayData[0];
				size_t maxIndex = 0;
				for (size_t i = 1; i < len; ++i)
				{
					if (ops->less(max, arr->arrayData[i]))
					{
						max = arr->arrayData[i];
						maxIndex = i;
					}
				}

				aCtx.push(max);
				aCtx.push(DataBuilders::createInt(maxIndex));
			}

			void ArrayIndexOf(SExecutionContext & aCtx)
			{
				const DataValue& arrVal = aCtx.getArg(0);
				const DataValue& val = aCtx.getArg(1);
				
				BaseOps::opsCheck(ArrayOps::get(), arrVal);
				BaseOps::typeCheck(arrVal.mArray->arrayData[0], val);

				const ArrayValue* arr = arrVal.mArray;
				const size_t len = arr->length;
				const auto* const ops = val.getOps();
				size_t index = -1;
				for (size_t i = 0; i < len; ++i)
				{
					if (ops->equal(val, arr->arrayData[i]))
					{
						index = i;
						break;
					}
				}

				const int64_t res = static_cast<int64_t>(index);
				if (res < 0)
				{
					aCtx.push(DataBuilders::createUndefinedValue());					
				}
				else
				{
					aCtx.push(DataBuilders::createInt(index));
				}
			}
			
		} // anonymous namespace

		const std::map<std::string, std::pair<TFunction, bool>> functions =
		{
			// Работа с массивами.
			{ "arrayCreate", std::make_pair(&CreateArray, true) },
			{ "arrayGet", std::make_pair(&GetArrayElement, false) },
			{ "arraySet", std::make_pair(&SetArrayElement, false) },
			{ "arrayLen", std::make_pair(&GetArrayLength, false) },
			{ "arrayCat", std::make_pair(&ArrayConcat, true) },
			{ "arraySum", std::make_pair(&ArraySum, true) },
			{ "arrayMax", std::make_pair(&ArrayMax, true) },
			{ "arrayIndexOf", std::make_pair(&ArrayIndexOf, true) },
		};

		void ArrayLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
