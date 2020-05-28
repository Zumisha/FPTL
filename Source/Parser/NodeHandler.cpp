#include "NodeHandler.h"
#include <iostream>

namespace FPTL
{
	namespace Parser
	{
		void NodeHandler::Handle(ASTNode* astRoot)
		{
			ChildToParent.clear();			
			ASTNode* node = astRoot;
			bool firstAttempt = true;
			size_t childIndex = 0;

			while (true)
			{
				ASTNode* nextNode = nullptr;
				// останавливаемся только если нет ни зарезервированных узлов, ни динамически генерируемых
				// в конце постобработка узла, поэтому до размера включительно
				while (childIndex <= node->mChilds.size() && nextNode == nullptr ||
					firstAttempt == true) // случай, когда динамические есть
				{
					firstAttempt = false;
					node->intermediateProcessing(this, childIndex);
					nextNode = node->getChild(this, childIndex);
					childIndex++;
				}
				firstAttempt = true;
				if (nextNode != nullptr)
				{	// to child
					ChildToParent.emplace_back(nextNode, node);
					node = nextNode;
					childIndex = 0;
				}
				else // to parent
				{	
					if (node == astRoot) return;
					ASTNode* parent = getParent(node);
					childIndex = parent->getChildIndex(this, node);
					if (childIndex == static_cast<size_t>(-1)) throw std::exception("Critical error in AST handling");
					node = parent;
					node->ChildHandled(this, childIndex);
					childIndex++;
				}
				if (node != nullptr)
					std::cout << childIndex << "/" << node->mChilds.size() << ". " << node << std::endl;
			}
		}

		ASTNode* NodeHandler::getParent(ASTNode* child)
		{
			//for (size_t i = ChildToParent.size(); i--;)
			for (auto pair = ChildToParent.rbegin(); pair != ChildToParent.rend(); ++pair)
			{
				if (pair->first == child)
				{
					ASTNode* parent = pair->second;
					ChildToParent.erase(std::next(pair).base());
					return parent;
				}
			}
			return nullptr;
		}
	}
}
