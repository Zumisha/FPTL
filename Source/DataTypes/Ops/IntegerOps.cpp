#include <istream>

#include "Ops.h"

namespace FPTL
{
	namespace Runtime
	{
		class IntegerOps : public BaseOps
		{
			IntegerOps() = default;

		public:
			static IntegerOps * get()
			{
				static IntegerOps ops;
				return &ops;
			}

			const Ops * combine(const Ops * aOther) const override
			{
				return aOther->withOps(this);
			}

			const Ops * withOps(const IntegerOps * aOps) const override
			{
				return get();
			}

			const Ops * withOps(const BooleanOps * aOps) const override
			{
				invalidOperation(getType(DataValue()));
				return nullptr;
			}

			const Ops * withOps(const DoubleOps * aOps) const override
			{
				return reinterpret_cast<Ops const*>(aOps);
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("int");
				return info;
			}

			// Преобразования типов.
			long long toInt(const DataValue & aVal) const override
			{
				return aVal.mIntVal;
			}

			double toDouble(const DataValue & aVal) const override
			{
				return static_cast<double>(aVal.mIntVal);
			}

			// Базисные функции.
			DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal + aRhs.getOps()->toInt(aRhs));
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal - aRhs.getOps()->toInt(aRhs));
			}

			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal * aRhs.getOps()->toInt(aRhs));
			}

			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const long long Right = aRhs.getOps()->toInt(aRhs);
				if (Right == 0) throw std::overflow_error("Divide by zero");
				return DataBuilders::createInt(aLhs.mIntVal / Right);
			}

			DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const long long Right = aRhs.getOps()->toInt(aRhs);
				if (Right == 0) throw std::overflow_error("Divide by zero");
				return DataBuilders::createInt(aLhs.mIntVal % Right);
			}

			DataValue abs(const DataValue & aArg) const override
			{
				return DataBuilders::createInt(std::abs(aArg.mIntVal));
			}

			// Функции сравнения.
			DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createBoolean(aLhs.mIntVal == aRhs.getOps()->toInt(aRhs));
			}

			DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createBoolean(aLhs.mIntVal < aRhs.getOps()->toInt(aRhs));
			}

			DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createBoolean(aLhs.mIntVal > aRhs.getOps()->toInt(aRhs));
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
			}

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
			}

			DataValue read(std::istream & aStream) const override
			{
				DataValue val(get());
				aStream >> val.mIntVal;
				return val;
			}
		};

		DataValue DataBuilders::createInt(long long aVal)
		{
			DataValue val(IntegerOps::get());
			val.mIntVal = aVal;
			return val;
		}
	}
}
