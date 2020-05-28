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

			static DataValue copy(SExecutionContext & ctx, const DataValue & arr);

			static void arrayValueCheck(const DataValue & arr);

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

			void mark(const DataValue & aVal, ObjectMarker * marker) const override;

			// Вывод содержимого массива.
			void print(const DataValue & aVal, std::ostream & aStream) const override;

			void write(const DataValue & aVal, std::ostream & aStream) const override;

			DataValue read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const override;
		};
	}
}
