#pragma once
#include "DataValue.h"

namespace FPTL
{
	namespace Runtime
	{
		// Неопределенное значение.
		class UndefinedValue : public DataValue
		{
			friend class DataBuilders;

			explicit UndefinedValue(const Ops * aOps)
				: DataValue(aOps)
			{}
		};
	}
}
