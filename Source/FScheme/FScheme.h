#pragma once

#include <utility>

#include "Evaluator/Context.h"
#include "Libraries/FunctionLibrary.h"
#include "FSchemeSerializer.h"

namespace FPTL
{
	namespace Runtime
	{
		class FSchemeNode;
		class FSchemeVisitor;
		struct SExecutionContext;

		//---------------------------------------------------------------------------------------------
		// Абстрактный узел функциональный схемы.
		class FSchemeNode
		{
		public:
			explicit FSchemeNode(bool aIsLong);
			virtual ~FSchemeNode() = default;

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
			explicit FFunctionNode(const F & aFunction) : FSchemeNode(false), mFunction(aFunction), mLine(0), mColumn(0)
			{
			}

			template <typename F>
			FFunctionNode(const F & aFunction, const std::string & aName, const size_t aLine, const size_t aCol) :
				FSchemeNode(false),
				mFunction(aFunction),
				mName(aName),
				mLine(aLine),
				mColumn(aCol)
			{}

			void accept(FSchemeVisitor * aVisitor) const override;

			std::string name() const { return mName; }
			size_t col() const { return mColumn; }
			size_t line() const { return mLine; }
			std::pair<size_t, size_t> pos() const { return{ mLine, mColumn }; }
			TFunction fn() const { return mFunction; }

		private:
			std::function<void(SExecutionContext &)> mFunction;

			// Имя функции и позиция в тексте программы.
			std::string mName;
			size_t mLine;
			size_t mColumn;
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
			FTakeNode(const long long aIndex, const size_t aLine, const size_t aCol)
				: FSchemeNode(false),
				mIndex(aIndex),
				mLine(aLine),
				mCol(aCol)
			{}

			void accept(FSchemeVisitor * aVisitor) const override;

			long long index() const { return mIndex; }
			size_t col() const { return mCol; }
			size_t line() const { return mLine; }
			std::pair<size_t, size_t> pos() const { return{ mLine, mCol }; }

		private:
			long long mIndex;
			size_t mLine;
			size_t mCol;
		};

		//---------------------------------------------------------------------------------------------
		class FConstantNode : public FSchemeNode
		{
		public:
			FConstantNode(TypeInfo aType, const DataValue & aData, const size_t aLine, const size_t aCol) :
				FSchemeNode(false),
				mData(aData),
				mType(std::move(aType)),
				mLine(aLine),
				mCol(aCol)
			{}

			void accept(FSchemeVisitor * aVisitor) const override;

			TypeInfo type() const { return mType; }
			DataValue data() const { return mData; }
			size_t col() const { return mCol; }
			size_t line() const { return mLine; }
			std::pair<size_t, size_t> pos() const { return{ mLine, mCol }; }

		private:
			DataValue mData;
			TypeInfo mType;
			size_t mLine;
			size_t mCol;
		};

		class FStringConstant : public FSchemeNode
		{
		public:
			FStringConstant(std::string aStr, const size_t aLine, const size_t aCol) :
				FSchemeNode(false),
				mStr(std::move(aStr)),
				mData(DataValue()),
				mType(TypeInfo("string")),
				mLine(aLine),
				mCol(aCol)
			{}

			void accept(FSchemeVisitor * aVisitor) const override;

			std::string str() const { return mStr; }
			TypeInfo type() const { return mType; }
			DataValue data() const { return mData; }
			size_t col() const { return mCol; }
			size_t line() const { return mLine; }
			std::pair<size_t, size_t> pos() const { return{ mLine, mCol }; }

		private:
			std::string mStr;
			DataValue mData;
			TypeInfo mType;
			size_t mLine;
			size_t mCol;
		};

		//---------------------------------------------------------------------------------------------
		// Функциональная схема.
		class FScheme : public FSchemeNode
		{
			friend class FSchemeSerializer;
			//friend FSchemeVisitor;

		public:
			explicit FScheme(FSchemeNode * aFirstNode);
			FScheme(FSchemeNode * aFirstNode, std::string aName);

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

	}
}
