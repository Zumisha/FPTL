#pragma once

#include <string>

namespace FPTL {
	namespace Parser {

		// Указатель на запись в таблице имен.
		struct Ident
		{
			size_t Col;
			size_t Line;
			const std::string * Ptr;

			bool operator==(const Ident & aOther) const { return Ptr == aOther.Ptr; }
			bool operator!=(const Ident & aOther) const { return Ptr != aOther.Ptr; }

			bool operator <(const Ident & aOther) const { return *Ptr < *aOther.Ptr; }

			const std::string & getStr() const { return *Ptr; }
		};

	}
}
