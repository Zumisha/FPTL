#include <cassert>

#include "Generated/parser.tab.hh"

#include "Support.h"
#include "Nodes.h"

namespace FPTL {
	namespace Parser {
		ExpressionNode::ExpressionNode(const ASTNodeType aType, ASTNode * aLeft, ASTNode * aRight)
			: ASTNode(aType),
			mLeft(aLeft),
			mRight(aRight),
			mMiddle(nullptr)
		{
		}

		ExpressionNode::ExpressionNode(const ASTNodeType aType, ASTNode * aLeft, ASTNode * aRight, ASTNode * aMiddle)
			: ASTNode(aType),
			mLeft(aLeft),
			mRight(aRight),
			mMiddle(aMiddle)
		{
		}

		ExpressionNode::~ExpressionNode()
		{
			delete mLeft;
			delete mRight;
			delete mMiddle;
		}

		void ExpressionNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * ExpressionNode::copy() const
		{
			return new ExpressionNode(getType(),
				mLeft ? mLeft->copy() : nullptr,
				mRight ? mRight->copy() : nullptr,
				mMiddle ? mMiddle->copy() : nullptr
			);
		}

		//-------------------------------------------------------------------------------------------

		ListNode::~ListNode()
		{
			for (auto& it : *this)
				delete it;
		}

		void ListNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ListNode * ListNode::copy() const
		{
			auto newList = new ListNode(getType());
			for (auto aElem : *this) { newList->push_back(aElem->copy()); }
			return newList;
		}

		//-------------------------------------------------------------------------------------------

		DataNode::DataNode(const Ident &aTypeName, ListNode * aTypeDefs, ListNode * aTypeParams, ListNode * aConstructors)
			: ASTNode(DataTypeDefinitionBlock),
			mTypeName(aTypeName),
			mConstructors(aConstructors),
			mTypeDefinitions(aTypeDefs),
			mTypeParameters(aTypeParams)
		{
		}

		DataNode::~DataNode()
		{
			delete mConstructors;
			delete mTypeDefinitions;
			delete mTypeParameters;
		}

		void DataNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * DataNode::copy() const
		{
			return new DataNode(mTypeName,
				mTypeDefinitions ? mTypeDefinitions->copy() : nullptr,
				mTypeParameters ? mTypeParameters->copy() : nullptr,
				mConstructors ? mConstructors->copy() : nullptr
			);
		}

		//-------------------------------------------------------------------------------------------

		ConstructorNode::ConstructorNode(const Ident &aName, ListNode * aCtorParameters, const Ident &aCtorResultTypeName)
			: ASTNode(Constructor),
			mName(aName),
			mCtorParameters(aCtorParameters),
			mCtorResultTypeName(aCtorResultTypeName)
		{
		}

		void ConstructorNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ConstructorNode::~ConstructorNode()
		{
			delete mCtorParameters;
		}

		ASTNode * ConstructorNode::copy() const
		{
			return new ConstructorNode(mName, mCtorParameters ? mCtorParameters->copy() : nullptr, mCtorResultTypeName);
		}

		//-------------------------------------------------------------------------------------------

		NameRefNode::NameRefNode(const Ident &aTypeName, const ASTNodeType aNodeType)
			: ASTNode(aNodeType),
			mTypeName(aTypeName),
			mParameters(nullptr),
			mTarget(nullptr)
		{
		}

		NameRefNode::NameRefNode(const Ident &aTypeName, const ASTNodeType aNodeType, ListNode * aParams)
			: ASTNode(aNodeType),
			mTypeName(aTypeName),
			mParameters(aParams),
			mTarget(nullptr)
		{
		}

		NameRefNode::~NameRefNode()
		{
			delete mParameters;
		}

		void NameRefNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * NameRefNode::copy() const
		{
			return new NameRefNode(mTypeName, getType(), mParameters ? mParameters->copy() : nullptr);
		}

		//-------------------------------------------------------------------------------------------

		FunctionNode::FunctionNode(const Ident &aFuncName, ListNode * aDefinitions, ListNode * aFormalParams)
			: ASTNode(ASTNode::FunctionBlock),
			mFuncName(aFuncName),
			mDefinitions(aDefinitions),
			mFormalParameters(aFormalParams)
		{
		}

		FunctionNode::~FunctionNode()
		{
			delete mDefinitions;
			delete mFormalParameters;
		}

		void FunctionNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		FunctionNode * FunctionNode::copy() const
		{
			const auto copy = new FunctionNode(mFuncName, mDefinitions ? mDefinitions->copy() : nullptr,
				mFormalParameters ? mFormalParameters->copy() : nullptr);

			return copy;
		}

		DefinitionNode * FunctionNode::getDefinition(const Ident &aName) const
		{
			for (auto& mDefinition : *mDefinitions)
			{
				// do not use dynamic_cast
				const auto def = static_cast<DefinitionNode *>(mDefinition);
				if (def->getDefinitionName() == aName)
				{
					return def;
				}
			}
			return nullptr;
		}

		std::vector<FunctionNode *> FunctionNode::getFunctionNodes() const
		{
			std::vector<FunctionNode *> functions;
			for (auto& mDefinition : *mDefinitions)
			{
				auto def = dynamic_cast<FunctionNode *>(mDefinition);
				if (def)
				{
					functions.push_back(def);
				}
			}

			return functions;
		}

		//-------------------------------------------------------------------------------------------

		DefinitionNode::DefinitionNode(const ASTNodeType aType, const Ident &aName, ASTNode * aDefinition)
			: ASTNode(aType),
			mDefinitionName(aName),
			mDefinition(aDefinition)
		{
		}

		DefinitionNode::~DefinitionNode()
		{
			delete mDefinition;
		}

		void DefinitionNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * DefinitionNode::copy() const
		{
			return new DefinitionNode(getType(), mDefinitionName, mDefinition ? mDefinition->copy() : nullptr);
		}

		//-------------------------------------------------------------------------------------------

		FunctionalProgram::FunctionalProgram(ListNode * aDataDefinitions, FunctionNode * aScheme, ApplicationBlock * aApplication)
			: ASTNode(FunctionalProgramDef),
			mDataDefinitions(aDataDefinitions),
			mScheme(aScheme),
			mApplication(aApplication)
		{
		}

		FunctionalProgram::~FunctionalProgram()
		{
			delete mDataDefinitions;
			delete mScheme;
			delete mApplication;
		}

		void FunctionalProgram::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * FunctionalProgram::copy() const
		{
			return new FunctionalProgram(
				mDataDefinitions ? mDataDefinitions->copy() : nullptr,
				mScheme ? mScheme->copy() : nullptr,
				mApplication ? mApplication->copy() : nullptr
			);
		}

		//-------------------------------------------------------------------------------------------

		ApplicationBlock::ApplicationBlock(NameRefNode * aRunSchemeName, ASTNode * aSchemeParameters, ListNode * aDataVarDefs)
			: ASTNode(Application),
			mRunSchemeName(aRunSchemeName),
			mSchemeParameters(aSchemeParameters),
			mDataVarDefinitions(aDataVarDefs)
		{
		}

		ApplicationBlock::~ApplicationBlock()
		{
			delete mRunSchemeName;
			delete mSchemeParameters;
			delete mDataVarDefinitions;
		}

		ApplicationBlock * ApplicationBlock::copy() const
		{
			return new ApplicationBlock(mRunSchemeName, mSchemeParameters ? mSchemeParameters->copy() : nullptr,
				mDataVarDefinitions ? mDataVarDefinitions->copy() : nullptr);
		}

		void ApplicationBlock::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		//-------------------------------------------------------------------------------------------

		void ConstantNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ASTNode * ConstantNode::copy() const
		{
			return new ConstantNode(getType(), mIdent);
		}

		bool ConstantNode::isNatural() const
		{
			return getType() == ASTNode::IntConstant && atoi(mIdent.getStr().c_str()) > 0;
		}
	}
}
