#pragma once

#include "../TypeInfo.h"
#include "DataTypes/Values/DataValue.h"
#include "DataTypes/Values/UndefinedValue.h"

namespace FPTL 
{
	namespace Runtime 
	{
		struct SExecutionContext;
		struct ADTValue;
		struct StringValue;
		struct ArrayValue;

		class ObjectMarker;

		// Интерфейс классов операций над типами данных
		class Ops
		{
		protected:
			virtual ~Ops() = default;
		public:
			virtual const std::string& getTypeName() const = 0;
			virtual TypeInfo getType(const DataValue& aVal) const = 0;

			// Преобразование типов.
			virtual long long toInt(const DataValue& aVal) const = 0;
			virtual double toDouble(const DataValue& aVal) const = 0;

			// Арифметические функции.
			virtual DataValue add(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual DataValue add(const SExecutionContext & aCtx, const DataValue* first, const DataValue* last) const = 0;
			virtual DataValue sub(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual DataValue sub(const SExecutionContext & aCtx, const DataValue* first, const DataValue* last) const = 0;
			virtual DataValue mul(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual DataValue mul(const SExecutionContext & aCtx, const DataValue* first, const DataValue* last) const = 0;
			virtual DataValue div(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual DataValue div(const SExecutionContext & aCtx, const DataValue* first, const DataValue* last) const = 0;
			virtual DataValue mod(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual DataValue mod(const SExecutionContext & aCtx, const DataValue* first, const DataValue* last) const = 0;
			virtual DataValue abs(const DataValue& aArg) const = 0;

			// Функции сравнения.
			virtual bool equal(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual bool less(const DataValue& aLhs, const DataValue& aRhs) const = 0;
			virtual bool greater(const DataValue& aLhs, const DataValue& aRhs) const = 0;

			// Метод для определения достижимых объектов при сборке мусора.
			virtual void mark(const DataValue& aVal, ObjectMarker* marker) const = 0;

			// Вывод в поток.
			virtual void print(const DataValue& aVal, std::ostream& aStream) const = 0;
			virtual void rawPrint(const DataValue& aVal, std::ostream& aStream) const = 0;
			virtual DataValue read(const DataValue& aVal, const SExecutionContext& aCtx, std::istream & aStream) const = 0;
		};

		// Базовая реализация операций. Кидает исключения на вызов любого метода.
		class BaseOps : public Ops
		{
		public:
			virtual ~BaseOps() = default;

			// Базисные функции.
			DataValue add(const DataValue& aLhs, const DataValue& aRhs) const override;
			DataValue add(const SExecutionContext& aCtx, const DataValue* first, const DataValue* last) const override;
			DataValue sub(const DataValue& aLhs, const DataValue& aRhs) const override;
			DataValue sub(const SExecutionContext& aCtx, const DataValue* first, const DataValue* last) const override;
			DataValue mul(const DataValue& aLhs, const DataValue& aRhs) const override;
			DataValue mul(const SExecutionContext& aCtx, const DataValue* first, const DataValue* last) const override;
			DataValue div(const DataValue& aLhs, const DataValue& aRhs) const override;
			DataValue div(const SExecutionContext& aCtx, const DataValue* first, const DataValue* last) const override;
			DataValue mod(const DataValue& aLhs, const DataValue& aRhs) const override;
			DataValue mod(const SExecutionContext& aCtx, const DataValue* first, const DataValue* last) const override;
			DataValue abs(const DataValue& aVal) const override;

			// Функции сравнения.
			bool equal(const DataValue& aLhs, const DataValue& aRhs) const override;
			bool less(const DataValue& aLhs, const DataValue& aRhs) const override;
			bool greater(const DataValue& aLhs, const DataValue& aRhs) const override;

			// Функции преобразования.
			int64_t toInt(const DataValue& aVal) const override;
			double toDouble(const DataValue& aVal) const override;

			void mark(const DataValue& aVal, ObjectMarker* marker) const override;

			DataValue read(const DataValue& aVal, const SExecutionContext& aCtx, std::istream& aStream) const override;

			static std::runtime_error divideByZero();
			static void opsCheck(const Ops* ops, const DataValue& val);
			static void typeCheck(const DataValue& refVal, const DataValue& val);
			
			inline static const std::string invalidOpsMsg = "invalid operation on type \"";
			inline static const std::string divideByZeroMsg = "divide by zero ";

		private:
			static std::runtime_error invalidValueType(const std::string& refType, const std::string& valType);
			std::runtime_error invalidOperation(const std::string& funcName) const;
		};

		// Конструкторы типов данных.
		class DataBuilders
		{
		public:
			static DataValue createVal(Ops* aOps);

			static DataValue createInt(int64_t aVal);
			static DataValue createDouble(double aVal);
			static DataValue createBoolean(bool aVal);
			static DataValue createTime(int64_t aVal);
			//static DataValue createFile(std::FILE& aVal);

			static UndefinedValue createUndefinedValue();
			static DataValue createADT(ADTValue* aADTVal, Ops* aOps);
		};

	}
}
