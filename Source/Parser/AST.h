#pragma once

#include <utility>
#include "DataTypes/TypeInfo.h"
#include "Ident.h"

namespace FPTL 
{
	namespace Parser 
	{
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
				Unknown = 0,				// Заглушка. Если что-то в парсере реализовано, а дальше нет.

				FunctionalProgramDef,		// вся система функциональных уравнений (программа)

				DataTypeDefinitionsBlocks,	// список блоков АТД
				DataTypeDefinitionBlock,	// блок АТД
				ConstructorsDefinitionList,	// список определений конструкторов АТД
				Constructor,				// имя конструктора
				ConstructorParametersList,	// конструкция, оборачиваемая конструктором

				TypeExpression,				// композиция объединения множеств АТД
				TypeExpressionsList,		// список фактических параметров параметризованного АТД
				TypesDefinitionList,		// список определений АТД
				DefinitionsList,			// список функциональных уравнений

				// DefinitionNode
				TypeParametersList,			// список формальных параметров параметризованного АТД
				TypeParameterDefinition,	// формальный параметр параметризованного АТД
				TypeDefinition,				// определение АТД
				TypeConstructorDefinition,	// определение конструктора АТД
				Definition,					// функциональное уравнение
				InputVarDefinition,			// определение входного параметра, передаваемого в схему в блоке Application
				FunctionParameterDefinition,// формальный параметр функционала или схемы

				VariantTerm,				// композиция ортогонального объединения графиков
				ConditionTerm,				// условная композиция
				CompositionTerm,			// параллельная композиция
				SequentialTerm,				// последовательная композиция
				FormalParametersList,		// список формальных параметров функционала или схемы
				FunctionBlock,				// блок Fun
				FuncArgumentsList,			// список фактических параметров функционала или схемы

				// NameRefNode
				BaseType,					// базовый тип данных
				Template,					// параметризованный АТД
				Type,						// АТД
				ConstructorName,			// конструктор
				DestructorName,				// деструктор
				BuildInFunction,			// функция стандартной библиотеки
				FuncObjectName,				// пользовательская функция
				TypeParamName,				// фактический параметр параметризованного АТД
				FuncObjectWithParameters,	// пользовательская функция с параметрами (функционал)
				InputVarName,				// входной параметр, передаваемый в схему в блоке Application
				FuncParameterName,			// фактический параметр функционала или схемы
				RunningSchemeName,			// схема, запускаемая в блоке Application (%)

				Application,				// блок Application
				InputVarDefinitionList,		// список определений входного параметра, передаваемого в схему в блоке Application
				InputVarList,				// операция преобразования списка входных параметров, 
											// передаваемых в схему в блоке Application, в кортеж
				// ConstantNode
				TupleElemNumber,			// Выбор элемента из кортежа
				DoubleConstant,				// Real
				FloatConstant,				// Real
				StringConstant,				// String
				IntConstant,				// Integer
				LongLongConstant,			// Real
				TrueValue,					// True
				FalseValue,					// False

				// ExpressionNode
				ValueComposition,			// кортеж значений
				ValueConstructor			// конструктор какого-либо данного
			};

			static std::string NodeTypeToString(ASTNodeType a_type)
			{
				switch (a_type)
				{
				case FunctionalProgramDef:
					return "FunctionalProgramDef";
				case DataTypeDefinitionsBlocks:
					return "DataTypeDefinitionsBlocks";
				case DataTypeDefinitionBlock:
					return "DataTypeDefinitionBlock";
				case ConstructorsDefinitionList:
					return "ConstructorsDefinitionList";
				case Constructor:
					return "Constructor";
				case ConstructorParametersList:
					return "ConstructorParametersList";
				case TypeExpression:
					return "TypeExpression";
				case TypeExpressionsList:
					return "TypeExpressionsList";
				case TypesDefinitionList:
					return "TypesDefinitionList";
				case DefinitionsList:
					return "DefinitionsList";
				case TypeParametersList:
					return "TypeParametersList";
				case TypeParameterDefinition:
					return "TypeParameterDefinition";
				case TypeDefinition:
					return "TypeDefinition";
				case TypeConstructorDefinition:
					return "TypeConstructorDefinition";
				case Definition:
					return "Definition";
				case InputVarDefinition:
					return "InputVarDefinition";
				case FunctionParameterDefinition:
					return "FunctionParameterDefinition";
				case VariantTerm:
					return "VariantTerm";
				case ConditionTerm:
					return "ConditionTerm";
				case CompositionTerm:
					return "CompositionTerm";
				case SequentialTerm:
					return "SequentialTerm";
				case FormalParametersList:
					return "FormalParametersList";
				case FunctionBlock:
					return "FunctionBlock";
				case FuncArgumentsList:
					return "FuncArgumentsList";
				case BaseType:
					return "BaseType";
				case Template:
					return "Template";
				case Type:
					return "Type";
				case ConstructorName:
					return "ConstructorName";
				case DestructorName:
					return "DestructorName";
				case BuildInFunction:
					return "BuildInFunction";
				case FuncObjectName:
					return "FuncObjectName";
				case TypeParamName:
					return "TypeParamName";
				case FuncObjectWithParameters:
					return "FuncObjectWithParameters";
				case InputVarName:
					return "InputVarName";
				case FuncParameterName:
					return "FuncParameterName";
				case RunningSchemeName:
					return "RunningSchemeName";
				case Application:
					return "Application";
				case InputVarDefinitionList:
					return "InputVarDefinitionList";
				case InputVarList:
					return "InputVarList";
				case TupleElemNumber:
					return "TupleElemNumber";
				case DoubleConstant:
					return "DoubleConstant";
				case FloatConstant:
					return "FloatConstant";
				case StringConstant:
					return "StringConstant";
				case IntConstant:
					return "IntConstant";
				case LongLongConstant:
					return "LongLongConstant";
				case TrueValue:
					return "TrueValue";
				case FalseValue:
					return "FalseValue";
				case ValueComposition:
					return "ValueComposition";
				case ValueConstructor:
					return "ValueConstructor";
				case Unknown:
				default:
					return "Unknown";
				}
			}

			explicit ASTNode(const ASTNodeType& aType)
			: mParent(nullptr), mType(aType), mCyclicIndex(0) {}

			virtual ~ASTNode() = default;

			ASTNodeType getType() const { return mType; }

			virtual void accept(class NodeVisitor* aVisitor) = 0;
			virtual void handle(class NodeHandler* aVisitor) = 0;
			virtual std::string childNameToString(size_t) = 0;

			// Возвращает количество циклов, в которых состоит эта вершина.
			size_t cyclicIndex() const { return mCyclicIndex; }

			void increaseCyclicIndex() { mCyclicIndex++; }

			bool isRecursive() const { return mCyclicIndex > 0; }

			// Некоторые узлы дерева могут иметь параметры, например функции и типы данных.
			// Данный метод упрощает проверку числа параметров.
			virtual int numParameters() const { return 0; }

			// Информация о типе узла.
			std::vector<Runtime::TypeInfo> getTypeTuple() const { return mTypeTuple; }
			void setTypeTuple(const std::vector<Runtime::TypeInfo> & aTuple) { mTypeTuple = aTuple; }

			// deleted
			ASTNode(const ASTNode &) = delete;
			ASTNode & operator=(const ASTNode &) = delete;
			const ASTNode * mParent;
			std::vector<ASTNode*> mChilds;

		private:
			ASTNodeType mType;
			size_t mCyclicIndex;
			std::vector<Runtime::TypeInfo> mTypeTuple;
		};
	}
}
