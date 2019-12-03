#pragma once

#include <string>
#include <vector>

#include "../TypeInfo.h"
#include "ADTValue.h"
#include "Evaluator/Context.h"

namespace FPTL
{
	namespace Runtime
	{
		class Constructor
		{
		public:

			Constructor(std::string aConstructorName,
				const std::string & aTypeName,
			            std::vector<TypeInfo> aRefType,
				const std::vector<std::string> & aParameters
			);
			virtual ~Constructor() = default;

			virtual void execConstructor(SExecutionContext & aCtx) const;
			virtual void execDestructor(SExecutionContext & aCtx) const;

			std::string name() const { return mConstructorName; }
			std::vector<TypeInfo> type() const { return mReferenceType; }
			TypeInfo targetType() const { return mTargetType; }
			size_t arity() const { return mReferenceType.size(); }

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

		class ADTValue
		{
		public:
			const Constructor* ctor;
			std::vector<Value> values;

			ADTValue() = delete;

			ADTValue(const Constructor * ctor, const std::vector<Value>& values)
			{
				this->ctor = ctor;
				this->values = values;
			}

			ADTValue(const ADTValue & other)
			{
				ctor = other.ctor;
				values = other.values;
			}
		};
	}
}
