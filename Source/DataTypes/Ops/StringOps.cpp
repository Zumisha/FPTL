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
			char* const value;
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

		void StringOps::mark(const DataValue & aVal, ObjectMarker * marker) const
		{
			marker->markAlive(aVal.mString, sizeof(StringValue));
			marker->markAlive(aVal.mString->data, aVal.mString->data->size() * sizeof(aVal.mString->data[0]));
		}

		// Арифметические функции.
		DataValue StringOps::add(const SExecutionContext & aCtx) const
		{
			size_t len = 0;
			for (size_t i = 0; i < aCtx.argNum; ++i)
			{
				const auto & arg = aCtx.getArg(i);
				len += arg.mString->length();
			}

			const auto val = StringBuilder::create(aCtx, len);
			const auto str = val.mString->getChars();
			size_t curPos = 0;

			for (size_t i = 0; i < aCtx.argNum; ++i)
			{
				const auto & arg = aCtx.getArg(i);
				const auto inStr = arg.mString;
				std::memcpy(str + curPos, inStr->getChars(), inStr->length());
				curPos += inStr->length();
			}

			return val;
		}

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
