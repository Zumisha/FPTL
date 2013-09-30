#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "Support.h"
#include "NodeVisitor.h"

namespace FPTL
{
	class TypeChecker : public NodeVisitor
	{
	public:

		bool visitEnter( FunctionNode * aFunctionNode );
		bool visitEnter( DefinitionNode * aDefinitionNode );
		bool visitEnter( NameRefNode * aNameRefNode );
	};
}

#endif