// Проверка типов.

#include <string>
#include <list>
#include <algorithm>
#include <cassert>

#include <boost/lexical_cast.hpp>

#include "Types.h"
#include "NodeVisitor.h"
#include "Nodes.h"

namespace FPTL {
namespace Parser {

// Список доступных имен и их типов. Как быть с конструктором?
class TypeLibrary
{
public:

	bool addFunction(const std::string & aFunctionName, const std::pair<TTuple, TTuple> & aType)
	{
		auto lb = mFunctions.lower_bound(aFunctionName);
		auto ub = mFunctions.upper_bound(aFunctionName);

		for (auto elem = lb; elem != ub; ++elem)
		{
			if (elem->second.first == aType.first)
			{
				// Неоднозначность.
				return false;
			}
		}

		mFunctions.insert(std::make_pair(aFunctionName, aType));

		return true;
	}

	bool getType(const std::string & aFunctionName, const TTuple & aInput, TTuple & aOutput) const
	{
		auto lb = mFunctions.lower_bound(aFunctionName);
		auto ub = mFunctions.upper_bound(aFunctionName);

		for (auto elem = lb; elem != ub; ++elem)
		{
			if (elem->second.first == aInput)
			{
				aOutput = elem->second.second;
				return true;
			}
		}

		return false;
	}

private:
	std::hash_multimap<std::string, std::pair<TTuple, TTuple>> mFunctions;
};

// Выводит тип для рекурсивного выражения.
class TypeInferer : public NodeVisitor
{
public:
	TypeInferer(const TTuple & aTuple, const TypeLibrary & aLibrary)
		: mTuple(aTuple), mLibrary(aLibrary)
	{}

	void visit(ExpressionNode * aNode)
	{
		switch (aNode->getType())
		{
			case ASTNode::CompositionTerm:
			{
				TypeInferer left(mTuple, mLibrary);
				left.process(aNode->getLeft());

				TypeInferer right(mTuple, mLibrary);
				right.process(aNode->getRight());
				
				mResult = left.mResult + right.mResult;

				break;
			}

			case ASTNode::SequentialTerm:
			{
				TypeInferer left(mTuple, mLibrary);
				left.process(aNode->getLeft());

				TypeInferer right(left.mResult, mLibrary);
				right.process(aNode->getRight());

				mResult = right.mResult;

				break;
			}

			case ASTNode::ConditionTerm:
			{
				TypeInferer trueBranch(mTuple, mLibrary);
				trueBranch.process(aNode->getRight());

				TypeInferer falseBranch(mTuple, mLibrary);
				falseBranch.process(aNode->getMiddle());
				
				mResult = !trueBranch.mResult.empty() ? trueBranch.mResult : falseBranch.mResult;
				break;
			}
		}
	}

	void visit(DefinitionNode * aNode)
	{
		NodeVisitor::visit(aNode);
	}

	void visit(ConstantNode * aNode)
	{
		// По типу константы определяем тип.
		switch (aNode->getType())
		{
			case ASTNode::TupleElemNumber:
				// TODO: добавить проверку на валидность диапазона.
				mResult = TTuple(1, mTuple.at(boost::lexical_cast<int>(aNode->getConstant().getStr())-1));
				break;

			case ASTNode::IntConstant:
				break;

			case ASTNode::DoubleConstant:
			case ASTNode::FloatConstant:
				break;

			case ASTNode::StringConstant:
				break;

			case ASTNode::TrueValue:
			case ASTNode::FalseValue:
				break;

			default:
				assert(false);
		}
	}

	void visit(NameRefNode * aNode)
	{
		// По входному типу определяем результирующий.
		auto name = aNode->getName().getStr();
		auto target = aNode->getTarget();

		if (!mLibrary.getType(name, mTuple, mResult))
		{
			mLibrary.addFunction(name, std::make_pair(mTuple, TTuple()));

			if (target)
			{
				TypeInferer inferer(mTuple, mLibrary);
				inferer.process(target);

				mResult = inferer.mResult;	
			}
		}
	}

	void visit(FunctionNode * aNode)
	{
		// Начинаем новый вывод с главного уравнения.
		auto mainDefinition = aNode->getDefinition(aNode->getFuncName());

		process(mainDefinition);
	}

	TTuple result() const
	{
		return mResult;
	}

private:
	TypeLibrary mLibrary;
	const TTuple mTuple;
	TTuple mResult;
};

// Производит типовую проверку выражений.
class TypeBuilder : public NodeVisitor
{
public:
	TypeBuilder(const TTuple & aTuple, const TypeLibrary & aLibrary)
		: mTuple(aTuple), mLibrary(aLibrary)
	{}

	void visit(ExpressionNode * aNode)
	{
		switch (aNode->getType())
		{
			case ASTNode::CompositionTerm:
			{
				auto input = mTuple;

				process(aNode->getLeft());

				mTuple = input;
				process(aNode->getRight());

				mTuple = aNode->getLeft()->getTypeTuple() + aNode->getRight()->getTypeTuple();

				break;
			}

			case ASTNode::SequentialTerm:
			{
				process(aNode->getLeft());
				mTuple = aNode->getLeft()->getTypeTuple();

				process(aNode->getRight());
				mTuple = aNode->getRight()->getTypeTuple();

				break;
			}

			case ASTNode::ConditionTerm:
			{
				auto input = mTuple;

				process(aNode->getLeft());

				mTuple = input;
				process(aNode->getRight());

				mTuple = input;
				process(aNode->getMiddle());

				auto left = aNode->getRight()->getTypeTuple();
				auto right =  aNode->getMiddle()->getTypeTuple();
				
				if (left == right)
				{
					mTuple = right;
				}
				else
				{
					mErrorList.push_front("type error in -> expression: " + left.toString() + " incompatibe with " + right.toString());
				}

				break;
			}
		}

		aNode->setTypeTuple(mTuple);

	}

	void visit(DefinitionNode * aNode)
	{
		// Выводим свой тип, и добавляем его в библиотеку.
		TypeInferer inferer(mTuple, mLibrary);
		inferer.process(aNode->getDefinition());

		mLibrary.addFunction(aNode->getDefinitionName().getStr(), std::make_pair(mTuple, inferer.result()));

		NodeVisitor::visit(aNode);

		aNode->setTypeTuple(aNode->getDefinition()->getTypeTuple());
	}

	void visit(ConstantNode * aNode)
	{
		TypeInferer inferer(mTuple, mLibrary);
		inferer.process(aNode);
		aNode->setTypeTuple(inferer.result());
	}

	void visit(NameRefNode * aNode)
	{
		// По входному типу определяем результирующий.
		auto name = aNode->getName().getStr();
		auto target = aNode->getTarget();

		TTuple result;

		if (!mLibrary.getType(name, mTuple, result))
		{
			// Выводим тип.
			TypeInferer inferer(mTuple, mLibrary);
			inferer.process(target);

			mLibrary.addFunction(name, std::make_pair(mTuple, inferer.result()));

			if (target)
			{
				TypeBuilder builder(mTuple, mLibrary);	

				auto targetCopy = target->copy();
				builder.process(targetCopy);
				result = targetCopy->getTypeTuple();
				
				aNode->setTarget(targetCopy);

				mErrorList.insert(mErrorList.end(), builder.mErrorList.begin(), builder.mErrorList.end());
			}
			else
			{
				// Ошибка вывода типов.
				mErrorList.push_front("type error: function " + name + " taking arguments of type " + mTuple.toString() + " is not found");
			}
		}

		// Проверяем тип.
		mTuple = result;
		aNode->setTypeTuple(mTuple);
	}

	void visit(FunctionNode * aNode)
	{
		// Начинаем новый вывод с главного уравнения.
		auto mainDefinition = aNode->getDefinition(aNode->getFuncName());

		process(mainDefinition);
	}

private:
	TypeLibrary mLibrary;
	TTuple mTuple;

	std::list<std::string> mErrorList;
};

bool checkTypes(ASTNode * aNode)
{
	TypeLibrary library;
	TTuple input;

	input.push_back(TypeInfo("int"));

	// Тестовый тип данных.
	library.addFunction("add", std::make_pair(TTuple(2, TypeInfo("int")), TTuple(1, TypeInfo("float"))));

	TypeBuilder builder(input, library);

	builder.process(aNode);

	return true;
}

}}