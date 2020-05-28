#pragma once

#include <string>
#include <map>
#include <stack>

#include "Parser/NodeVisitor.h"
#include "DataTypes/TypeInfo.h"

namespace FPTL
{
	namespace Runtime
	{
		class Constructor;

		class ConstructorGenerator : public Parser::NodeVisitor
		{
		public:

			ConstructorGenerator();

			void work(Parser::FunctionalProgram * aFuncProgram);

			void handle(Parser::DataNode * aData) override;
			void handle(Parser::NameRefNode * aNameReference) override;
			void handle(Parser::DefinitionNode * aDefinition) override;

			Constructor * getConstructor(const std::string & aConstructorName) const;
			std::vector<std::string> constructors() const;

		private:

			Parser::DataNode * mCurrentData;

			// Сгенерированные эталонные типы для конструкторов.
			std::map<std::string, std::shared_ptr<Constructor>> mConstructors;

			std::vector<TypeInfo> mTypeTuple;
			std::stack<std::vector<TypeInfo>> mStack;

			// Типовые параметры для типа, определяемого конструкторами.
			std::vector<std::string> mTypeParameters;
		};

	}
}
