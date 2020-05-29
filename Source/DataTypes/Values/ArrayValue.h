#pragma once

#include <string>

#include "DataTypes/TypeInfo.h"
#include "GC/CollectedHeap.h"

namespace FPTL::Runtime
{	
		// Внутреннее представление массива.
		struct ArrayValue : Collectable
		{
		public:
			const size_t length;
			const TypeInfo type;

			DataValue* arrayData;

			ArrayValue(const size_t aLength, const DataValue & initial)
				: length(aLength), type(CreateType(initial)), arrayData(nullptr)
			{
			}

			const DataValue* last() const
			{
				return &arrayData[length - 1];
			}

			// Конструктор массива.
			static DataValue create(SExecutionContext & ctx, size_t length, const DataValue & initial);

			// Получение элемента массива.
			static DataValue uncheckedGet(const DataValue & arr, size_t pos);

			// Установка значения элемента массива.
			static void uncheckedSet(const DataValue & arr, size_t pos, const DataValue & val);

			static size_t getLen(const DataValue & arr);

			static DataValue copy(SExecutionContext & ctx, const DataValue & arr);

			static size_t checkIndex(const size_t arrSize, const int64_t index)
			{
				const size_t checked = static_cast<size_t>(index);
				if (index < 0 || checked >= arrSize)
				{
					std::stringstream error;
					error << "attempt to get the element with index " << index << " in array of size " << arrSize;
					throw std::runtime_error(error.str());
				}
				return checked;
			}

			static std::string overflowSizeMsg(const long long size, const std::string& initType)
			{
				std::stringstream error;
				error << "array size is too large (" << size << " elements of type " << initType << ")";
				return error.str();
			}

			static void nonPositiveSizeCheck(const int64_t size)
			{
				if (size <= 0)
				{
					std::stringstream error;
					error << "size of the array must be greater than zero (actual: " << size << ")";
					throw std::invalid_argument(error.str());
				}
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
			static TypeInfo CreateType(const DataValue & initial);
		};
}
