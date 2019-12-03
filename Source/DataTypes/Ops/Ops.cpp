#include <cassert>
#include <sstream>

#include "Ops.h"

namespace FPTL
{
	namespace Runtime
	{
		const Ops * DataValue::getOps() const
		{
			return mOps;
		}

		DataValue::DataValue()
			: mOps(nullptr)
		{
		}

		DataValue::DataValue(const Ops * aOps)
			: mOps(aOps)
		{
		}

		//-----------------------------------------------------------------------------
		Ops * BaseOps::withOps(const Ops * aOther) const
		{
			invalidOperation(getType(DataValue()));
			return nullptr;
		}

		Ops * BaseOps::withOps(StringOps const * aOther) const
		{
			invalidOperation(getType(DataValue()));
			return nullptr;
		}

		// Базисные функции.
		DataValue BaseOps::add(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::sub(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::mul(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::div(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::mod(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::abs(const DataValue & aVal) const
		{
			return invalidOperation(aVal.getOps()->getType(aVal));
		}

		// Функции сравнения.
		DataValue BaseOps::equal(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::less(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		DataValue BaseOps::greater(const DataValue & aLhs, const DataValue & aRhs) const
		{
			return invalidOperation(aRhs.getOps()->getType(aRhs));
		}

		// Функции преобразования.
		long long BaseOps::toInt(const DataValue & aVal) const
		{
			invalidOperation(aVal.getOps()->getType(aVal));
			return 0;
		}

		double BaseOps::toDouble(const DataValue & aVal) const
		{
			invalidOperation(aVal.getOps()->getType(aVal));
			return 0.0;
		}

		StringValue * BaseOps::toString(const DataValue & aVal) const
		{
			invalidOperation(aVal.getOps()->getType(aVal));
			return nullptr;
		}

		void BaseOps::write(const class DataValue& aVal, std::ostream& aStream) const
		{
			invalidOperation(aVal.getOps()->getType(aVal));
		}

		DataValue BaseOps::read(std::istream & aStream) const
		{
			invalidOperation(this->getType(*reinterpret_cast<DataValue const*>(this)));
			return DataValue();
		}

		void BaseOps::mark(const DataValue & aVal, ObjectMarker * marker) const
		{
		}

		DataValue BaseOps::invalidOperation(const TypeInfo & valType)
		{
			std::stringstream error;
			error << "invalid operation on type " << valType << ".";
			throw std::runtime_error(error.str());
		}

		//-----------------------------------------------------------------------------

		DataValue DataBuilders::createVal(Ops * aOps)
		{
			DataValue val(aOps);
			return val;
		}

		DataValue DataBuilders::createADT(ADTValue* aADTVal, Ops * aOps)
		{
			DataValue val(aOps);
			val.mADT = aADTVal;
			return val;
		}
	}
}
