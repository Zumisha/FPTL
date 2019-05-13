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
	int length() const;
	std::string str() const;
};

//-----------------------------------------------------------------------------
// Класс для создания строк.
class StringBuilder
{
public:
	static DataValue create(SExecutionContext & aCtx, const std::string & aData);
	static DataValue create(SExecutionContext & aCtx, size_t aSize);
	static DataValue create(SExecutionContext & aCtx, const StringValue * aOther, int aBegin, int aEnd);
};

//-----------------------------------------------------------------------------

} // Runtime
} // FPTL