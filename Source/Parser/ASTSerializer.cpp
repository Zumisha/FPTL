#include <fstream>
#include <string>

#include "ASTSerializer.h"
#include "Ident.h"
#include "Nodes.h"
#include "Utils/FileStreamHelper.h"
#include "Utils/XmlHelper.h"

namespace FPTL
{
	namespace Parser
	{
		void ASTSerializer::serialize(ASTNode* root)
		{
			Utils::setPermissions(serialization_path);

			mFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				mFile.open(serialization_path, std::ios::out);
				astSerialize(root);
				mFile.close();
			}
			catch (const std::ios_base::failure& exc)
			{
				throw std::runtime_error(Utils::getfStreamError(mFile));
			}
		}

		void ASTSerializer::astSerialize(ASTNode* root)
		{
			if (root == nullptr) return;

			const std::string xml_element_name = ASTNode::NodeTypeToString(root->getType());

			Utils::OpenTag(mFile, xml_element_name);
			{
				root->handle(this);

				if (!root->mChilds.empty())
				{
					Utils::OpenTag(mFile, CHILDS);
					{
						for (size_t i = 0; i < root->mChilds.size(); ++i)
						{
							if (root->mChilds[i] == nullptr) continue;

							Utils::OpenTag(mFile, root->childNameToString(i));
							astSerialize(root->mChilds[i]);
							Utils::CloseTag(mFile, root->childNameToString(i));
						}
					}
					Utils::CloseTag(mFile, CHILDS);
				}
			}
			Utils::CloseTag(mFile, xml_element_name);
		}

		void ASTSerializer::handle(ExpressionNode* aExpressionNode)
		{
		}

		void ASTSerializer::handle(ConditionNode* aConditionNode)
		{
		}

		void ASTSerializer::handle(ConstantNode* aConstantNode)
		{
			mFile << "<Value>" << aConstantNode->getConstant().getStr() << "</Value>";
		}

		void ASTSerializer::handle(ListNode* aNode)
		{
		}

		void ASTSerializer::handle(DefinitionNode* aDefinitionNode)
		{
			mFile << "<Name>" << aDefinitionNode->getDefinitionName().getStr() << "</Name>";
		}

		void ASTSerializer::handle(NameRefNode* aNameRefNode)
		{
			mFile << "<Name>" << aNameRefNode->getName().getStr() << "</Name>";
			if (aNameRefNode->mTarget != nullptr)
			{
				const std::string xml_element_name = ASTNode::NodeTypeToString(aNameRefNode->mTarget->getType());

				Utils::OpenTag(mFile, xml_element_name);
				aNameRefNode->mTarget->handle(this);
				Utils::CloseTag(mFile, xml_element_name);
			}
		}

		void ASTSerializer::handle(ConstructorNode* aFunctionNode)
		{
			mFile << "<Name>" << aFunctionNode->getCtorName().getStr() << "</Name>";
			mFile << "<Type Name>" << aFunctionNode->getCtorResultTypeName().getStr() << "</Type Name>";
		}

		void ASTSerializer::handle(DataNode* aDataNode)
		{
			mFile << "<Name>" << aDataNode->getDataName().getStr() << "</Name>";
		}

		void ASTSerializer::handle(FunctionNode* aFunctionNode)
		{
			mFile << "<Name>" << aFunctionNode->getFuncName().getStr() << "</Name>";
		}

		void ASTSerializer::handle(ApplicationBlock* aApplicationBlock)
		{
		}

		void ASTSerializer::handle(FunctionalProgram* aFuncProgram)
		{
		}
	}
}
