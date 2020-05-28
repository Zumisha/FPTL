#pragma once

#include <boost/lexical_cast.hpp>

#include "Evaluator/Context.h"
#include "GC/CollectedHeap.h"

namespace FPTL {
	namespace Runtime {

		struct StringData;

		//-----------------------------------------------------------------------------
		struct StringValue : public Collectable
		{
			StringData* data;
			size_t begin;
			size_t end;

			char * getChars() const;
			char * contents() const;
			size_t length() const;
			std::string str() const;
		};

		//-----------------------------------------------------------------------------
		// Класс для создания строк.
		class StringBuilder
		{
		public:
			static DataValue create(const SExecutionContext & aCtx, const std::string & aData);
			static DataValue create(const SExecutionContext & aCtx, size_t aSize);
			static DataValue create(const SExecutionContext & aCtx, const StringValue * aOther, size_t aBegin, size_t aEnd);
		};

		//-----------------------------------------------------------------------------

		class StringOps : public BaseOps
		{
		protected:
			StringOps() = default;

		public:
			static StringOps * get()
			{
				static StringOps ops;
				return &ops;
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("String");
				return info;
			}

			// Преобразование типов.
			int64_t toInt(const DataValue & aVal) const override
			{
				return boost::lexical_cast<int64_t>(aVal.mString->str());
			}

			double toDouble(const DataValue & aVal) const override
			{
				return boost::lexical_cast<double>(aVal.mString->str());
			}

			// Арифметические функции.
			DataValue add(const SExecutionContext & aCtx) const override;

			// Функции сравнения.
			bool equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto* lhs = aLhs.mString;
				const auto* rhs = aRhs.mString;
				return lhs->length() == rhs->length() &&
					std::equal(
						lhs->getChars(),
						lhs->getChars() + lhs->length(),
						rhs->getChars());
			}

			bool less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto* lhs = aLhs.mString;
				const auto* rhs = aRhs.mString;
				return std::lexicographical_compare(
					lhs->getChars(),
					lhs->getChars() + lhs->length(),
					rhs->getChars(),
					rhs->getChars() + rhs->length());
			}

			bool greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto lhs = aLhs.mString;
				const auto rhs = aRhs.mString;
				return std::lexicographical_compare(
					rhs->getChars(),
					rhs->getChars() + rhs->length(),
					lhs->getChars(),
					lhs->getChars() + lhs->length());
			}

			void mark(const DataValue & aVal, ObjectMarker * marker) const override;

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << "\"" << aVal.mString->str() << "\"";
			}

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mString->str();
			}

			DataValue read(const DataValue & aVal, const SExecutionContext & aCtx, std::istream & aStream) const override
			{
				std::string str;
				aStream >> str;
				return StringBuilder::create(aCtx, str);
			}
		};

	}
}
