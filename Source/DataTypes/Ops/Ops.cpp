#include <cassert>
#include <sstream>

#include "Ops.h"
#include "Evaluator/Context.h"
#include "Macros.h"

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
		
		DataValue BaseOps::add(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::add(const SExecutionContext&, const DataValue* const, const DataValue* const) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::sub(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::sub(const SExecutionContext&, const DataValue* const, const DataValue* const) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::mul(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::mul(const SExecutionContext&, const DataValue* const, const DataValue* const) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::div(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::div(const SExecutionContext&, const DataValue* const, const DataValue* const) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::mod(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::mod(const SExecutionContext&, const DataValue* const, const DataValue* const) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::abs(const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		// Функции сравнения.
		bool BaseOps::equal(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		bool BaseOps::less(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		bool BaseOps::greater(const DataValue&, const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		// Функции преобразования.
		long long BaseOps::toInt(const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		double BaseOps::toDouble(const DataValue&) const
		{
			throw invalidOperation(__func__);
		}

		DataValue BaseOps::read(const DataValue&, const SExecutionContext&, std::istream&) const
		{
			throw invalidOperation(__func__);
		}

		void BaseOps::mark(const DataValue &, ObjectMarker*) const
		{
		}

		std::runtime_error BaseOps::invalidOperation(const std::string& funcName) const
		{
			std::stringstream error;
			error << invalidOpsMsg << this->getType(*reinterpret_cast<DataValue const*>(this)) << ": " << funcName;
			return std::runtime_error(error.str());
		}
		
		std::runtime_error BaseOps::invalidValueType(const std::string& refType, const std::string& valType)
		{
			std::stringstream error;
			error << invalidOpsMsg << valType << "\". Expected value of type \"" << refType << "\".";
			return std::runtime_error(error.str());			
		}

		void BaseOps::opsCheck(const Ops* ops, const DataValue& val)
		{
#if fptlDebugBuild
			if (val.getOps() != ops)
			{
				throw invalidValueType(ops->getTypeName(), std::string(val.getOps()->getType(val)));
			}
#endif
		}
		
		void BaseOps::typeCheck(const DataValue& refVal, const DataValue& val)
		{
#if fptlDebugBuild
			if (val.getOps()->getType(val) != refVal.getOps()->getType(refVal))
			{
				throw invalidValueType(std::string(val.getOps()->getType(val)), 
					std::string(refVal.getOps()->getType(refVal)));
			}
#endif
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
