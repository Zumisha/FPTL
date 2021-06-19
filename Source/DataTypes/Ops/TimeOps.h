#pragma once

#include <ctime>

#include "Ops.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		class TimeOps : public BaseOps
		{
			TimeOps() = default;

		public:
			static TimeOps* get()
			{
				static TimeOps ops;
				return &ops;
			}

			inline static const std::string typeName = "Time";
			const std::string& getTypeName() const override
			{
				return typeName;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info(typeName);
				return info;
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal - aRhs.mIntVal);
			}
			
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << _ctime64(&aVal.mIntVal);
			}

			void rawPrint(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
			}
		};

		/*inline DataValue DataBuilders::createTime(int64_t aVal)
		{
			DataValue val(TimeOps::get());
			val.mIntVal = aVal;
			return val;
		}*/
	}
}