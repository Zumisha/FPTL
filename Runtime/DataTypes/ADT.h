#pragma once

namespace FPTL
{
	namespace Runtime
	{
		struct SExecutionContext;
		struct DataValueArray;
		class DataValue;

		class Constructor
		{
		public:

			Constructor(const std::string & aConstructorName,
				const std::string & aTypeName,
				const TTypeList & aRefType,
				const std::vector<std::string> & aParameters
			);
			virtual ~Constructor();

			virtual void execConstructor(SExecutionContext & aCtx) const;
			virtual void execDestructor(SExecutionContext & aCtx) const;

			std::string name() const { return mConstructorName; }
			TTypeList type() const { return mReferenceType; }
			TypeInfo * targetType() const { return const_cast<TypeInfo *>(&mTargetType); }
			int arity() const { return static_cast<int>(mReferenceType.size()); }

		protected:

			std::string mConstructorName;
			std::string mTypeName;

			// Эталонный тип.
			TTypeList mReferenceType;

			// Создаваемый тип данных.
			TypeInfo mTargetType;
		};

		//-------------------------------------------------------------------------------
		// Конструктор без параметров.
		class EmptyConstructor : public Constructor
		{
		public:

			EmptyConstructor(const std::string & aConstructorName, const std::string & aTypeName);

		private:
			TypeInfo mTypeInfo;
		};

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
