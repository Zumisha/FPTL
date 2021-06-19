#pragma once
#include <any>
//#include <experimental/atomic>

#include "atomic_shared_ptr.h"

namespace FPTL
{
	namespace Runtime
	{
		class DataValue
		{
		public:
			
			/*DataValue(bool val)
			{
				value = val;
			}

			DataValue(int64_t val)
			{
				value = val;
			}

			DataValue(uint64_t val)
			{
				value = val;
			}

			DataValue(double val)
			{
				value = val;
			}
			
			template <typename T>
			DataValue(const T& val)
			{
				value = val;
			}*/
			
			DataValue(DataValue&& other) noexcept
			{
				std::swap(value,other.value);				
			}
			
			DataValue& operator=(DataValue&& other) noexcept
			{
				if (this != &other)
				{
					value.reset();
					std::swap(value, other.value);
				}
				return *this;
			}

			DataValue(const DataValue& other) = default;
			
			DataValue& operator=(const DataValue& other) 
			{
				if (this != &other)
				{
					value.reset();
					value = other.value;
				}
				return *this;
			}
			/*
			bool GetBool() const
			{
				return std::get<bool>(value);
			}

			int64_t GetInt64() const
			{
				return std::get<int64_t>(value);
			}

			uint64_t GetUInt64() const
			{
				return std::get<uint64_t>(value);
			}

			double GetDouble() const
			{
				return std::get<double>(value);
			}

			jss::atomic_shared_ptr<void*> GetPtr() const
			{
				return jss::atomic_shared_ptr<void*>(ptrValue.load());
			}*/

			std::any value;
			//std::experimental::atomic_shared_ptr<void*> va;
		};
	}
}
