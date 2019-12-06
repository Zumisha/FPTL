#include <iostream>
#include "Parser/AST.h"

namespace FPTL
{
	namespace Runtime
	{
		/*
		const size_t K = 3;
		struct KNode {
			int data;
			KNode * c[K];
		};*/
		// Обход к-ичного дерева без использования стека.
		// Редуцированный граф переходов		
		/*void traverseKReduced(Parser::ASTNode * astRoot)
		{
			enum State
			{
				Start,
				Child,
				Parent,
				Calc
			};
			State state = Start;
			Parser::ASTNode* node = astRoot;
			size_t child_ptr = 0;
			Parser::ASTNode** next_ptr;
			do
			{
				switch (state)
				{
				case Start:
					state = Child;
					node = astRoot;
					child_ptr = 0;
					break;
				case Child:
					if (child_ptr == 0)
						std::cout << node->data << ' ';
					if (child_ptr == node->mChilds.size() && node == astRoot)
					{
						state = Parent;
					}
					else if (child_ptr == node->mChilds.size())
					{
						next_ptr = node->mParent->mChilds;
						state = Calc;
					}
					else if (node->mChilds[child_ptr] != nullptr)
					{
						node = *child_ptr;
						child_ptr = node->mChilds;
					}
					else
					{
						++child_ptr;
					}
					break;
				case Calc:
					if (*next_ptr == node)
					{
						++next_ptr;
						state = Parent;
					}
					else
						++next_ptr;
					break;
				case Parent:
					if (node != astRoot)
					{
						child_ptr = next_ptr;
						node = node->mParent;
						state = Child;
					}
					else
						state = Start;
					break;
				}
			} while (state != Start);
		}*/
	}
}
