#include <cassert>
#include <sstream>

#include "Ops.h"
#include "Evaluator/Context.h"

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
		// Базисные функции.
		
		DataValue& BaseOps::add(DataValue& aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "add");
		}

		DataValue BaseOps::add(const SExecutionContext & aCtx) const
		{
			const auto& arg = aCtx.getArg(0);
			throw invalidOperation(arg.getOps()->getType(arg), "add");
		}

		DataValue BaseOps::sub(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "sub");
		}

		DataValue BaseOps::mul(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "mul");
		}

		DataValue BaseOps::div(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "div");
		}

		DataValue BaseOps::mod(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "mod");
		}

		DataValue BaseOps::abs(const DataValue & aVal) const
		{
			throw invalidOperation(aVal.getOps()->getType(aVal), "abs");
		}

		// Функции сравнения.
		bool BaseOps::equal(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "equal");
		}

		bool BaseOps::less(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "less");
		}

		bool BaseOps::greater(const DataValue & aLhs, const DataValue & aRhs) const
		{
			throw invalidOperation(aRhs.getOps()->getType(aRhs), "greater");
		}

		// Функции преобразования.
		long long BaseOps::toInt(const DataValue & aVal) const
		{
			throw invalidOperation(aVal.getOps()->getType(aVal), "toInt");
		}

		double BaseOps::toDouble(const DataValue & aVal) const
		{
			throw invalidOperation(aVal.getOps()->getType(aVal), "toDouble");
		}

		void BaseOps::write(const class DataValue& aVal, std::ostream& aStream) const
		{
			throw invalidOperation(aVal.getOps()->getType(aVal), "write");
		}

		DataValue BaseOps::read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const
		{
			throw invalidOperation("read");
		}

		void BaseOps::mark(const DataValue & aVal, ObjectMarker * marker) const
		{
		}
		
		std::runtime_error  BaseOps::invalidOperation(const TypeInfo& valType1, const TypeInfo& valType2, const std::string& funcName)
		{
			std::stringstream error;
			error << invalidCombineMsg << valType1 << " and " << valType2 << " in " << funcName;
			return std::runtime_error(error.str());			
		}

		std::runtime_error BaseOps::invalidOperation(const TypeInfo& valType, const std::string& funcName)
		{
			std::stringstream error;
			error << invalidOpsMsg << valType << ": " << funcName;
			return std::runtime_error(error.str());
		}

		std::runtime_error BaseOps::invalidOperation(const std::string& funcName) const
		{
			std::stringstream error;
			error << invalidOpsMsg << this->getType(*reinterpret_cast<DataValue const*>(this)) << ": " << funcName;
			return std::runtime_error(error.str());
		}

		std::runtime_error BaseOps::divideByZero()
		{
			return std::runtime_error(divideByZeroMsg);
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
