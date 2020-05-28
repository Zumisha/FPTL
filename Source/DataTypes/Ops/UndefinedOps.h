#pragma once

#include <ostream>
#include "Ops.h"

namespace FPTL
{
	namespace Runtime
	{

		class UndefinedValueOps : public BaseOps
		{
			UndefinedValueOps() = default;

		public:
			static UndefinedValueOps* get()
			{
				static UndefinedValueOps ops;
				return &ops;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("Undefined");
				return info;
			}

			// Функция сравнения со значением true определена.
			bool equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return false;
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << "Undefined";
			}
		};

		inline UndefinedValue DataBuilders::createUndefinedValue()
		{
			return UndefinedValue(UndefinedValueOps::get());
		}
	}
}
