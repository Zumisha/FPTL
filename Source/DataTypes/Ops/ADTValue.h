#pragma once

#include <string>
#include <vector>

#include "DataTypes/TypeInfo.h"
#include "GC/CollectedHeap.h"

//#include "../TypeInfo.h"

namespace FPTL
{
	namespace Runtime
	{
		struct SExecutionContext;
		struct DataValueArray;
		class DataValue;
		struct ADTValue;

		struct DataValueArray : public Collectable
		{
			DataValue values[];

			static size_t size(const size_t n)
			{
				return sizeof(DataValueArray) + n * sizeof(DataValue);
			}
		};

		class Constructor
		{
		public:
			Constructor(std::string aConstructorName, const std::string & aTypeName,
				std::vector<TypeInfo> aRefType, const std::vector<std::string> & aParameters);

			virtual ~Constructor() = default;

			virtual void execConstructor(SExecutionContext & aCtx) const;
			virtual void execDestructor(SExecutionContext & aCtx) const;

			std::string name() const { return mConstructorName; }
			std::string typeName() const { return mConstructorName; }
			std::vector<TypeInfo> type() const { return mReferenceType; }
			TypeInfo* targetType() const { return const_cast<TypeInfo*>(&mTargetType); }
			size_t arity() const { return static_cast<size_t>(mReferenceType.size()); }

		protected:

			std::string mConstructorName;
			std::string mTypeName;

			// Эталонный тип.
			std::vector<TypeInfo> mReferenceType;

			// Создаваемый тип данных.
			TypeInfo mTargetType;
		};

		//-------------------------------------------------------------------------------
		// Конструктор без параметров.
		class EmptyConstructor : public Constructor
		{
		public:
			EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName)
				: Constructor(aConstructorName, aTypeName, std::vector<TypeInfo>(), std::vector<std::string>()),
				mTypeInfo(aTypeName) {}

		private:
			TypeInfo mTypeInfo;
		};

		// Внутреннее представление абстрактного типа данных (boxed tuple).
		struct ADTValue
		{
			const Constructor * ctor;
			DataValueArray * values;

			ADTValue(): ctor(nullptr), values(nullptr)
			{
			}

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

			const DataValue & operator[](const size_t i) const
			{
				return values->values[i];
			}

			DataValue & operator[](const size_t i)
			{
				return values->values[i];
			}

			size_t size() const
			{
				return DataValueArray::size(ctor->arity());
			}
		};
	}
}
