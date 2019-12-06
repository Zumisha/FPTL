#pragma once

#include "DataTypes/TypeInfo.h"

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

			explicit ASTNode(const ASTNodeType aType) : mParent(nullptr), mType(aType), mCyclicIndex(0) {}
			virtual ~ASTNode() = default;

			ASTNodeType getType() const { return mType; }

			virtual void accept(class NodeVisitor * aVisitor) = 0;

			//virtual ASTNode* copy() const = 0;

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