#include <cassert>

#include "Generated/parser.tab.hh"

#include "Support.h"
#include "Nodes.h"

namespace FPTL {
	namespace Parser {

		ExpressionNode::ExpressionNode(const ASTNodeType aType, ASTNode* aLeft, ASTNode* aRight, ASTNode* aMiddle)
			: ASTNode(aType)
		{
			mChilds = std::vector<ASTNode*>(3);
			mChilds[mLeft] = aLeft;
			mChilds[mRight] = aRight;
			mChilds[mMiddle] = aMiddle;
		}

		ExpressionNode::~ExpressionNode()
		{
			delete mChilds[mLeft];
			delete mChilds[mRight];
			delete mChilds[mMiddle];
		}

		void ExpressionNode::accept(NodeVisitor* aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode* ExpressionNode::copy() const
		{
			auto copy = new ExpressionNode(getType(),
				mChilds[mLeft] ? mChilds[mLeft]->copy() : nullptr,
				mChilds[mRight] ? mChilds[mRight]->copy() : nullptr,
				mChilds[mMiddle] ? mChilds[mMiddle]->copy() : nullptr);
			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-------------------------------------------------------------------------------------------

		ListNode::~ListNode()
		{
			for (auto& it : mChilds)
				delete it;
		}

		void ListNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ListNode * ListNode::copy() const
		{
			auto newList = new ListNode(getType());
			newList->mChilds = std::vector<ASTNode*>(mChilds.size());
			for (auto aElem : mChilds)
			{
				newList->mChilds.push_back(aElem->copy());
				newList->mChilds.back()->mParent = newList;
			}
			return newList;
		}*/

		//-------------------------------------------------------------------------------------------

		DefinitionNode::DefinitionNode(const ASTNodeType aType, const Ident &aName, ASTNode * aDefinition)
			: ASTNode(aType), mDefinitionName(aName)
		{
			mChilds = std::vector<ASTNode*>(1);
			mChilds[mDefinition] = aDefinition;
		}

		DefinitionNode::~DefinitionNode()
		{
			delete mChilds[mDefinition];
		}

		void DefinitionNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode * DefinitionNode::copy() const
		{
			auto copy = new DefinitionNode(getType(),
				mDefinitionName,
				mChilds[mDefinition] ? mChilds[mDefinition]->copy() : nullptr);
			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-----------------------------------------------------------

		NameRefNode::NameRefNode(const Ident &aTypeName, const ASTNodeType aNodeType, ListNode * aParams)
			: ASTNode(aNodeType), mTypeName(aTypeName)
		{
			mChilds = std::vector<ASTNode*>(2);
			mChilds[mParameters] = aParams;
			mChilds[mTarget] = nullptr;
		}

		NameRefNode::~NameRefNode()
		{
			delete mChilds[mParameters];
		}

		void NameRefNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode * NameRefNode::copy() const
		{
			auto copy = new NameRefNode(mTypeName, getType(),
				mChilds[mParameters] ? static_cast<ListNode*>(mChilds[mParameters])->copy() : nullptr);
			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-------------------------------------------------------------------------------------------

		ConstructorNode::ConstructorNode(const Ident &aName, ListNode * aCtorParameters, const Ident &aCtorResultTypeName)
			: ASTNode(Constructor),
			mName(aName),
			mCtorResultTypeName(aCtorResultTypeName)
		{
			mChilds = std::vector<ASTNode*>(1);
			mChilds[mCtorParameters] = aCtorParameters;
		}

		void ConstructorNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		ConstructorNode::~ConstructorNode()
		{
			delete mChilds[mCtorParameters];
		}

		/*ASTNode * ConstructorNode::copy() const
		{
			auto copy = new ConstructorNode(mName, mChilds[mCtorParameters] ? static_cast<ListNode*>(mChilds[mCtorParameters])->copy() : nullptr, mCtorResultTypeName);
			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-------------------------------------------------------------------------------------------

		DataNode::DataNode(const Ident &aTypeName, ListNode * aTypeDefs, ListNode * aTypeParams, ListNode * aConstructors)
			: ASTNode(DataTypeDefinitionBlock),	mTypeName(aTypeName)
		{
			mChilds = std::vector<ASTNode*>(3);
			mChilds[mConstructors] = aConstructors;
			mChilds[mTypeDefinitions] = aTypeDefs;
			mChilds[mTypeParameters] = aTypeParams;
		}

		DataNode::~DataNode()
		{
			delete mChilds[mConstructors];
			delete mChilds[mTypeDefinitions];
			delete mChilds[mTypeParameters];
		}

		void DataNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode * DataNode::copy() const
		{
			auto copy = new DataNode(mTypeName,
				mChilds[mTypeDefinitions] ? static_cast<ListNode*>(mChilds[mTypeDefinitions])->copy() : nullptr,
				mChilds[mTypeParameters] ? static_cast<ListNode*>(mChilds[mTypeParameters])->copy() : nullptr,
				mChilds[mConstructors] ? static_cast<ListNode*>(mChilds[mConstructors])->copy() : nullptr);

			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-------------------------------------------------------------------------------------------

		FunctionNode::FunctionNode(const Ident &aFuncName, ListNode * aDefinitions, ListNode * aFormalParams)
			: ASTNode(FunctionBlock), mFuncName(aFuncName)
		{
			mChilds = std::vector<ASTNode*>(2);
			mChilds[mFormalParameters] = (aFormalParams);
			mChilds[mDefinitions] = (aDefinitions);
		}

		FunctionNode::~FunctionNode()
		{
			delete mChilds[mDefinitions];
			delete mChilds[mFormalParameters];
		}

		void FunctionNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*FunctionNode * FunctionNode::copy() const
		{
			auto copy = new FunctionNode(mFuncName,
				mChilds[mDefinitions] ? static_cast<ListNode*>(mChilds[mDefinitions])->copy() : nullptr,
				mChilds[mFormalParameters] ? static_cast<ListNode*>(mChilds[mFormalParameters]->copy()) : nullptr);

			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		DefinitionNode * FunctionNode::getDefinition(const Ident &aName) const
		{
			const auto defList = static_cast<ListNode*>(mChilds[mDefinitions]);
			for (size_t i = defList->mChilds.size(); i--;)
			//for (auto& mDefinition : defList->mChilds)
			{
				// do not use dynamic_cast
				const auto def = static_cast<DefinitionNode *>(defList->mChilds[i]);
				//const auto def = static_cast<DefinitionNode *>(mDefinition);
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
			const auto defList = static_cast<ListNode*>(mChilds[mDefinitions]);
			for (size_t i = defList->mChilds.size(); i--;)
			//for (auto& mDefinition : defList->mChilds)
			{
				const auto def = dynamic_cast<FunctionNode *>(defList->mChilds[i]);
				//const auto def = dynamic_cast<FunctionNode *>(mDefinition);
				if (def)
				{
					functions.push_back(def);
				}
			}

			return functions;
		}

		//-------------------------------------------------------------------------------------------

		FunctionalProgram::FunctionalProgram(ASTNode * aDataDefinitions, FunctionNode * aScheme, ApplicationBlock * aApplication)
		: ASTNode(FunctionalProgramDef)
		{
			mChilds = std::vector<ASTNode*>(3);
			mChilds[mDataDefinitions] = aDataDefinitions;
			mChilds[mScheme] = aScheme;
			mChilds[mApplication] = aApplication;
		}

		FunctionalProgram::~FunctionalProgram()
		{
			delete mChilds[mDataDefinitions];
			delete mChilds[mScheme];
			delete mChilds[mApplication];
		}

		void FunctionalProgram::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode * FunctionalProgram::copy() const
		{
			auto copy = new FunctionalProgram(
				mChilds[mDataDefinitions] ? mChilds[mDataDefinitions]->copy() : nullptr,
				mChilds[mScheme] ? static_cast<FunctionNode*>(mChilds[mScheme])->copy() : nullptr,
				mChilds[mApplication] ? static_cast<ApplicationBlock*>(mChilds[mApplication])->copy() : nullptr);

			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		//-------------------------------------------------------------------------------------------

		ApplicationBlock::ApplicationBlock(NameRefNode * aRunSchemeName, ASTNode * aSchemeParameters, ListNode * aDataVarDefs)
		: ASTNode(Application)
		{
			mChilds = std::vector<ASTNode*>(3);
			mChilds[mRunSchemeName] = aRunSchemeName;
			mChilds[mSchemeParameters] = aSchemeParameters;
			mChilds[mDataVarDefinitions] = aDataVarDefs;
		}

		ApplicationBlock::~ApplicationBlock()
		{
			delete mChilds[mRunSchemeName];
			delete mChilds[mSchemeParameters];
			delete mChilds[mDataVarDefinitions];
		}

		/*ApplicationBlock * ApplicationBlock::copy() const
		{
			auto copy = new ApplicationBlock(static_cast<NameRefNode*>(mChilds[mRunSchemeName]), 
				mChilds[mSchemeParameters] ? mChilds[mSchemeParameters]->copy() : nullptr,
				mChilds[mDataVarDefinitions] ? static_cast<ListNode*>(mChilds[mDataVarDefinitions])->copy() : nullptr);

			for (auto& child : copy->mChilds)
				child->mParent = copy;
			return copy;
		}*/

		void ApplicationBlock::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		//-------------------------------------------------------------------------------------------

		void ConstantNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		/*ASTNode * ConstantNode::copy() const
		{
			return new ConstantNode(getType(), mIdent);
		}*/

		bool ConstantNode::isNatural() const
		{
			return getType() == IntConstant && atoi(mIdent.getStr().c_str()) > 0;
		}
	}
}
