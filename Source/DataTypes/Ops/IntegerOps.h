#pragma once

#include <istream>

#include "Ops.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		class IntegerOps : public BaseOps
		{
			IntegerOps() = default;

		public:
			static IntegerOps* get()
			{
				static IntegerOps ops;
				return &ops;
			}

			inline static const std::string typeName = "Int";
			const std::string& getTypeName() const override
			{
				return typeName;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info(typeName);
				return info;
			}

			// Преобразования типов.
			int64_t toInt(const DataValue & aVal) const override
			{
				return aVal.mIntVal;
			}

			double toDouble(const DataValue & aVal) const override
			{
				return static_cast<double>(aVal.mIntVal);
			}

			DataValue add(const DataValue& aLhs, const DataValue& aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal + aRhs.mIntVal);
			}

			DataValue add(const SExecutionContext&, const DataValue* const first, const DataValue* const last) const override
			{
				int64_t sum = 0;
				const DataValue* iterator = first;
				while (iterator <= last)
				{
					sum += iterator->mIntVal;
					iterator++;
				}				
				return DataBuilders::createInt(sum);
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal - aRhs.mIntVal);
			}

			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal * aRhs.mIntVal);
			}

			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const long long Right = aRhs.mIntVal;
				if (Right == 0) throw divideByZero();
				return DataBuilders::createInt(aLhs.mIntVal / Right);
			}

			DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const long long Right = aRhs.mIntVal;
				if (Right == 0) throw divideByZero();
				return DataBuilders::createInt(aLhs.mIntVal % Right);
			}

			DataValue abs(const DataValue & aArg) const override
			{
				return DataBuilders::createInt(std::abs(aArg.mIntVal));
			}

			// Функции сравнения.
			bool equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mIntVal == aRhs.mIntVal;
			}

			bool less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mIntVal < aRhs.mIntVal;
			}

			bool greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return aLhs.mIntVal > aRhs.mIntVal;
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
			}

			void rawPrint(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
			}

			DataValue read(const DataValue&, const SExecutionContext&, std::istream & aStream) const override
			{
				DataValue val(get());
				aStream >> val.mIntVal;
				return val;
			}
		};

		inline DataValue DataBuilders::createInt(int64_t aVal)
		{
			DataValue val(IntegerOps::get());
			val.mIntVal = aVal;
			return val;
		}
	}
}
