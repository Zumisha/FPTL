#include "Generated/parser.tab.hh"

#include "Support.h"
#include "Nodes.h"
#include "NodeVisitor.h"
#include "NodeHandler.h"

namespace FPTL {
	namespace Parser {

		ExpressionNode::ExpressionNode(const ASTNodeType aType, ASTNode* aLeft, ASTNode* aRight)
			: ASTNode(aType)
		{
			mChilds = std::vector<ASTNode*>(3);
			mChilds[mLeft] = aLeft;
			mChilds[mRight] = aRight;
		}

		ExpressionNode::~ExpressionNode()
		{
			delete mChilds[mLeft];
			delete mChilds[mRight];
		}

		void ExpressionNode::accept(NodeVisitor* aVisitor)
		{
			aVisitor->visit(this);
		}

		void ExpressionNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string ExpressionNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mLeft:
				return "Left";
			case mRight:
				return "Right";
			default:
				return "Error!";
			}
		}

		//-------------------------------------------------------------------------------------------

		ConditionNode::ConditionNode(const ASTNodeType aType, ASTNode* aLeft, ASTNode* aRight, ASTNode* aMiddle)
				: ASTNode(aType)
			{
				mChilds = std::vector<ASTNode*>(3);
				mChilds[mThen] = aLeft;
				mChilds[mElse] = aRight;
				mChilds[mCond] = aMiddle;
			}

			ConditionNode::~ConditionNode()
			{
				delete mChilds[mThen];
				delete mChilds[mElse];
				delete mChilds[mCond];
			}

			void ConditionNode::accept(NodeVisitor * aVisitor)
			{
				aVisitor->visit(this);
			}

			void ConditionNode::handle(NodeHandler* aHandler)
			{
				aHandler->handle(this);
			}

			std::string ConditionNode::childNameToString(size_t child)
			{
				switch (child)
				{
				case mThen:
					return "Then";
				case mElse:
					return "Else";
				case mCond:
					return "Else";
				default:
					return "Error!";
				}
			}

		//-------------------------------------------------------------------------------------------

		void ConstantNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		void ConstantNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		bool ConstantNode::isNatural() const
		{
			return getType() == IntConstant && atoi(mIdent.getStr().c_str()) > 0;
		}

		std::string ConstantNode::childNameToString(size_t)
		{
			return "Error!";
		}

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

		void ListNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string ListNode::childNameToString(size_t)
		{
			return "Node";
		}

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

		void DefinitionNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string DefinitionNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mDefinition:
				return "Definition";
			default:
				return "Error!";
			}
		}

		//-----------------------------------------------------------

		NameRefNode::NameRefNode(const Ident &aTypeName, const ASTNodeType aNodeType, ListNode * aParams)
			: ASTNode(aNodeType), mTypeName(aTypeName)
		{
			mChilds = std::vector<ASTNode*>(2);
			mChilds[mParameters] = aParams;
			mTarget = nullptr;
		}

		NameRefNode::~NameRefNode()
		{
			delete mChilds[mParameters];
		}

		void NameRefNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		void NameRefNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string NameRefNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mParameters:
				return "Parameters";
			default:
				return "Error!";
			}
		}

		//-------------------------------------------------------------------------------------------

		ConstructorNode::ConstructorNode(const Ident &aName, ListNode * aCtorParameters, const Ident &aCtorResultTypeName)
			: ASTNode(Constructor), mName(aName), mCtorResultTypeName(aCtorResultTypeName)
		{
			mChilds = std::vector<ASTNode*>(1);
			mChilds[mCtorParameters] = aCtorParameters;
		}

		void ConstructorNode::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		void ConstructorNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		ConstructorNode::~ConstructorNode()
		{
			delete mChilds[mCtorParameters];
		}

		std::string ConstructorNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mCtorParameters:
				return "ConstructorParameters";
			default:
				return "Error!";
			}
		}

		//-------------------------------------------------------------------------------------------

		DataNode::DataNode(const Ident &aTypeName, ListNode * aTypeDefs, ListNode * aTypeParams, ListNode * aConstructors)
			: ASTNode(DataTypeDefinitionBlock), mTypeName(aTypeName)
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

		void DataNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string DataNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mConstructors:
				return "Constructors";
			case mTypeDefinitions:
				return "TypeDefinitions";
			case mTypeParameters:
				return "TypeParameters";
			default:
				return "Error!";
			}
		}

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

		void FunctionNode::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

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

		std::string FunctionNode::childNameToString(size_t child)
		{
			switch (child)
			{
			case mDefinitions:
				return "Definitions";
			case mFormalParameters:
				return "FormalParameters";
			default:
				return "Error!";
			}
		}

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

		void ApplicationBlock::accept(NodeVisitor * aVisitor)
		{
			aVisitor->visit(this);
		}

		void ApplicationBlock::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string ApplicationBlock::childNameToString(size_t child)
		{
			switch (child)
			{
			case mRunSchemeName:
				return "RunSchemeName";
			case mSchemeParameters:
				return "SchemeParameters";
			case mDataVarDefinitions:
				return "DataVarDefinitions";
			default:
				return "Error!";
			}
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

		void FunctionalProgram::handle(NodeHandler* aHandler)
		{
			aHandler->handle(this);
		}

		std::string FunctionalProgram::childNameToString(size_t child)
		{
			switch (child)
			{
			case mDataDefinitions:
				return "DataDefinitions";
			case mScheme:
				return "Scheme";
			case mApplication:
				return "Application";
			default:
				return "Error!";
			}
		}
	}
}
