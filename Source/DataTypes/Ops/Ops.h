#pragma once

#include "../TypeInfo.h"
#include "ADTOps.h"

namespace FPTL 
{
	namespace Runtime 
	{
		//-----------------------------------------------------------------------------
		class Ops;

		struct ADTValue;
		struct StringValue;
		struct ArrayValue;

		class ObjectMarker;

		// Variant для представления всех типов данных, кроме неопределенного значения.
		class DataValue
		{
			friend class DataBuilders;

		public:
			// Конструктор по умолчанию. Создает значение типа "неопределенность".
			DataValue();
			explicit DataValue(const Ops * aOps);
			DataValue(const DataValue & other)
			{
				*this = other;
			}

			const Ops * getOps() const;

		protected:
			const Ops * mOps;

			// Доступ к информационной части открыт для удобства.
		public:
			union
			{
				long long mIntVal;
				double mDoubleVal;
				ADTValue* mADT;
				StringValue* mString;
				ArrayValue* mArray;
			}; // size = max of members size 
		};

		// Неопределенное значение.
		class UndefinedValue : public DataValue
		{
			friend class DataBuilders;

			explicit UndefinedValue(const Ops * aOps)
				: DataValue(aOps)
			{}
		};

		// Интерфейс классов операций над типами данных
		class Ops
		{
		protected:
			virtual ~Ops() = default;
		public:
			virtual TypeInfo getType(const DataValue & aVal) const = 0;

			// Добавлять сюда методы по мере добавления новых типов.
			virtual const Ops * combine(const Ops * aOther) const = 0;
			virtual const Ops * withOps(class IntegerOps const * aOps) const = 0;
			virtual const Ops * withOps(class BooleanOps const * aOps) const = 0;
			virtual const Ops * withOps(class DoubleOps const * aOps) const = 0;
			virtual const Ops * withOps(class StringOps const * aOps) const = 0;
			virtual const Ops * withOps(const Ops * aOther) const = 0;

			// Преобразование типов.
			virtual long long toInt(const DataValue & aVal) const = 0;
			virtual double toDouble(const DataValue & aVal) const = 0;
			virtual StringValue * toString(const DataValue & aVal) const = 0;

			// Арифметические функции.
			virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue abs(const DataValue & aArg) const = 0;

			// Функции сравнения.
			virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const = 0;
			virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const = 0;

			// Метод для определения достижимых объектов при сборке мусора.
			virtual void mark(const DataValue & aVal, ObjectMarker * marker) const = 0;

			// Вывод в поток.
			virtual void print(const DataValue & aVal, std::ostream & aStream) const = 0;
			virtual void write(const DataValue & aVal, std::ostream & aStream) const = 0;
			virtual DataValue read(std::istream & aStream) const = 0;
		};

		// Базовая реализация операций. Кидает исключения на вызов любого метода.
		class BaseOps : public Ops
		{
		public:
			virtual ~BaseOps() = default;
			const Ops* withOps(const Ops * aOther) const override;
			const Ops* withOps(class StringOps const * aOther) const override;

			// Базисные функции.
			DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue abs(const DataValue & aVal) const override;

			// Функции сравнения.
			DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override;
			DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override;

			// Функции преобразования.
			long long toInt(const DataValue & aVal) const override;
			double toDouble(const DataValue & aVal) const override;
			StringValue * toString(const DataValue & aVal) const override;

			void mark(const DataValue & aVal, ObjectMarker * marker) const override;

			DataValue read(std::istream & aStream) const override;
			void write(const DataValue & aVal, std::ostream & aStream) const override;

			static std::runtime_error divideByZero();
			static std::runtime_error invalidOperation(const TypeInfo& valType, const std::string& funcName);
			std::runtime_error invalidOperation(const std::string& funcName) const;

			inline static const std::string invalidOpsMsg = "invalid operation on type ";
			inline static const std::string divideByZeroMsg = "divide by zero ";
		};

		// Конструкторы типов данных.
		class DataBuilders
		{
		public:
			static DataValue createVal(Ops * aOps);

			static DataValue createInt(long long aVal);
			static DataValue createDouble(double aVal);
			static DataValue createBoolean(bool aVal);

			static UndefinedValue createUndefinedValue();
			static DataValue createADT(ADTValue * aADTVal, Ops * aOps);
		};

	}
}
