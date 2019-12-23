#pragma once

#include <string>
#include <fstream>

#include "AST.h"
#include "NodeHandler.h"

namespace FPTL
{
	namespace Parser
	{
		class ASTSerializer : NodeHandler
		{
		public:
			inline static const std::string serialization_path = "AST.xml";
			inline static const std::string CHILDS = "Childs";

			void serialize(ASTNode* root);

		private:
			std::fstream mFile;

			void astSerialize(ASTNode* root);

			void handle(ExpressionNode* aExpressionNode) override;
			void handle(ConditionNode* aConditionNode) override;
			void handle(ConstantNode* aConstantNode) override;
			void handle(ListNode* aNode) override;
			void handle(DefinitionNode* aDefinitionNode) override;
			void handle(NameRefNode* aNameRefNode) override;
			void handle(ConstructorNode* aFunctionNode) override;
			void handle(DataNode* aDataNode) override;
			void handle(FunctionNode* aFunctionNode) override;
			void handle(ApplicationBlock* aApplicationBlock) override;
			void handle(FunctionalProgram* aFuncProgram) override;
		};
	}
}
