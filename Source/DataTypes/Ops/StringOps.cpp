#include <cassert>

#include <boost/lexical_cast.hpp>

#include "Ops.h"
#include "StringOps.h"
#include "BooleanOps.h"
#include "GC/CollectedHeap.h"
#include "GC/GarbageCollector.h"

namespace FPTL
{
	namespace Runtime
	{
		struct StringData : public Collectable
		{
			char * const value;
			const size_t length;

			explicit StringData(const size_t aLength)
				: value(reinterpret_cast<char *>(this) + sizeof(StringData)),
				length(aLength)
			{}

			size_t size() const
			{
				return sizeof(StringData) + length * sizeof(char);
			}
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

			const Ops* combine(const Ops * aOther) const override
			{
				return aOther->withOps(this);
			}

			const Ops* withOps(const StringOps * aOther) const override
			{
				return get();
			}

			const Ops* withOps(const Ops * aOps) const override
			{
				throw invalidOperation("combine");
			}

			const Ops* withOps(const BooleanOps * aOps) const override
			{
				throw invalidOperation("toBool");
			}

			const Ops * withOps(const IntegerOps * aOps) const override
			{
				throw invalidOperation("toInt");
			}

			const Ops * withOps(const DoubleOps * aOps) const override
			{
				throw invalidOperation("toDouble");
			}

			TypeInfo getType(const DataValue &aVal) const override
			{
				static TypeInfo info("string");
				return info;
			}

			// Преобразование типов.
			long long toInt(const DataValue & aVal) const override
			{
				return boost::lexical_cast<long long>(aVal.mString->str());
			}

			double toDouble(const DataValue & aVal) const override
			{
				return boost::lexical_cast<double>(aVal.mString->str());
			}

			StringValue * toString(const DataValue & aVal) const override
			{
				return aVal.mString;
			}

			// Арифметические функции.
			DataValue add(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("add");
			}

			DataValue sub(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("sub");
			}

			DataValue mul(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("mul");
			}

			DataValue div(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("div");
			}

			DataValue mod(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				throw invalidOperation("mod");
			}

			DataValue abs(const DataValue & aArg) const override
			{
				throw invalidOperation("abs");
			}

			// Функции сравнения.
			DataValue equal(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto lhs = aLhs.mString;
				const auto rhs = aRhs.mString;
				return DataBuilders::createBoolean(
					lhs->length() == rhs->length() && std::equal(lhs->getChars(), lhs->getChars() + lhs->length(), rhs->getChars())
				);
			}

			DataValue less(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto lhs = aLhs.mString;
				const auto rhs = aRhs.mString;
				return DataBuilders::createBoolean(
					std::lexicographical_compare(lhs->getChars(), lhs->getChars() + lhs->length(), rhs->getChars(), rhs->getChars() + rhs->length())
				);
			}

			DataValue greater(const DataValue & aLhs, const DataValue & aRhs) const override
			{
				const auto lhs = aLhs.mString;
				const auto rhs = aRhs.mString;
				return DataBuilders::createBoolean(
					std::lexicographical_compare(rhs->getChars(), rhs->getChars() + rhs->length(), lhs->getChars(), lhs->getChars() + lhs->length())
				);
			}

			void mark(const DataValue & aVal, ObjectMarker * marker) const override
			{
				marker->markAlive(aVal.mString, sizeof(StringValue));
				marker->markAlive(aVal.mString->data, aVal.mString->data->size() * sizeof(aVal.mString->data[0]));
			}

			// Вывод в поток.
			void print(const DataValue & aVal, std::ostream & aStream) const override
			{
				const auto str = aVal.mString;
				aStream << "\"" << aVal.mString->str() << "\"";
			}

			void write(const DataValue & aVal, std::ostream & aStream) const override
			{
				aStream << aVal.mString->data->value;
			}

			DataValue read(std::istream & aStream) const override
			{
				throw invalidOperation("read");
			}
		};

		//-----------------------------------------------------------------------------

		char * StringValue::getChars() const
		{
			return data->value + begin;
		}

		char * StringValue::contents() const
		{
			return data->value;
		}

		size_t StringValue::length() const
		{
			return end - begin;
		}

		std::string StringValue::str() const
		{
			return std::string(data->value + begin, data->value + end);
		}

		//-----------------------------------------------------------------------------

		DataValue StringBuilder::create(const SExecutionContext & aCtx, const std::string & aData)
		{
			auto val = create(aCtx, aData.size());

			std::copy(aData.begin(), aData.end(), val.mString->getChars());

			return val;
		}

		DataValue StringBuilder::create(const SExecutionContext & aCtx, size_t aSize)
		{
			auto val = DataBuilders::createVal(StringOps::get());

			GcAwarePtr<StringData> data = aCtx.heap().alloc<StringData>([aSize](void * m) { return new(m) StringData(aSize); }, sizeof(StringData) + aSize);
			GcAwarePtr<StringValue> str = aCtx.heap().alloc<StringValue>(sizeof(StringValue));

			str->begin = 0;
			str->end = aSize;
			str->data = data.ptr();

			val.mString = str.ptr();
			return val;
		}

		DataValue StringBuilder::create(const SExecutionContext & aCtx, const StringValue * aOther, size_t aBegin, size_t aEnd)
		{
			auto str = aCtx.heap().alloc<StringValue>(sizeof(StringValue));

			str->data = aOther->data;
			str->begin = aBegin;
			str->end = aEnd;

			auto val = DataBuilders::createVal(StringOps::get());
			val.mString = str.ptr();
			return val;
		}
	}
}
