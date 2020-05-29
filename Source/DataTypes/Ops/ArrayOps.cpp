#include "ArrayOps.h"

#include <boost/format.hpp>
#include <algorithm>

#include "DataTypes/TypeInfo.h"
#include "DataTypes/Values/ArrayValue.h"
#include "GC/GarbageCollector.h"
#include "DataTypes/Values/DataValue.h"

namespace FPTL
{
	namespace Runtime
	{
		TypeInfo ArrayOps::getType(const DataValue& aVal) const
		{
			return aVal.mArray->type;
		}

		void ArrayOps::mark(const DataValue& aVal, ObjectMarker* marker) const
		{
			if (marker->markAlive(aVal.mArray, sizeof(ArrayValue) + sizeof(aVal.mArray->arrayData[0]) * aVal.mArray->length))
			{
				for (size_t i = 0; i < aVal.mArray->length; i++)
				{
					marker->addChild(&aVal.mArray->arrayData[i]);
				}
			}
		}

		// Вывод содержимого массива.
		void  ArrayOps::print(const DataValue & aVal, std::ostream & aStream) const
		{
			ArrayValue * arr = aVal.mArray;

			std::string delimiter;
			if (arr->arrayData[0].getOps() == ArrayOps::get())
			{
				delimiter = ",\n";
			}
			else
			{
				delimiter = ", ";
			}

			size_t i = 0;
			aStream << "[";
			for (; i < std::min(arr->length, 5llu); ++i)
			{
				if (i > 0)
				{
					aStream << delimiter;
				}

				DataValue & val = arr->arrayData[i];
				val.getOps()->print(val, aStream);
			}
			if (arr->length - i > 5)
			{
				i = arr->length - 5;
				aStream << delimiter << "... ";
			}
			for (; i < arr->length; ++i)
			{
				aStream << delimiter;

				DataValue & val = arr->arrayData[i];
				val.getOps()->print(val, aStream);
			}
			aStream << "]";
		}

		void  ArrayOps::rawPrint(const DataValue & aVal, std::ostream & aStream) const
		{
			ArrayValue* arrVal = aVal.mArray;

			std::string delimiter;
			if (arrVal->arrayData[0].getOps() == ArrayOps::get())
			{
				delimiter = "\n";
			}
			else
			{
				delimiter = " ";
			}
			
			for (size_t i = 0; i < arrVal->length; ++i)
			{
				arrVal->arrayData[0].getOps()->rawPrint(arrVal->arrayData[i], aStream);
				if (i < arrVal->length - 1)
				{
					aStream << delimiter;
				}
			}
		}

		DataValue ArrayOps::read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const
		{
			auto* const arrVal = aVal.mArray;
			for (size_t i = 0; i < arrVal->length; ++i)
			{
				arrVal->arrayData[i] = arrVal->arrayData[i].getOps()->read(arrVal->arrayData[i], aCtx, aStream);
			}
			return aVal;
		}
	}
}
