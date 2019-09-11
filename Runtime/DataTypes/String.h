#pragma once

#include "../Context.h"
#include "Runtime/CollectedHeap.h"

namespace FPTL {
namespace Runtime {

struct StringData;

//-----------------------------------------------------------------------------
struct StringValue : public Collectable
{
	StringData * data;
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
	static DataValue create(SExecutionContext & aCtx, const std::string & aData);
	static DataValue create(SExecutionContext & aCtx, size_t aSize);
	static DataValue create(SExecutionContext & aCtx, const StringValue * aOther, size_t aBegin, size_t aEnd);
};

//-----------------------------------------------------------------------------

} // Runtime
} // FPTL