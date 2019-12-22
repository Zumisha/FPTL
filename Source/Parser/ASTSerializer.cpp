#include <fstream>
#include <string>
#include <experimental/filesystem>

#include "ASTSerializer.h"
#include "Ident.h"
#include "Nodes.h"
#include "Utils/FileStreamHelper.h"

namespace FPTL
{
	namespace Parser
	{

		bool ASTSerializer::serialize(ASTNode* root)
		{
			if (std::experimental::filesystem::exists(std::experimental::filesystem::status(serialization_path)))
			{
				std::experimental::filesystem::permissions(serialization_path,
					std::experimental::filesystem::perms::add_perms | std::experimental::filesystem::perms::owner_all | std::experimental::filesystem::perms::group_all);
			}

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

			return true;
		}

		void ASTSerializer::astSerialize(ASTNode* root)
		{
			if (root == nullptr) return;

			const std::string xml_element_name = ASTNode::NodeTypeToString(root->getType());
			
			mFile << "<" << xml_element_name << ">";
			{
				root->handle(this);

				if (!root->mChilds.empty())
				{
					mFile << "<" << CHILDS << ">";
					{
						for (size_t i = 0; i < root->mChilds.size(); ++i)
						{
							if (root->mChilds[i] == nullptr) continue;

							mFile << "<" << root->childNameToString(i) << ">";
							astSerialize(root->mChilds[i]);
							mFile << "</" << root->childNameToString(i) << ">";
						}
					}
					mFile << "</" << CHILDS << ">";
				}
			}
			mFile << "</" << xml_element_name << ">";
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
				mFile << "<Target>" << "<" << xml_element_name << ">";
				aNameRefNode->mTarget->handle(this);
				mFile << "</" << xml_element_name << ">" << "</Target>";
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
