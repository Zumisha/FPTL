#pragma once

#include <sstream>
#include <utility>

#include "Ops.h"
#include "UndefinedOps.h"
#include "GC/CollectedHeap.h"
#include "GC/GarbageCollector.h"
#include "ADTValue.h"

namespace FPTL
{
	namespace Runtime
	{
		struct ADTValue;

		// Implementation of operations on abstract data types (ADT) values (boxed tuple).
		class ADTOps : public BaseOps
		{
			// TODO: определить функции Equal, Length
		public:
			static ADTOps * get()
			{
				// It breaks if there are errors in the Ops, BaseOps, Value, ADTValue or this classes.
				static ADTOps ops;
				return &ops;
			}

			inline static const std::string typeName = "ADT";
			const std::string& getTypeName() const override
			{
				return typeName;
			}

			TypeInfo getType(const DataValue & aVal) const override
			{
				return *aVal.mADT->ctor->targetType();
			}
			
			void mark(const DataValue & aVal, ObjectMarker * marker) const override
			{
				if (marker->markAlive(aVal.mADT->values, aVal.mADT->size()))
				{
					for (size_t i = 0; i < aVal.mADT->ctor->arity(); i++)
					{
						marker->addChild(&(*aVal.mADT)[i]);
					}
				}
			}

			void print(const DataValue& aVal, std::ostream& aStream) const override
			{
				const auto val = aVal.mADT;
				const size_t arity = val->ctor->arity();

				if (arity > 0)
				{
					aStream << "(";

					for (size_t i = 0; i < arity; ++i)
					{
						(*val)[i].getOps()->print((*val)[i], aStream);

						if (i + 1 < arity)
						{
							aStream << "*";
						}
					}

					aStream << ").";
				}

				aStream << val->ctor->name();
			}

			void rawPrint(const DataValue& aVal, std::ostream& aStream) const override
			{
				print(aVal, aStream);
			}

			static std::string assignErrMsg(const std::string& fType, const std::string& sType)
			{
				std::stringstream error;
				error << "type mismatch. Actual: " << fType << ". Expected: " << sType << ".";
				return error.str();
			}
		};
	}
}
