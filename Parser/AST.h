#ifndef AST_H
#define AST_H

#include <vector>

#include "Types.h"

namespace FPTL {
	namespace Parser {

		class TTuple;

		//
		// Объекты данного класса и его потомков нельзя создавать только в динамической памяти.
		//
		class ASTNode
		{
		public:

			// Варианты узлов абстрактного синтаксического дерева.
			enum ASTNodeType
			{
				Unknown = 0,

				FunctionalProgramDef,

				DataTypeDefinitionsBlocks,
				DataTypeDefinitionBlock,
				TypeParametersList,
				ConstructorsDefinitionList,
				Constructor,
				ConstructorParametersList,

				TypeExpression,
				TypeExpressionsList,
				TypesDefinitionList,
				DefinitionsList,

				// DefinitionNode
				TypeParameterDefinition,
				TypeDefinition,
				TypeConstructorDefinition,
				Definition,
				InputVarDefinition,
				FunctionParameterDefinition,

				VariantTerm,
				ConditionTerm,
				CompositionTerm,
				SequentialTerm,
				FormalParametersList,
				FunctionBlock,
				FuncArgumentsList,

				// NameRefNode
				BaseType,
				Template,
				Type,               // typeName
				ConstructorName,
				DestructorName,
				BuildInFunction,
				FuncObjectName,
				TypeParamName,
				FuncObjectWithParameters, // ParametrizedCall
				InputVarName,
				FuncParameterName,
				RunningSchemeName,

				Application,
				InputVarDefinitionList,
				InputVarList,
				InputVar,

				// ConstantNode
				TupleElemNumber,
				DoubleConstant,
				FloatConstant,
				StringConstant,
				IntConstant,
				LongLongConstant,
				TrueValue,
				FalseValue,

				// ExpressionNode
				ValueComposition,
				ValueConstructor
			};

			explicit ASTNode(const ASTNodeType aType) : mType(aType), mCyclicIndex(0) {}
			virtual ~ASTNode() = default;

			ASTNodeType getType() const { return mType; }

			virtual void accept(class NodeVisitor * aVisitor) = 0;

			virtual ASTNode * copy() const = 0;

			// Возвращает количество циклов, в которых состоит эта вершина.
			size_t cyclicIndex() const { return mCyclicIndex; }

			void increaseCyclicIndex() { mCyclicIndex++; }

			bool isRecursive() const { return mCyclicIndex > 0; }

			// Некоторые узлы дерева могут иметь параметры, например функции и типы данных.
			// Данный метод упрощает проверку числа параметров.
			virtual int numParameters() const { return 0; }

			// Информация о типе узла.
			TTuple getTypeTuple() const { return mTypeTuple; }
			void setTypeTuple(const TTuple & aTuple) { mTypeTuple = aTuple; }

			// deleted
			ASTNode(const ASTNode &) = delete;
			ASTNode & operator=(const ASTNode &) = delete;

		private:
			ASTNodeType mType;
			size_t mCyclicIndex;
			TTuple mTypeTuple;
		};

	} // Parser
} // FPTL

#endif