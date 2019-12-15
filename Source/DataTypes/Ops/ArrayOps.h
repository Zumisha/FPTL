#pragma once

#include <string>

#include "Ops.h"
#include "Evaluator/Context.h"
#include "GC/CollectedHeap.h"
#include "../TypeInfo.h"

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

			DataValue* arrayData;

			ArrayValue(const size_t aLength, const DataValue & initial)
				: ops(initial.getOps()), length(aLength), type(CreateType(initial)), arrayData(nullptr)
			{
			}

			// Конструктор массива.
			static DataValue create(SExecutionContext & ctx, size_t length, const DataValue & initial);

			// Получение элемента массива.
			static DataValue get(const DataValue & arr, size_t pos);

			// Установка значения элемента массива.
			static void set(const DataValue & arr, size_t pos, const DataValue & val);

			static size_t getLen(const DataValue & arr);

			static DataValue concat(const SExecutionContext & ctx);

			static DataValue copy(SExecutionContext & ctx, const DataValue & arr);

			static DataValue dot(SExecutionContext & ctx, const DataValue & arr1, const DataValue & arr2);

			static void arrayValueCheck(const DataValue & arr);

			static void fromString(const DataValue & arr, std::istream & aStream);

			inline static const std::string typeName = "array";

			static std::string badIndexMsg(const long long size, const long long index)
			{
				std::stringstream error;
				error << "attempt to get the element with index " << index << " in array of size " << size;
				return error.str();
			}

			static std::string overflowSizeMsg(const long long size, const std::string& initType)
			{
				std::stringstream error;
				error << "array size is too large (" << size << " elements of type " << initType << ")";
				return error.str();
			}

			static std::string negativeSizeMsg(const long long size)
			{
				std::stringstream error;
				error << "size of the array must be greater than zero (actual " << size << ")";
				return error.str();
			}

			static std::string assignErrMsg(const std::string& lType, const std::string& rType)
			{
				std::stringstream error;
				error << "cannot assign element of type " << lType << " to an array of type " << rType << ".";
				return error.str();
			}

			static std::string concatErrMsg(const std::string& lType, const std::string& rType)
			{
				std::stringstream error;
				error << "cannot concat an array of type " << lType << " with an array of type " << rType;
				return error.str();
			}

		private:
			static TypeInfo CreateType(const DataValue & initial)
			{
				const auto elType = initial.getOps()->getType(initial);
				TypeInfo info(typeName, elType);
				return info;
			}
		};
	}
}
