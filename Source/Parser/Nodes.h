#pragma once

#include "AST.h"
#include "Ident.h"

namespace FPTL
{
	namespace Parser
	{
		class Support;

		//-------------------------------------------------------------------------------------
		// Выражение.

		class ExpressionNode : public ASTNode
		{
		public:
			ExpressionNode(ASTNodeType aType, ASTNode * aLeft, ASTNode * aRight);
			~ExpressionNode();

			ASTNode * getLeft() const { return mChilds[mLeft]; }
			ASTNode * getRight() const { return mChilds[mRight]; }

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			std::string childNameToString(size_t child) override;

			enum
			{
				mLeft,
				mRight
			};
		};

		class ConditionNode : public ASTNode
		{
		public:

			ConditionNode(const ASTNodeType aType, ASTNode* aLeft, ASTNode* aRight, ASTNode* aMiddle);
			~ConditionNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			ASTNode * getThen() const { return mChilds[mThen]; }
			ASTNode * getElse() const { return mChilds[mElse]; }
			ASTNode * getCond() const { return mChilds[mCond]; }

			std::string childNameToString(size_t child) override;

			enum
			{
				mThen,
				mElse,
				mCond
			};
		};

		//-------------------------------------------------------------------------------------
		// Описание константы.

		class ConstantNode : public ASTNode
		{
		public:

			ConstantNode(const ASTNodeType aType, const Ident &aConstant) :
				ASTNode(aType), mIdent(aConstant) {}

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			bool isNatural() const;

			Ident getConstant() const { return mIdent; }

			std::string childNameToString(size_t) override;

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mIdent;
			}

		private:
			Ident          mIdent;
		};

		//-------------------------------------------------------------------------------------
		// Списковая синтаксическая структура.
		// При обработке АСД обходить только строго в обратном порядке!
		class ListNode : public ASTNode
		{
		public:

			explicit ListNode(const ASTNodeType aType) : ASTNode(aType) {}
			~ListNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			ListNode* addElement(ASTNode * aElem)
			{
				if (aElem) mChilds.push_back(aElem);
				//if (aElem) mChilds.insert(mChilds.begin(), aElem);
				return this;
			}

			size_t getNumElements() const
			{
				return mChilds.size();
			}

			std::string childNameToString(size_t) override;

		};

		//-------------------------------------------------------------------------------------
		// Определение (типового уравнения, функциональной переменной, типового или функционального параметра, переменной).

		class DefinitionNode : public ASTNode
		{
		public:

			DefinitionNode(ASTNodeType aType, const Ident &aName, ASTNode * aDefinition);
			~DefinitionNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			Ident         getDefinitionName() const { return mDefinitionName; }
			ASTNode *     getDefinition() const { return mChilds[mDefinition]; }

			std::string childNameToString(size_t child) override;

			enum
			{
				mDefinition
			};

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mDefinitionName;
			}

		private:
			Ident mDefinitionName;
		};

		//-------------------------------------------------------------------------------------
		// Ссылка на именованный объект (тип, конструктор, имя функции или функциональной переменной, имя встроенной функции).

		class NameRefNode : public ASTNode
		{
		public:

			NameRefNode(const Ident &aTypeName, ASTNodeType aNodeType, ListNode * aParams);
			~NameRefNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			Ident getName() const { return mTypeName; }
			ListNode* getParameters() const { return static_cast<ListNode*>(mChilds[mParameters]); }
			size_t numParameters() const override
			{
				return mChilds[mParameters] ? static_cast<size_t>(static_cast<ListNode*>(mChilds[mParameters])->mChilds.size()) : 0;
			}

			std::string childNameToString(size_t child) override;

			enum
			{
				mParameters
			};

			ASTNode* mTarget;

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mTypeName;
			}

		private:

			Ident mTypeName;
		};

		//-------------------------------------------------------------------------------------
		// Конструктор. FIXME: этот класс не нужен в новой нотации описания конструкторов.

		class ConstructorNode : public ASTNode
		{
		public:

			ConstructorNode(const Ident &aName, ListNode * aCtorParameters, const Ident &aCtorResultTypeName);
			~ConstructorNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			Ident                 getCtorName() const { return mName; }
			Ident                 getCtorResultTypeName() const { return mCtorResultTypeName; }
			ListNode *            getCtorParameters() const { return static_cast<ListNode*>(mChilds[mCtorParameters]); }

			std::string childNameToString(size_t child) override;

			enum
			{
				mCtorParameters
			};

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mName << "; " << mCtorResultTypeName;
			}

		private:
			Ident mName;
			Ident mCtorResultTypeName;
		};

		//-------------------------------------------------------------------------------------
		// Блок описания данных.

		class DataNode : public ASTNode
		{
		public:

			DataNode(const Ident &aTypeName, ListNode * aTypeDefs, ListNode * aTypeParams, ListNode * aConstructors);
			~DataNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			ListNode *      getConstructors() const { return static_cast<ListNode*>(mChilds[mConstructors]); }
			Ident           getDataName() const { return mTypeName; }
			ListNode *      getTypeDefs() const { return static_cast<ListNode*>(mChilds[mTypeDefinitions]); }
			ListNode *      getTypeParams() const { return static_cast<ListNode*>(mChilds[mTypeParameters]); }

			size_t numParameters() const override
			{
				return mChilds[mTypeParameters] ? static_cast<size_t>(static_cast<ListNode*>(mChilds[mTypeParameters])->mChilds.size()) : 0;
			}

			std::string childNameToString(size_t child) override;

			enum
			{
				mConstructors,
				mTypeDefinitions,
				mTypeParameters
			};

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mTypeName;
			}

		private:
			Ident mTypeName;
		};

		//-------------------------------------------------------------------------------------
		// Описание функции или схемы.

		class FunctionNode : public ASTNode
		{
		public:

			FunctionNode(const Ident &aFuncName, ListNode * aDefinitions, ListNode * aFormalParams);
			~FunctionNode();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			Ident             getFuncName() const { return mFuncName; }
			ListNode *        getDefinitions() const { return static_cast<ListNode*>(mChilds[mDefinitions]); }
			ListNode *        getFormalParameters() const { return static_cast<ListNode*>(mChilds[mFormalParameters]); }
			DefinitionNode *  getDefinition(const Ident &aName) const;

			size_t numParameters() const override
			{
				return mChilds[mFormalParameters] ? static_cast<size_t>(static_cast<ListNode*>(mChilds[mFormalParameters])->mChilds.size()) : 0;
			}

			std::string childNameToString(size_t child) override;

			std::vector<FunctionNode *>    getFunctionNodes() const;

			enum
			{
				mDefinitions,
				mFormalParameters
			};

			void serialize(std::ostream& aStream, const ASTNode* node) const override
			{
				aStream << NodeTypeToString(node->getType()) << ": " << mFuncName;
			}

		private:
			Ident mFuncName;
		};

		//-------------------------------------------------------------------------------------
		// Описание входных данных схемы.

		class ApplicationBlock : public ASTNode
		{
		public:

			ApplicationBlock(NameRefNode * aRunSchemeName, ASTNode * aSchemeParameters, ListNode * aDataVarDefs);
			~ApplicationBlock();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			NameRefNode * getRunningSchemeName() const { return static_cast<NameRefNode*>(mChilds[mRunSchemeName]); }
			ASTNode *     getSchemeParameters() const { return mChilds[mSchemeParameters]; }
			ListNode *    getDataVarDefinitions() const { return static_cast<ListNode*>(mChilds[mDataVarDefinitions]); }

			std::string childNameToString(size_t child) override;

			enum
			{
				mRunSchemeName,
				mSchemeParameters,
				mDataVarDefinitions
			};
		};

		//-------------------------------------------------------------------------------------
		// Описание функциональной программы.

		class FunctionalProgram : public ASTNode
		{
		public:
			FunctionalProgram(ASTNode * aDataDefinitions, FunctionNode * aScheme, ApplicationBlock * aApplication);
			~FunctionalProgram();

			void handle(NodeVisitor* aHandler) override;
			ASTNode* getChild(NodeHandler* aHandler, size_t childNum) override;
			size_t getChildIndex(NodeHandler* aHandler, ASTNode* child) override;
			void intermediateProcessing(NodeHandler* aHandler, size_t childNum) override;
			void ChildHandled(NodeHandler* aHandler, size_t childNum) override;

			ListNode*             getDataDefinitions() const { return static_cast<ListNode*>(mChilds[mDataDefinitions]); }
			FunctionNode*         getScheme() const { return static_cast<FunctionNode*>(mChilds[mScheme]); }
			ApplicationBlock*     getApplication() const { return static_cast<ApplicationBlock*>(mChilds[mApplication]); }

			std::string childNameToString(size_t child) override;
			//ASTNode * copy() const override;

			enum
			{
				mDataDefinitions,
				mScheme,
				mApplication
			};
		};
	}
}
