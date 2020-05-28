#pragma once

#include <istream>
#include <cmath>

#include "Ops.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		class DoubleOps : public BaseOps
		{
			DoubleOps() = default;

		public:
			static DoubleOps * get()
			{
				static DoubleOps ops;
				return &ops;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("Double");
				return info;
			}

			// Функции преобразования.
			int64_t toInt(const DataValue & aVal) const override
			{
				return static_cast<int64_t>(aVal.mDoubleVal);
			}

			double toDouble(const DataValue & aVal) const override
			{
				return aVal.mDoubleVal;
			}

			DataValue& add(DataValue& aLhs, const DataValue& aRhs) const override
			{
				aLhs.mDoubleVal += aRhs.mDoubleVal;
				return aLhs;
			}

			DataValue add(const SExecutionContext& aCtx) const override
			{
				double sum = 0;
				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					sum += aCtx.getArg(i).mDoubleVal;
				}
				return DataBuilders::createDouble(sum);
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createDouble(aLhs.mDoubleVal - aRhs.mDoubleVal);
			}

			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createDouble(aLhs.mDoubleVal * aRhs.mDoubleVal);
			}

			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto Right = aRhs.mDoubleVal;
				if (Right == 0) throw divideByZero();
				return DataBuilders::createDouble(aLhs.mDoubleVal / Right);
			}

			DataValue abs(const DataValue & aArg) const override
			{
				return DataBuilders::createDouble(std::abs(aArg.mDoubleVal));
			}

			// Функции сравнения.
			bool equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mDoubleVal == aRhs.mDoubleVal;
			}

			bool less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mDoubleVal < aRhs.mDoubleVal;
			}

			bool greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mDoubleVal > aRhs.mDoubleVal;
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mDoubleVal;
			}

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mDoubleVal;
			}

			DataValue read(const DataValue&, const SExecutionContext&, std::istream & aStream) const override
			{
				DataValue val(get());
				aStream >> val.mDoubleVal;
				return val;
			}
		};

		inline DataValue DataBuilders::createDouble(const double aVal)
		{
			DataValue val(DoubleOps::get());
			val.mDoubleVal = aVal;
			return val;
		}
	}
}
