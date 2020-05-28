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
			mChilds = std::vector<ASTNode*>(2);
			mChilds[mLeft] = aLeft;
			mChilds[mRight] = aRight;
		}

		ExpressionNode::~ExpressionNode()
		{
			delete mChilds[mLeft];
			delete mChilds[mRight];
		}

		void ExpressionNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* ExpressionNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t ExpressionNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void ExpressionNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void ExpressionNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

			void ConditionNode::handle(NodeVisitor* aHandler)
			{
				aHandler->handle(this);
			}
			ASTNode* ConditionNode::getChild(NodeHandler* aHandler, size_t childNum)
			{
				return aHandler->getChild(this, childNum);
			}
			size_t ConditionNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
			{
				return aHandler->getChildIndex(this, child);
			}
			void ConditionNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
			{
				aHandler->intermediateProcessing(this, childNum);
			}
			void ConditionNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
			{
				aHandler->ChildHandled(this, childNum);
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

		void ConstantNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* ConstantNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t ConstantNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void ConstantNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void ConstantNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void ListNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* ListNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t ListNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void ListNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void ListNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void DefinitionNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* DefinitionNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t DefinitionNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void DefinitionNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void DefinitionNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void NameRefNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* NameRefNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t NameRefNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void NameRefNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void NameRefNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void ConstructorNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* ConstructorNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t ConstructorNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void ConstructorNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void ConstructorNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void DataNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* DataNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t DataNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void DataNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void DataNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void FunctionNode::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* FunctionNode::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t FunctionNode::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void FunctionNode::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void FunctionNode::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void ApplicationBlock::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* ApplicationBlock::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t ApplicationBlock::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void ApplicationBlock::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void ApplicationBlock::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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

		void FunctionalProgram::handle(NodeVisitor* aHandler)
		{
			aHandler->handle(this);
		}
		ASTNode* FunctionalProgram::getChild(NodeHandler* aHandler, size_t childNum)
		{
			return aHandler->getChild(this, childNum);
		}
		size_t FunctionalProgram::getChildIndex(NodeHandler* aHandler, ASTNode* child)
		{
			return aHandler->getChildIndex(this, child);
		}
		void FunctionalProgram::intermediateProcessing(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->intermediateProcessing(this, childNum);
		}
		void FunctionalProgram::ChildHandled(NodeHandler* aHandler, size_t childNum)
		{
			aHandler->ChildHandled(this, childNum);
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
