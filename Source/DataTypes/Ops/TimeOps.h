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

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("Time");
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

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << _ctime64(&aVal.mIntVal);
			}
		};

		inline DataValue DataBuilders::createTime(int64_t aVal)
		{
			DataValue val(TimeOps::get());
			val.mIntVal = aVal;
			return val;
		}
	}
}