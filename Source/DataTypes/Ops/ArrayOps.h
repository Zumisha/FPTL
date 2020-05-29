#pragma once

#include <string>

#include "Ops.h"
#include "Evaluator/Context.h"
#include "../TypeInfo.h"

namespace FPTL
{
	namespace Runtime
	{
		// Операции над массивами.
		class ArrayOps : public BaseOps
		{
			ArrayOps() = default;

		public:
			static ArrayOps * get()
			{
				static ArrayOps ops;
				return &ops;
			}

			inline static const std::string typeName = "Array";
			const std::string& getTypeName() const override
			{
				return typeName;
			}

			TypeInfo getType(const DataValue& aVal) const override;

			void mark(const DataValue & aVal, ObjectMarker * marker) const override;

			// Вывод содержимого массива.
			void print(const DataValue & aVal, std::ostream & aStream) const override;

			void rawPrint(const DataValue & aVal, std::ostream & aStream) const override;

			DataValue read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const override;
		};
	}
}
