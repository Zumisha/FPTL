#pragma once

namespace FPTL
{
	namespace Runtime
	{
		class Constructor;
		struct DataValueArray;
		class DataValue;

		// Внутреннее представление абстрактного типа данных (boxed tuple).
		struct ADTValue
		{
			const Constructor * ctor;
			DataValueArray * values;

			ADTValue()
			{}

			ADTValue(const Constructor * ctor, DataValueArray * values)
			{
				this->ctor = ctor;
				this->values = values;
			}

			ADTValue(const ADTValue & other)
			{
				ctor = other.ctor;
				values = other.values;
			}

			const DataValue & operator[](int i) const;
			DataValue & operator[](int i);

			size_t size() const;
		};
	}
}
