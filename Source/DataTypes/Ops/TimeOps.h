#pragma once

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

			// Преобразования типов.
			int64_t toInt(const DataValue & aVal) const override
			{
				return aVal.mIntVal;
			}

			double toDouble(const DataValue & aVal) const override
			{
				return static_cast<double>(aVal.mIntVal);
			}

			DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal + aRhs.mIntVal);
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				return DataBuilders::createInt(aLhs.mIntVal - aRhs.mIntVal);
			}
			
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				const std::chrono::system_clock::time_point dt{ std::chrono::system_clock::duration{aVal.mIntVal} };
				auto t = std::chrono::system_clock::to_time_t(dt);
				aStream << _ctime64(&t);
			}

			void rawPrint(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mIntVal;
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