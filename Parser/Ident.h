#ifndef IDENT_H
#define IDENT_H

#include <string>
#include <ext/hash_map>

namespace FPTL {
namespace Parser {

	// ”казатель на запись в таблице имен.
	struct Ident
	{
		short Col;
		short Line;
		const std::string * Ptr;

		bool operator==( const Ident & aOther ) const { return Ptr == aOther.Ptr; }
		bool operator!=( const Ident & aOther ) const { return Ptr != aOther.Ptr; }

		bool operator <( const Ident & aOther ) const { return *Ptr < *aOther.Ptr; }

		const std::string & getStr() const { return *Ptr; }
	};

}
}

#endif
