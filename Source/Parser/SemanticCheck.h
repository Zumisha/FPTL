#pragma once

#include <map>
#include <algorithm>
#include <cassert>

#include "Support.h"
#include "Nodes.h"
#include "NodeVisitor.h"

namespace FPTL
{
	namespace Parser
	{
		//
		// NamesChecker. Проверяет было ли используемое имя определено в текущем контексте (данное, функция).
		//
		class NamesChecker : public NodeVisitor
		{
			struct STermDescriptor
			{
				Ident TermName;
				NameRefNode * Node;

				bool operator<(const STermDescriptor & aOther) const { return TermName < aOther.TermName; }
			};

			struct SLexicalContext
			{
				FunctionNode * currentFunction;
				std::vector<STermDescriptor> TermsList;
				std::map<Ident, ASTNode*> DefinitionsList;

				SLexicalContext() : currentFunction(nullptr)
				{
				}

				void clear()
				{
					TermsList.clear();
					DefinitionsList.clear();
					currentFunction = nullptr;
				}

				bool insertName(const Ident & aIdent, ASTNode * aNode)
				{
					return DefinitionsList.insert(std::make_pair(aIdent, aNode)).second;
				}
			};

		public:

			NamesChecker(Support * aSupport, ASTNode * root);

			void visit(DataNode * aDataNode) override;
			void visit(FunctionNode * aFunctionNode) override;
			void visit(DefinitionNode * aDefinitionNode) override;
			void visit(NameRefNode * aNameNode) override;
			void visit(ApplicationBlock * aApplicationBlock) override;

		private:

			void pushContext();
			void pushContext(FunctionNode * function);
			void popContext();
			void checkName(STermDescriptor & aTermDesc);
			void checkNames();

			SLexicalContext mContext;
			std::vector<SLexicalContext> mContextStack;

			Support * mSupport;
		};

		//
		// Находит рекурсивные типовые уравнения, выставляет им ненулевой циклический индекс.
		//
		class RecursionFinder : public NodeVisitor
		{
		public:
			RecursionFinder(ASTNode * root)
			{
				process(root);
			}

			void visit(DefinitionNode * aDefinitionNode) override
			{
				mTestDefinitions.push_back(aDefinitionNode->getDefinitionName());

				if (aDefinitionNode->getType() == ASTNode::Definition)
				{
					process(aDefinitionNode->getDefinition());
				}

				mTestDefinitions.pop_back();
			}

			void visit(NameRefNode * aNameRefNode) override
			{
				if (aNameRefNode->getType() == ASTNode::FuncObjectName || aNameRefNode->getType() == ASTNode::FuncParameterName)
				{
					ASTNode * target = aNameRefNode->getTarget();

					// Отлавливаем рекурсию.
					if (std::find(mTestDefinitions.begin(), mTestDefinitions.end(), aNameRefNode->getName()) != mTestDefinitions.end())
					{
						target->increaseCyclicIndex();
					}
					else
					{
						process(target);
					}
				}

				if (aNameRefNode->getType() == ASTNode::FuncObjectWithParameters)
				{
					// Ищем рекурсию среди функциональных параметров.
					process(aNameRefNode->getParameters());
				}
			}

		private:

			std::vector<Ident> mTestDefinitions;
		};
	}
}
