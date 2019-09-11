#include <sstream>
#include <utility>

#include "DataTypes/Data.h"
#include "DataTypes/ADT.h"
#include "CollectedHeap.h"
#include "GarbageCollector.h"
#include "Context.h"

namespace FPTL {
namespace Runtime {

//-------------------------------------------------------------------------------

struct DataValueArray : public Collectable
{
	DataValue values[];

	static size_t size(int n)
	{
		return sizeof(DataValueArray) + n * sizeof(DataValue);
	}
};

const DataValue & ADTValue::operator[](size_t i) const
{
	return values->values[i];
}

DataValue & ADTValue::operator[](size_t i)
{
	return values->values[i];
}

size_t ADTValue::size() const
{
	return DataValueArray::size(ctor->arity());
}

//-------------------------------------------------------------------------------

// Операции с абстрактным типом данных.
class ADTOps : public Ops
{
	ADTOps()
	{}

public:
	static ADTOps * get()
	{
		static ADTOps ops;
		return &ops;
	}

	TypeInfo getType(const DataValue & aVal) const override
	{
		return *aVal.mADT->ctor->targetType();
	}
	
	// Добавлять сюда методы по мере добавления новых типов.
	Ops * combine(const Ops * aOther) const override
	{
		throw invalidOperation();
	}

	Ops * withOps(class Ops const * aOps) const override
	{
		throw invalidOperation();
	}

	Ops * withOps(class IntegerOps const * aOps) const override
	{
		throw invalidOperation();
	}

	Ops * withOps(class BooleanOps const * aOps) const override
	{
		throw invalidOperation();
	}

	Ops * withOps(class DoubleOps const * aOps) const override
	{
		throw invalidOperation();
	}

	Ops * withOps(class StringOps const * aOps) const override
	{
		throw invalidOperation();
	}

	// Преобразование типов.
	long long toInt(const DataValue & aVal) const override
	{
		throw invalidOperation();
	}

	double toDouble(const DataValue & aVal) const override
	{
		throw invalidOperation();
	}

	StringValue * toString(const DataValue & aVal) const override
	{
		throw invalidOperation();
	}

	// Арифметические функции.
	DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue abs(const DataValue & aArg) const override
	{
		throw invalidOperation();
	}

	// Функции сравнения.
	DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		// TODO: возможно эту функцию можно определить.
		throw invalidOperation();
	}

	DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override
	{
		throw invalidOperation();
	}

	void mark(const DataValue & aVal, ObjectMarker * marker) const override
	{
		if (marker->markAlive(aVal.mADT->values, aVal.mADT->size()))
		{
			for (int i = 0; i < aVal.mADT->ctor->arity(); i++)
			{
				marker->addChild(&(*aVal.mADT)[i]);
			}
		}
	}

	// Вывод в поток.
	void print(const DataValue & aVal, std::ostream & aStream) const override
	{
		auto val = aVal.mADT;
		int arity = val->ctor->arity();

		if (arity > 0)
		{
			aStream << "(";

			for (auto i = 0; i < arity; ++i)
			{
				(*val)[i].getOps()->print((*val)[i], aStream);

				if (i + 1 < arity)
				{
					aStream << "*";
				}
			}
		
			aStream << ").";
		}

		aStream << val->ctor->name();
	}

private:
	static std::runtime_error invalidOperation()
	{
		std::stringstream str;
		str << "invalid operation on abstract data type";
		return std::runtime_error(str.str());
	}
};

//-------------------------------------------------------------------------------
Constructor::Constructor(std::string aConstructorName, const std::string & aTypeName,
                         std::vector<TypeInfo> aRefType, const std::vector<std::string> & aParameters)
	: mConstructorName(std::move(aConstructorName)),
	mTypeName(aTypeName),
	mReferenceType(std::move(aRefType)),
	mTargetType(aTypeName)
{
	for (auto &param : aParameters)
	{
		mTargetType.typeParameters.emplace_back(param, TypeInfo(param));
	}
}

//-------------------------------------------------------------------------------
Constructor::~Constructor()
{
}

//-------------------------------------------------------------------------------
void Constructor::execConstructor(SExecutionContext & aCtx) const
{
	// Проверяем соответствие типов входного кортежа сигнатуре конструктора.
	int argNum = 0;
	std::unordered_map<std::string, struct TypeInfo> params;

	int ar = arity();
	auto values = aCtx.heap().alloc<DataValueArray>(DataValueArray::size(ar));

	for (auto i = 0; i < ar; ++i)
	{
		auto & arg = aCtx.getArg(i);

		if (!TypeInfo::matchType(arg.getOps()->getType(arg), &mReferenceType[i], params))
		{
			throw std::runtime_error("type mismatch. Actual:" + arg.getOps()->getType(arg).typeName + " Expected: " + mReferenceType[i].typeName + ".");
		}

		values->values[i] = arg;
	}

	// С типами все ок, cоздаем абстрактный тип данных.
	aCtx.push(DataBuilders::createADT(new ADTValue(this, values.ptr()), ADTOps::get()));
}

//-------------------------------------------------------------------------------
void Constructor::execDestructor(SExecutionContext & aCtx) const
{
	// Проверяем что значение было создано именно этим деструктором.
	auto & arg = aCtx.getArg(0);

	if (arg.getOps() == ADTOps::get())
	{
		const auto adt = arg.mADT;

		if (adt->ctor == this)
		{
			// Разворачиваем кортеж.
			for (int i = 0; i < arity(); ++i)
			{
				aCtx.push((*adt)[i]);
			}

			return;
		}
	}

	// Добавляем UndefinedValue.
	aCtx.push(DataBuilders::createUndefinedValue());
}

//-------------------------------------------------------------------------------
EmptyConstructor::EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName)
	: Constructor(aConstructorName, aTypeName, std::vector<TypeInfo>(), std::vector<std::string>()),
	mTypeInfo(aTypeName)
{
}
//-------------------------------------------------------------------------------

} // Runtime
} // FPTL