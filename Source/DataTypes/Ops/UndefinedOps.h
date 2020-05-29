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

			inline static const std::string typeName = "Undefined";
			const std::string& getTypeName() const override
			{
				return typeName;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info(typeName);
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
			
			void rawPrint(const DataValue & aVal, std::ostream & aStream) const override
			{
				print(aVal, aStream);
			}
		};

		inline UndefinedValue DataBuilders::createUndefinedValue()
		{
			return UndefinedValue(UndefinedValueOps::get());
		}
	}
}
