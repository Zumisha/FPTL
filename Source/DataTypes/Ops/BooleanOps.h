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

			const Ops * combine(const Ops * aOther) const override
			{
				return aOther->withOps(this);
			}

			const Ops * withOps(const IntegerOps * aOps) const override
			{
				throw invalidOperation("combine with int");
			}

			const Ops * withOps(const BooleanOps * aOps) const override
			{
				return get();
			}

			const Ops * withOps(const DoubleOps * aOps) const override
			{
				throw invalidOperation("combine with double");
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("boolean");
				return info;
			}

			// Преобразования типов.
			long long toInt(const DataValue & aVal) const override
			{
				return (aVal.mIntVal ? 1 : 0);
			}

			double toDouble(const DataValue & aVal) const override
			{
				return (aVal.mIntVal ? 1.0 : 0.0);
			}

			// Функции сравнения. Оба аргумента обязаны быть типа boolean.
			DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createBoolean(aLhs.mIntVal == aRhs.mIntVal);
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

			DataValue read(std::istream & aStream) const override
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
