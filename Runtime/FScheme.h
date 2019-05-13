// FScheme.h - описание функциональной схемы.

#ifndef FSCHEME_H
#define FSCHEME_H

#include "Context.h"
#include "FunctionLibrary.h"

namespace FPTL {
namespace Runtime {

class FSchemeNode;
class FSchemeVisitor;
struct SExecutionContext;

//---------------------------------------------------------------------------------------------
// Абстрактный узел функциональный схемы.
class FSchemeNode
{
public:
	FSchemeNode(bool aIsLong);
	virtual ~FSchemeNode() {}

	virtual void accept(FSchemeVisitor * aVisitor) const = 0;

	bool isLong() const { return mIsLong; }

protected:
	bool mIsLong;
};

//---------------------------------------------------------------------------------------------
class FParallelNode : public FSchemeNode
{
public:
	FParallelNode(FSchemeNode * aLeft, FSchemeNode * aRight);

	void accept(FSchemeVisitor * aVisitor) const override;

	FSchemeNode * left() const { return mLeft; }
	FSchemeNode * right() const { return mRight; }

private:

	// Дочерние элементы блока, могут выполняться параллельно.
	FSchemeNode * mLeft;
	FSchemeNode * mRight;
};

//---------------------------------------------------------------------------------------------
// Узел, инкапсулирующий вызов встроенной функции или схемы.
class FFunctionNode : public FSchemeNode
{
public:
	template <typename F>
	FFunctionNode(const F & aFunction) : FSchemeNode(false), mFunction(aFunction)
	{}

	template <typename F>
	FFunctionNode(const F & aFunction, const std::string & aName, short aLine, short aCol)
		: FSchemeNode(false),
		  mFunction(aFunction),
		  mName(aName),
		  mColumn(aCol),
		  mLine(aLine)
	{}

	void accept(FSchemeVisitor * aVisitor) const override;

	std::string name() const { return mName; }
	int col() const { return mColumn; }
	int line() const { return mLine; }
	std::pair<int, int> pos() const { return{ mColumn, mLine }; }
	TFunction fn() const { return mFunction; }

private:
	std::function<void(SExecutionContext &)> mFunction;

	// Имя функции и позиция в тексте программы.
	std::string mName;
	short mLine;
	short mColumn;
};

//---------------------------------------------------------------------------------------------
class FSequentialNode : public FSchemeNode
{
public:
	FSequentialNode(FSchemeNode * aFirst, FSchemeNode * aSecond);

	void accept(FSchemeVisitor * aVisitor) const override;

	FSchemeNode * first() const { return mFirst; }
	FSchemeNode * second() const { return mSecond; }

private:
	FSchemeNode * mFirst;
	FSchemeNode * mSecond;
};

//---------------------------------------------------------------------------------------------
class FConditionNode : public FSchemeNode
{
public:

	FConditionNode(FSchemeNode * aCondition, FSchemeNode * aTrueBranch, FSchemeNode * aFalseBranch);

	void accept(FSchemeVisitor * aVisitor) const override;

	FSchemeNode * condition() const { return mCondition; }
	FSchemeNode * trueBranch() const { return mTrueBranch; }
	FSchemeNode * falseBranch() const { return mFalseBranch; }

private:

	FSchemeNode * mCondition;
	FSchemeNode * mTrueBranch;
	FSchemeNode * mFalseBranch;
};

//---------------------------------------------------------------------------------------------
class FTakeNode : public FSchemeNode
{
public:
	FTakeNode(int aIndex, short aLine, short aCol)
		: FSchemeNode(false), 
		mIndex(aIndex),
		mLine(aLine),
		mCol(aCol)
	{}

	void accept(FSchemeVisitor * aVisitor) const override;

	int index() const { return mIndex; }
	int col() const { return mCol; }
	int line() const { return mLine; }
	std::pair<int, int> pos() const { return{ mCol, mLine }; }

private:
	int mIndex;

	short mLine;
	short mCol;
};

//---------------------------------------------------------------------------------------------
class FConstantNode : public FSchemeNode
{
public:
	FConstantNode(const TypeInfo & aType, const DataValue & aData, short aLine, short aCol)
		: FSchemeNode(false),
		mData(aData),
		mType(aType),
		mLine(aLine),
		mCol(aCol)
	{}

	void accept(FSchemeVisitor * aVisitor) const override;

	TypeInfo type() const { return mType; }
	DataValue data() const { return mData; }

private:
	DataValue mData;
	TypeInfo mType;
	short mLine;
	short mCol;
};

class FStringConstant : public FConstantNode
{
public:
	FStringConstant(const std::string & aStr, short aLine, short aCol);

	std::string str() const { return mStr; }

private:
	std::string mStr;
};

//---------------------------------------------------------------------------------------------
// Функциональная схема.
class FScheme : public FSchemeNode
{
public:
	FScheme(FSchemeNode * aFirstNode);
	FScheme(FSchemeNode * aFirstNode, const std::string & aName);

	void accept(FSchemeVisitor * aVisitor) const override;

	void setFirstNode(FSchemeNode * aFirstNode);
	void setDefinitions(const std::map<std::string, FSchemeNode *> & aDefinitions);

	FSchemeNode * firstNode() const { return mFirstNode; }
	std::string name() const { return mName; }

	std::vector<std::string> definitions() const;
	FSchemeNode * definition(const std::string & aName) const;

private:
	FSchemeNode * mFirstNode;
	std::string mName;
	std::map<std::string, FSchemeNode *> mDefinitions;
};

} // Runtime
} // FPTL

#endif