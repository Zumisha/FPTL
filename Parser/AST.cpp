#include <cassert>
#include "AST.h"
#include "Support.h"
#include "NodeVisitor.h"

namespace FPTL {
namespace Parser {

	ASTNode::ASTNode( ASTNodeType aType ) : mType(aType), mCyclicIndex(0)
	{
	}

	ASTNode::~ASTNode()
	{
	}

	int ASTNode::cyclicIndex() const
	{
		return mCyclicIndex;
	}

	void ASTNode::increaseCyclicIndex()
	{
		mCyclicIndex++;
	}

	void ASTNode::setTypeTuple(const TTuple & aTuple)
	{
		mTypeTuple = aTuple;
	}

	TTuple ASTNode::getTypeTuple() const
	{
		return mTypeTuple;
	}

}}