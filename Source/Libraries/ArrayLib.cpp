#include <regex>
#include <random>
#include <string>
#include <queue>

#include "ArrayLib.h"

#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/ArrayOps.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "DataTypes/Ops/StringOps.h"
#include "Utils/FileStreamHelper.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Создание массива.
			void CreateArray(SExecutionContext & aCtx)
			{
				const auto sizeVal = aCtx.getArg(0);
				const auto& initialVal = aCtx.getArg(1);

#if fptlDebugBuild
				if (sizeVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(sizeVal.getOps()->getType(sizeVal), __func__);
#endif

				const auto intSize = sizeVal.getOps()->toInt(sizeVal);

#if fptlDebugBuild
				if (intSize <= 0) throw std::invalid_argument(ArrayValue::negativeSizeMsg(intSize));
#endif

				const auto size = static_cast<size_t>(intSize);
				aCtx.push(ArrayValue::create(aCtx, size, initialVal));
			}

			// Чтение элемента из массива.
			void GetArrayElement(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				const auto & posVal = aCtx.getArg(1);

#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal);
				if (posVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(posVal.getOps()->getType(posVal), __func__);
#endif
				
				const size_t pos = posVal.getOps()->toInt(posVal);

#if fptlDebugBuild
				if (pos >= arrVal.mArray->length)
					throw std::runtime_error(ArrayValue::badIndexMsg(arrVal.mArray->length, pos));
#endif

				aCtx.push(ArrayValue::get(arrVal, pos));
			}

			// Запись элемента в массив.
			void SetArrayElement(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				const auto & posVal = aCtx.getArg(1);
				const auto & val = aCtx.getArg(2);

#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal);
				if (posVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(posVal.getOps()->getType(posVal), __func__);
#endif

				const size_t pos = posVal.getOps()->toInt(posVal);

#if fptlDebugBuild
				if (pos >= arrVal.mArray->length)
					throw std::runtime_error(ArrayValue::badIndexMsg(arrVal.mArray->length, pos));
#endif

				ArrayValue::set(const_cast<DataValue &>(arrVal), pos, val);

				aCtx.push(arrVal);
			}

			void GetArrayLength(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				
#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal);
#endif
				
				aCtx.push(DataBuilders::createInt(ArrayValue::getLen(arrVal)));
			}

			void ArrayConcat(SExecutionContext & aCtx)
			{
				const auto& first = aCtx.getArg(0);
				
#if fptlDebugBuild
				ArrayValue::arrayValueCheck(first);
				const auto* const firstOps = first.getOps();
				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					const auto& arg = aCtx.getArg(i);
					ArrayValue::arrayValueCheck(arg);
					if (firstOps != arg.getOps())
						throw BaseOps::invalidOperation(firstOps->getType(first), arg.getOps()->getType(arg), __func__);
				}
#endif

				auto* firstArr = first.mArray;
				const auto type = firstArr->type;
				size_t len = firstArr->length;

				for (size_t i = 1; i < aCtx.argNum; ++i)
				{
					auto* const rArr = aCtx.getArg(i).mArray;
#if fptlDebugBuild
					if (rArr->type != type)
					{
						throw std::runtime_error(ArrayValue::concatErrMsg(std::string(type), std::string(rArr->type)));
					}
#endif
					len += rArr->length;
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
					const auto& arr = aCtx.getArg(i);
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

			void ArrayDot(SExecutionContext & aCtx)
			{
				const auto & arrVal1 = aCtx.getArg(0);
				const auto & arrVal2 = aCtx.getArg(1);
				
#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal1);
				ArrayValue::arrayValueCheck(arrVal2);
#endif
				
				ArrayValue * arr1Val = arrVal1.mArray;
				ArrayValue * arr2Val = arrVal2.mArray;
				const auto arr1Len = arr1Val->length;
				
#if fptlDebugBuild
				const auto arr1Type = arr1Val->type;
				const auto arr2Len = arr2Val->length;
				const auto arr2Type = arr2Val->type;
				if (arr1Type != arr2Type)
				{
					std::stringstream error;
					error << "Cannot find dot product of an array of type " << arr1Type << " and an array of type " << arr2Type;
					throw std::runtime_error(error.str());
				}
				if (arr1Len != arr2Len)
				{
					std::stringstream error;
					error << "Cannot find dot product of an array of size " << arr1Len << " and an array of size " << arr2Len;
					throw std::runtime_error(error.str());
				}
#endif
				
				/*class DataValueComparator
				{
				public:
					bool operator() (const DataValue& p1, const DataValue& p2) const
					{
						return p1.getOps()->greater(p1, p2);
					}
				};

				std::priority_queue< DataValue, std::vector<DataValue>, DataValueComparator > pq;

				for (size_t i = 0; i < arr1Len; ++i)
				{
					pq.push(arr1Val->arrayData[i].getOps()->sub(arr1Val->arrayData[i], arr2Val->arrayData[i]));
				}

				while (pq.size() > 1)
				{
					auto res = pq.top();
					pq.pop();
					res = res.getOps()->add(res, pq.top());
					pq.pop();
					pq.push(res);
				}*/

				const auto* const ops = arr1Val->arrayData[0].getOps();
				auto dot = ops->mul(arr1Val->arrayData[0], arr2Val->arrayData[0]);
				for (size_t i = 1; i < arr1Len; ++i)
				{
					dot = ops->add(dot, ops->mul(arr1Val->arrayData[i], arr2Val->arrayData[i]));
				}				
				
				aCtx.push(dot);
			}

			void ArraySum(SExecutionContext & aCtx)
			{
				const auto & arrVal1 = aCtx.getArg(0);
				
#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal1);
#endif

				ArrayValue * val = arrVal1.mArray;
				const auto len = val->length;

				const auto* const ops = val->arrayData[0].getOps();
				auto sum = val->arrayData[0];
				for (size_t i = 1; i < len; ++i)
				{
					sum = ops->add(sum, val->arrayData[i]);
				}

				aCtx.push(sum);
			}
			
		} // anonymous namespace

		const std::map<std::string, TFunction> functions =
		{
			// Работа с массивами.
			{"arrayCreate", &CreateArray},
			{ "arrayGet", &GetArrayElement },
			{ "arraySet", &SetArrayElement },
			{ "arrayLen", &GetArrayLength },
			{ "arrayCat", &ArrayConcat },
			{ "arrayDot", &ArrayDot },
			{ "arraySum", &ArraySum },
		};

		void ArrayLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
