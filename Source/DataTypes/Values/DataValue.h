#pragma once

namespace FPTL
{
	namespace Runtime
	{
		class Ops;
		struct ADTValue;
		struct StringValue;
		struct ArrayValue;

		// Variant дл€ представлени€ всех типов данных, кроме неопределенного значени€.
		class DataValue
		{
			friend class DataBuilders;

		public:
			//  онструктор по умолчанию. —оздает значение типа "неопределенность".
			DataValue();
			explicit DataValue(const Ops * aOps);
			DataValue(const DataValue & other)
			{
				*this = other;
			}

			const Ops * getOps() const;

		protected:
			const Ops * mOps;

			// ƒоступ к информационной части открыт дл€ удобства.
		public:
			// Ќе стоит здесь использовать типы, размер которых не 8Ѕ -
			// данные могут выровн€тьс€ не так, как ожидаетс€.
			union
			{
				int64_t mIntVal;
				double mDoubleVal;
				ADTValue* mADT;
				StringValue* mString;
				ArrayValue* mArray;
			}; // size = max of members size 
		};
	}
}
