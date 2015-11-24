#include <cassert>

#include "Data.h"
#include "ADT.h"
#include "Functions.h"
#include "CollectedHeap.h"
#include "GarbageCollector.h"

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

const DataValue & ADTValue::operator[](int i) const
{
	return values->values[i];
}

DataValue & ADTValue::operator[](int i)
{
	return values->values[i];
}

int ADTValue::size() const
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

	virtual TypeInfo * getType(const DataValue & aVal) const
	{
		return aVal.mADT.ctor->targetType();
	}
	
	// Добавлять сюда методы по мере добавления новых типов.
	virtual Ops * combine(const Ops * aOther) const
	{
		throw invalidOperation();
	}

	virtual Ops * withOps(class IntegerOps const * aOps) const
	{
		throw invalidOperation();
	}

	virtual Ops * withOps(class BooleanOps const * aOps) const
	{
		throw invalidOperation();
	}

	virtual Ops * withOps(class DoubleOps const * aOps) const
	{
		throw invalidOperation();
	}

	// Преобразование типов.
	virtual int toInt(const DataValue & aVal) const
	{
		throw invalidOperation();
	}

	virtual double toDouble(const DataValue & aVal) const
	{
		throw invalidOperation();
	}

	virtual StringValue * toString(const DataValue & aVal) const
	{
		throw invalidOperation();
	}

	// Арифметические функции.
	virtual DataValue add(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue div(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue abs(const DataValue & aArg) const
	{
		throw invalidOperation();
	}

	// Функции сравнения.
	virtual DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const
	{
		// TODO: возможно эту функцию можно определить.
		throw invalidOperation();
	}

	virtual DataValue less(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const
	{
		throw invalidOperation();
	}

	virtual void mark(const DataValue & aVal, ObjectMarker * marker) const
	{
		if (marker->markAlive(aVal.mADT.values, aVal.mADT.size()))
		{
			for (int i = 0; i < aVal.mADT.ctor->arity(); i++)
			{
				marker->addChild(&aVal.mADT[i]);
			}
		}
	}

	// Вывод в поток.
	virtual void print(const DataValue & aVal, std::ostream & aStream) const
	{
		auto val = aVal.mADT;
		int arity = val.ctor->arity();

		if (arity > 0)
		{
			aStream << "(";

			for (auto i = 0; i < arity; ++i)
			{
				val[i].getOps()->print(val[i], aStream);

				if (i + 1 < arity)
				{
					aStream << "*";
				}
			}
		
			aStream << ").";
		}

		aStream << val.ctor->name();
	}

private:
	std::exception invalidOperation() const
	{
		std::stringstream str;
		str << "invalid operation on abstract data type";
		return std::runtime_error(str.str());
	}
};

//-------------------------------------------------------------------------------
Constructor::Constructor(const std::string & aConstructorName, const std::string & aTypeName, const TTypeList & aRefType, const std::vector<std::string> & aParameters)
	: mConstructorName(aConstructorName),
	mReferenceType(aRefType),
	mTypeName(aTypeName),
	mTargetType(aTypeName)
{
	std::for_each(aParameters.begin(), aParameters.end(), [this](const std::string & param)
		{
			mTargetType.addParameter(param, TypeInfo(param));
		}
	);
}

//-------------------------------------------------------------------------------
Constructor::~Constructor()
{
}

//-------------------------------------------------------------------------------
void Constructor::execConstructor(SExecutionContext & aCtx) const
{
	// Проверяем соответсвие типов входного кортежа сигнатуре конструктора.
	try
	{
		int argNum = 0;
		TParametersMap params;

		int ar = arity();
		auto values = aCtx.heap().alloc<DataValueArray>(DataValueArray::size(ar));

		for (auto i = 0; i < ar; ++i)
		{
			auto & arg = aCtx.getArg(i);

			if (!TypeInfo::matchType(arg.getOps()->getType(arg), &mReferenceType[i], params))
			{
				throw std::runtime_error(std::string("type missmath: ")
					+ arg.getOps()->getType(arg)->TypeName + " expecting: " + mReferenceType[i].TypeName);
			}

			values->values[i] = arg;
		}

		// С типами все ок, cоздаем абстрактный тип данных.
		aCtx.push(DataBuilders::createADT(ADTValue(this, values.ptr()), ADTOps::get()));
	}
	catch (std::out_of_range & oor)
	{
		throw;
	}
}

//-------------------------------------------------------------------------------
void Constructor::execDestructor(SExecutionContext & aCtx) const
{
	// Проверяем что значение было создано именно этим деструктором.
	auto & arg = aCtx.getArg(0);

	if (arg.getOps() == ADTOps::get())
	{
		auto adt = arg.mADT;

		if (adt.ctor == this)
		{
			// Разворачиваем кортеж.
			for (int i = 0; i < arity(); ++i)
			{
				aCtx.push(adt[i]);
			}

			return;
		}
	}

	// Добавляем UndefinedValue.
	aCtx.push(DataBuilders::createUndefinedValue());
}

//-------------------------------------------------------------------------------
EmptyConstructor::EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName)
	: Constructor(aConstructorName, aTypeName, TTypeList(), std::vector<std::string>()),
	mTypeInfo(aTypeName)
{
}


//-------------------------------------------------------------------------------
void EmptyConstructor::execConstructor(SExecutionContext & aCtx) const
{
	// TODO: не нужно.
	Constructor::execConstructor(aCtx);
}

//-------------------------------------------------------------------------------
FunctionLibrary::FunctionLibrary(const std::string & aLibraryName)
	: mLibraryName(aLibraryName)
{
}

void FunctionLibrary::addFunction(const std::string & aFunctionName, const TFunction & aFunction)
{
	mFunctions.insert(std::make_pair(aFunctionName, aFunction));
}

TFunction FunctionLibrary::getFunction(const std::string & aFunctionName) const
{
	if (mFunctions.find(aFunctionName) != mFunctions.end())
	{
		return mFunctions.at(aFunctionName);
	}
	else
	{
		//assert(false); // Функция не найдена в библиотеке.

		// Возвращаем "пустышку".
		return [](SExecutionContext & aCtx) {
			aCtx.push(DataBuilders::createUndefinedValue());
		};
	}
}

std::vector<std::string> FunctionLibrary::getFunctionNames() const
{
	std::vector<std::string> result;

	std::for_each(mFunctions.begin(), mFunctions.end(), [&result](const std::pair<std::string, TFunction> & aElem)
		{
			result.push_back(aElem.first);
		}
	);

	return result;
}

std::string FunctionLibrary::getName() const
{
	return mLibraryName;
}

//-------------------------------------------------------------------------------

} // Runtime
} // FPTL