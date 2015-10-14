#pragma once

#include <stack>
#include <sstream>
#include <functional>

#include "Types.h"
#include "ADT.h"

namespace FPTL { namespace Runtime {

//-----------------------------------------------------------------------------
class Ops;

struct ADTValue;
struct StringValue;
struct ArrayValue;

// Variant для представления всех типов данных, кроме неопределенного значения.
class DataValue
{
	friend class DataBuilders;

public:
	// Конструктор по умолчани. Создает значение типа "неопределенность".
	DataValue();
	DataValue(const DataValue & other)
	{
		*this = other;
	}

	const Ops * getOps() const;

protected:
	DataValue(const Ops * aOps);

	const Ops * mOps;

// Доступ к информационной части открыт для удобства.
public:
	union
	{
		int mIntVal;
		double mDoubleVal;
		ADTValue mADT;
		StringValue * mString;
		ArrayValue * mArray;
	};
};

// Неопределенное значение.
class UndefinedValue : public DataValue
{
	friend class DataBuilders;

	UndefinedValue(const Ops * aOps)
		: DataValue(aOps)
	{}
};

// Интерфейс классов операций над типами данных
class Ops
{
public:
	virtual TypeInfo * getType(const DataValue & aVal) const = 0;
	
	// Добавлять сюда методы по мере добавления новых типов.
	virtual Ops * combine(const Ops * aOther) const = 0;
	virtual Ops * withOps(class IntegerOps const * aOps) const = 0;
	virtual Ops * withOps(class BooleanOps const * aOps) const = 0;
	virtual Ops * withOps(class DoubleOps const * aOps) const = 0;

	// Преобразование типов.
	virtual int toInt(const DataValue & aVal) const = 0;
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

	// Метод для определения достижимых обхектов при сборке мусора.
	virtual void mark(const DataValue & aVal, std::stack<class Collectable *> & aMarkStack) const = 0;

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const = 0;
};

// Базовая реализация операций. Кидает исключения на вызов любого метода.
class BaseOps : public Ops
{
public:
	// Базисные функции.
	virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue abs(const DataValue & aArg) const;

	// Функции сравнения.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const;
	virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const;

	// Функции преобразования.
	virtual int toInt(const DataValue & aVal) const;
	virtual double toDouble(const DataValue & aVal) const;
	virtual StringValue * toString(const DataValue & aVal) const;

	virtual void mark(const DataValue & aVal, std::stack<class Collectable *> & aMarkStack) const;

protected:
	DataValue invalidOperation() const;
};

// Конструкторы типов данных.
class DataBuilders
{
public:
	static DataValue createVal(Ops * aOps);

	static DataValue createInt(int aVal);
	static DataValue createDouble(double aVal);
	static DataValue createBoolean(bool aVal);

	static UndefinedValue createUndefinedValue();
	static DataValue createADT(const ADTValue & mADT, Ops * aOps);
};

} // Runtime
} // FPTL
