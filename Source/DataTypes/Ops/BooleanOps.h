#pragma once

#include <istream>

#include "Ops.h"

namespace FPTL
{
	namespace Runtime
	{
		class BooleanOps : public BaseOps
		{
			BooleanOps() = default;

		public:
			static BooleanOps * get()
			{
				static BooleanOps ops;
				return &ops;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("Boolean");
				return info;
			}

			// Преобразования типов.
			int64_t toInt(const DataValue & aVal) const override
			{
				return (aVal.mIntVal ? 1 : 0);
			}

			double toDouble(const DataValue & aVal) const override
			{
				return (aVal.mIntVal ? 1.0 : 0.0);
			}

			// Функции сравнения. Оба аргумента обязаны быть типа boolean.
			bool equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return (aLhs.mIntVal == 0) == (aRhs.mIntVal == 0);
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << (aVal.mIntVal ? "true" : "false");
			}

			// Вывод в поток.
			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << (aVal.mIntVal ? "1" : "0");
			}

			DataValue read(const DataValue&, const SExecutionContext&, std::istream & aStream) const override
			{
				DataValue val(get());
				aStream >> val.mIntVal;
				return val;
			}
		};

		inline DataValue DataBuilders::createBoolean(bool aVal)
		{
			DataValue val(BooleanOps::get());
			val.mIntVal = aVal;
			return val;
		}
	}
}
