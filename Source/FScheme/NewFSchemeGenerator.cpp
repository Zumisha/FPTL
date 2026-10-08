#include "NewFSchemeGenerator.h"

#include <cassert>

#include "NodeDeleter.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/ADTValue.h"
#include "Utils/StringUtils.hpp"

namespace FPTL {
    namespace Runtime {
        NewFSchemeGenerator::NewFSchemeGenerator(Parser::ASTNode *astRoot) : mScheme(nullptr),
                                                                             mSchemeInput(nullptr),
                                                                             mProgram(nullptr) {
            Handle(astRoot);
        }

        NewFSchemeGenerator::~NewFSchemeGenerator() {
            NodeDeleter deleter;
            deleter.releaseGraph(mProgram);
        }

        FSchemeNode *NewFSchemeGenerator::getProgram() const {
            return mProgram;
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ExpressionNode *aExpressionNode, const size_t childNum) {
            switch (childNum) {
                case Parser::ExpressionNode::mLeft: {
                    return aExpressionNode->getLeft();
                }
                case Parser::ExpressionNode::mRight: {
                    return aExpressionNode->getRight();
                }
                default: {
                    return nullptr;
                }
            }
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ExpressionNode *aExpressionNode, Parser::ASTNode *child) {
            if (child == aExpressionNode->getLeft()) {
                return Parser::ExpressionNode::mLeft;
            }
            if (child == aExpressionNode->getRight()) {
                return Parser::ExpressionNode::mRight;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ExpressionNode *aExpressionNode, const size_t childNum) {
            switch (childNum) {
                case Parser::ExpressionNode::mLeft:
                case Parser::ExpressionNode::mRight: {
                    break;
                }
                // post processing
                default: {
                    switch (aExpressionNode->getType()) {
                        case Parser::ASTNode::SequentialTerm:
                        case Parser::ASTNode::ValueConstructor: {
                            const auto second = mNodeStack.top();
                            mNodeStack.pop();

                            const auto first = mNodeStack.top();
                            mNodeStack.pop();

                            // �������������� ������, ����� ��� ��������� ������ � ����� �������,
                            // ����� ��� ���������� �� ������ advance ��� unwind.
                            if (const auto seqNode = dynamic_cast<FSequentialNode *>(second)) {
                                mNodeStack.push(new FSequentialNode(new FSequentialNode(first, seqNode->first()), seqNode->second()));
                            } else {
                                mNodeStack.push(new FSequentialNode(first, second));
                            }

                            break;
                        }

                        case Parser::ASTNode::CompositionTerm:
                        case Parser::ASTNode::ValueComposition:
                        case Parser::ASTNode::InputVarList: {
                            const auto right = mNodeStack.top();
                            mNodeStack.pop();

                            const auto left = mNodeStack.top();
                            mNodeStack.pop();

                            mNodeStack.push(new FParallelNode(left, right));

                            break;
                        }
                        default:
                            throw std::logic_error("unknown node type");
                    }
                }
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ExpressionNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ConditionNode *aConditionNode, const size_t childNum) {
            switch (childNum) {
                case Parser::ConditionNode::mThen: {
                    return aConditionNode->getThen();
                }
                case Parser::ConditionNode::mCond: {
                    return aConditionNode->getCond();
                }
                case Parser::ConditionNode::mElse: {
                    return aConditionNode->getElse();
                }
                default: {
                    return nullptr;
                }
            }
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ConditionNode *aConditionNode, Parser::ASTNode *child) {
            if (child == aConditionNode->getThen()) {
                return Parser::ConditionNode::mThen;
            }
            if (child == aConditionNode->getCond()) {
                return Parser::ConditionNode::mCond;
            }
            if (child == aConditionNode->getElse()) {
                return Parser::ConditionNode::mElse;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ConditionNode *aConditionNode, const size_t childNum) {
            switch (childNum) {
                case Parser::ConditionNode::mThen:
                case Parser::ConditionNode::mCond:
                case Parser::ConditionNode::mElse: {
                    break;
                }
                // post processing
                default: {
                    const auto thenBranch = mNodeStack.top();
                    mNodeStack.pop();

                    const auto middle = aConditionNode->getCond();
                    FSchemeNode *elseBranch = nullptr;
                    if (middle) {
                        elseBranch = mNodeStack.top();
                        mNodeStack.pop();
                    }

                    const auto condition = mNodeStack.top();
                    mNodeStack.pop();

                    mNodeStack.push(new FConditionNode(condition, thenBranch, elseBranch));
                    break;
                }
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ConditionNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ConstantNode *, size_t) {
            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ConstantNode *, Parser::ASTNode *) {
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ConstantNode *aConstantNode, size_t) {
            FSchemeNode *node = nullptr;

            const auto name = aConstantNode->getConstant();

            switch (aConstantNode->getType()) {
                // ������������� ���������.
                case Parser::ASTNode::IntConstant: {
                    const auto constant = StringUtils::toInt(aConstantNode->getConstant().getStr(), true);
                    node = new FConstantNode(TypeInfo("integer"), DataBuilders::createInt(constant), name.Line, name.Col);
                    break;
                }

                // ������������ ���������, ������� �����.
                case Parser::ASTNode::LongLongConstant:
                case Parser::ASTNode::FloatConstant:
                case Parser::ASTNode::DoubleConstant: {
                    const auto constant = StringUtils::toDouble(aConstantNode->getConstant().getStr(), true);
                    node = new FConstantNode(TypeInfo("double"), DataBuilders::createDouble(constant), name.Line, name.Col);
                    break;
                }

                // ��������� ���������.
                case Parser::ASTNode::StringConstant: {
                    const std::string str = aConstantNode->getConstant().getStr();
                    node = new FStringConstant(str, name.Line, name.Col);
                    break;
                }

                // ������ ���������.
                case Parser::ASTNode::TrueValue:
                case Parser::ASTNode::FalseValue: {
                    node = new FConstantNode(TypeInfo("boolean"), DataBuilders::createBoolean(aConstantNode->getType() == Parser::ASTNode::TrueValue),
                                             name.Line, name.Col);
                    break;
                }

                default: {
                    assert(false);
                }
            }

            mNodeStack.push(node);
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ConstantNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::TakeNode *, size_t) {
            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::TakeNode *, Parser::ASTNode *) {
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::TakeNode *aTakeNode, size_t) {
            const auto fromIdent = aTakeNode->getFrom();
            const auto from = StringUtils::toInt(fromIdent.getStr(), true);
            const auto to = StringUtils::toInt(aTakeNode->getTo().getStr(), true);

            FSchemeNode *node = new FTakeNode(from, to, fromIdent.Line, fromIdent.Col);

            mNodeStack.push(node);
        }

        void NewFSchemeGenerator::ChildHandled(Parser::TakeNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ListNode *aListNode, const size_t childNum) {
            if (childNum >= aListNode->mChilds.size()) return nullptr;
            return aListNode->mChilds[aListNode->mChilds.size() - 1 - childNum];
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ListNode *aListNode, Parser::ASTNode *child) {
            for (auto pair = aListNode->mChilds.rbegin(); pair != aListNode->mChilds.rend(); ++pair) {
                if (child == *pair) {
                    return std::next(pair).base() - aListNode->mChilds.begin();
                }
            }

            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ListNode *aListNode, size_t childNum) {
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ListNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::DefinitionNode *aDefinitionNode, const size_t childNum) {
            if (childNum == Parser::DefinitionNode::mDefinition) {
                return aDefinitionNode->getDefinition();
            }
            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::DefinitionNode *aDefinitionNode, Parser::ASTNode *child) {
            if (child == aDefinitionNode->getDefinition()) {
                return Parser::DefinitionNode::mDefinition;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::DefinitionNode *aDefinitionNode, const size_t childNum) {
            if (childNum == Parser::DefinitionNode::mDefinition &&
                aDefinitionNode->getType() == Parser::ASTNode::Definition) {
                auto name = aDefinitionNode->getDefinitionName().getStr();

                auto *me = new FScheme(nullptr, name);
                mDefinitions.insert(std::make_pair(name, me));
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::DefinitionNode *aDefinitionNode, const size_t childNum) {
            if (childNum == Parser::DefinitionNode::mDefinition &&
                aDefinitionNode->getType() == Parser::ASTNode::Definition) {
                auto *me = new FScheme(nullptr, aDefinitionNode->getDefinitionName().getStr());
                const auto contents = mNodeStack.top();
                mNodeStack.pop();
                me->setFirstNode(contents);
            }
        }

        // -------------------------------------------------------------------------------------------------------------

        // ToDo: ������� Parser::NameRefNode �� ��������� ����� �����
        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::NameRefNode *aNameRefNode, const size_t childNum) {
            switch (childNum) {
                case Parser::NameRefNode::mParameters: {
                    return aNameRefNode->getParameters();
                }
                case Parser::NameRefNode::mParameters + 1: {
                    switch (aNameRefNode->getType()) {
                        case Parser::ASTNode::BuildInFunction: {
                            return nullptr;
                        }

                        case Parser::ASTNode::FuncObjectWithParameters: {
                            return aNameRefNode->mTarget;
                        }
                        case Parser::ASTNode::FuncParameterName:
                        case Parser::ASTNode::FuncObjectName: {
                            // ���������, �� ���� ��������� ��� �����.
                            const auto target = aNameRefNode->mTarget;
                            const auto name = aNameRefNode->getName().getStr();

                            if (target->getType() == Parser::ASTNode::FunctionBlock &&
                                mDefinitions.find(name) == mDefinitions.end()) {
                                // ������������� ����������� �������, ��� ������ ��������� �� ������ ���
                                return target;
                            }

                            if (target->getType() == Parser::ASTNode::Definition) {
                                // ������ ����������� �������������� ���������.
                                if (!target->isRecursive()) {
                                    return dynamic_cast<Parser::DefinitionNode *>(target)->getDefinition();
                                }

                                if (mDefinitions.find(name) == mDefinitions.end()) {
                                    // ������������� ����������� �������, ��� ������ ��������� �� ������ ���
                                    return target;
                                }
                            }

                            return nullptr;
                        }

                        case Parser::ASTNode::ConstructorName:
                        case Parser::ASTNode::DestructorName: {
                            return nullptr;
                        }

                        case Parser::ASTNode::InputVarName: {
                            const auto *inputVarDef = dynamic_cast<Parser::DefinitionNode *>(aNameRefNode->mTarget);
                            return inputVarDef->getDefinition();
                        }

                        default:
                            assert(false);
                    }
                }
                default: {
                    return nullptr;
                }
            }
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::NameRefNode *aNameRefNode, Parser::ASTNode *child) {
            const auto target = aNameRefNode->mTarget;
            if (child == aNameRefNode->getParameters()) {
                return Parser::NameRefNode::mParameters;
            }
            if ((child == target &&
                 (aNameRefNode->getType() == Parser::ASTNode::FuncObjectWithParameters ||
                  (aNameRefNode->getType() == Parser::ASTNode::FuncParameterName ||
                   aNameRefNode->getType() == Parser::ASTNode::FuncObjectName
                  ) && (
                      target->getType() == Parser::ASTNode::FunctionBlock ||
                      (target->getType() == Parser::ASTNode::Definition &&
                       target->isRecursive()
                      )
                  )
                 )
                ) || (child == dynamic_cast<Parser::DefinitionNode *>(target)->getDefinition() &&
                      (aNameRefNode->getType() == Parser::ASTNode::InputVarName ||
                       ((aNameRefNode->getType() == Parser::ASTNode::FuncParameterName ||
                         aNameRefNode->getType() == Parser::ASTNode::FuncObjectName
                        ) && target->getType() == Parser::ASTNode::Definition && !target->isRecursive()
                       )
                      )
                )
            ) {
                return Parser::NameRefNode::mParameters + 1;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::NameRefNode *aNameRefNode, const size_t childNum) {
            switch (childNum) {
                case Parser::NameRefNode::mParameters: {
                    break;
                }
                // ���� �������������, ���� ���� ���. ��������
                case Parser::NameRefNode::mParameters + 1: {
                    switch (aNameRefNode->getType()) {
                        case Parser::ASTNode::BuildInFunction: {
                            const auto name = aNameRefNode->getName();
                            const auto [fst, snd] = FunctionLibrary::getFunction(name.getStr());
                            // ���� ������� � ����������.
                            auto function = new FFunctionNode(fst, snd, name.getStr(), name.Line, name.Col);
                            mNodeStack.emplace(function);
                            break;
                        }

                        case Parser::ASTNode::FuncObjectWithParameters: {
                            // ���������, �� ���� ��������� ��� �����.
                            auto *const target = aNameRefNode->mTarget;
                            // ������� ����� �������������� ����� � �����������.
                            mDefinitionsStack.push(mDefinitions);
                            mDefinitions.clear();

                            // ��������� � ������� ����������� �������� �������������� ���������.
                            // ToDo: ������� ������������ - ���������� (�� ����� �� ������������ dynamic_cast).
                            const Parser::ListNode *parameters = dynamic_cast<Parser::FunctionNode *>(target)->getFormalParameters();

                            for (auto &child: parameters->mChilds) {
                                FSchemeNode *node = mNodeStack.top();
                                mNodeStack.pop();

                                // ToDo: ������� ������������ - ���������� (�� ����� �� ������������ dynamic_cast).
                                const auto formalParamName = dynamic_cast<Parser::DefinitionNode *>(child);

                                auto delegateScheme = dynamic_cast<FScheme *>(node);
                                if (!delegateScheme) {
                                    delegateScheme = new FScheme(node);
                                }

                                // ����� ������ ������ insert(), �.�. �������� ���������� ������ ���������������� ������ ��� ��� ������ �� ��������� �������.
                                mDefinitions[formalParamName->getDefinitionName().getStr()] = delegateScheme;
                            }

                            // ���������� ����� ��� �������.
                            break;
                        }
                        case Parser::ASTNode::FuncParameterName:
                        case Parser::ASTNode::FuncObjectName: {
                            const auto name = aNameRefNode->getName().getStr();
                            const auto target = aNameRefNode->mTarget;
                            if (target->getType() == Parser::ASTNode::Definition || target->getType() == Parser::ASTNode::FunctionBlock) {
                                if (target->getType() != Parser::ASTNode::Definition || target->isRecursive()) {
                                    if (mDefinitions.find(name) != mDefinitions.end())
                                        mNodeStack.push(mDefinitions.at(name));
                                }
                            } else {
                                mNodeStack.push(mDefinitions.at(name));
                            }
                            break;
                        }

                        case Parser::ASTNode::ConstructorName: {
                            const auto ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
                            const auto name = aNameRefNode->getName();
                            FSchemeNode *node = new FFunctionNode([&ctor](auto &&arg) {
                                return ctor->execConstructor(std::forward<decltype(arg)>(arg));
                            }, false, name.getStr(), name.Line, name.Col);
                            mNodeStack.emplace(node);
                            break;
                        }

                        case Parser::ASTNode::DestructorName: {
                            const auto ctor = mConstructorGenerator.getConstructor(aNameRefNode->getName().getStr());
                            const auto name = aNameRefNode->getName();
                            FSchemeNode *node = new FFunctionNode([&ctor](auto &&arg) {
                                return ctor->execDestructor(std::forward<decltype(arg)>(arg));
                            }, false, name.getStr(), name.Line, name.Col);
                            mNodeStack.emplace(node);
                            break;
                        }

                        case Parser::ASTNode::InputVarName: {
                            break;
                        }

                        default:
                            assert(false);
                    }

                    break;
                }
                default: {
                    break;
                }
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::NameRefNode *aNameRefNode, const size_t childNum) {
            switch (childNum) {
                case Parser::NameRefNode::mParameters + 1: {
                    switch (aNameRefNode->getType()) {
                        case Parser::ASTNode::FuncObjectWithParameters: {
                            // ����������� ��������������� �����.
                            mNodeStack.push(mDefinitions.at(aNameRefNode->getName().getStr()));

                            mDefinitions = mDefinitionsStack.top();
                            mDefinitionsStack.pop();
                            break;
                        }
                        case Parser::ASTNode::FuncParameterName:
                        case Parser::ASTNode::FuncObjectName: {
                            // ���������, �� ���� ��������� ��� �����.
                            auto *const target = aNameRefNode->mTarget;
                            const auto name = aNameRefNode->getName().getStr();
                            if (target->getType() == Parser::ASTNode::Definition || target->getType() == Parser::ASTNode::FunctionBlock) {
                                if (target->isRecursive() || target->getType() != Parser::ASTNode::Definition) {
                                    if (mDefinitions.find(name) == mDefinitions.end())
                                        mNodeStack.push(mDefinitions.at(name));
                                }
                            }
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ConstructorNode *aConstructorNode, const size_t childNum) {
            if (childNum == Parser::DataNode::mConstructors) {
                return aConstructorNode->getCtorParameters();
            }
            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ConstructorNode *aConstructorNode, Parser::ASTNode *child) {
            if (child == aConstructorNode->getCtorParameters()) {
                return Parser::DataNode::mConstructors;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ConstructorNode *aConstructorNode, size_t childNum) {
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ConstructorNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::DataNode *aDataNode, const size_t childNum) {
            switch (childNum) {
                case Parser::DataNode::mConstructors: {
                    return aDataNode->getConstructors();
                }
                case Parser::DataNode::mTypeParameters: {
                    return aDataNode->getTypeParams();
                }
                case Parser::DataNode::mTypeDefinitions: {
                    return aDataNode->getTypeDefs();
                }
                default: {
                    return nullptr;
                }
            }
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::DataNode *aDataNode, Parser::ASTNode *child) {
            if (child == aDataNode->getConstructors()) {
                return Parser::DataNode::mConstructors;
            }
            if (child == aDataNode->getTypeParams()) {
                return Parser::DataNode::mTypeParameters;
            }
            if (child == aDataNode->getTypeDefs()) {
                return Parser::DataNode::mTypeDefinitions;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::DataNode *aDataNode, size_t childNum) {
        }

        void NewFSchemeGenerator::ChildHandled(Parser::DataNode *, size_t) {
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::FunctionNode *aFunctionNode, const size_t childNum) {
            if (childNum == Parser::FunctionNode::mDefinitions) {
                return aFunctionNode->getDefinition(aFunctionNode->getFuncName());
            }

            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::FunctionNode *aFunctionNode, Parser::ASTNode *child) {
            if (child == aFunctionNode->getDefinition(aFunctionNode->getFuncName())) {
                return Parser::FunctionNode::mDefinitions;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::FunctionNode *aFunctionNode, const size_t childNum) {
            if (childNum == Parser::FunctionNode::mDefinitions) {
                // ��������� ��������. ���� ���� �������������� ���������, �������� ����������� ������.
                if (aFunctionNode->getFormalParameters() != nullptr) {
                    mDefinitionsStack.push(mDefinitions);
                    mDefinitions.clear();
                }
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::FunctionNode *aFunctionNode, const size_t childNum) {
            if (childNum == Parser::FunctionNode::mDefinitions) {
                // ��������� ������ �����������.
                std::map<std::string, FSchemeNode *> definitionMap;
                for (const auto &[fst, snd]: mDefinitions) {
                    definitionMap.insert(std::make_pair(fst, snd));
                }

                const auto name = aFunctionNode->getFuncName();

                auto *me = mDefinitions.at(name.getStr());
                me->setDefinitions(definitionMap);

                // ��������������� ��������. ���� ���� �������������� ���������, �������� ����������������� ������.
                if (aFunctionNode->getFormalParameters() != nullptr) {
                    mDefinitions = mDefinitionsStack.top();
                    mDefinitionsStack.pop();

                    // fun-���� ������ ���� ����� �� ������� ���������
                    mDefinitions.insert(std::make_pair(name.getStr(), me));
                }
            }
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::ApplicationBlock *aApplicationBlock, const size_t childNum) {
            if (childNum == Parser::ApplicationBlock::mSchemeParameters) {
                return aApplicationBlock->getSchemeParameters();
            }

            return nullptr;
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::ApplicationBlock *aApplicationBlock, Parser::ASTNode *child) {
            if (child == aApplicationBlock->getSchemeParameters()) {
                return Parser::ApplicationBlock::mSchemeParameters;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::ApplicationBlock *aApplicationBlock, size_t childNum) {
        }

        void NewFSchemeGenerator::ChildHandled(Parser::ApplicationBlock *aApplicationBlock, const size_t childNum) {
            if (childNum == Parser::ApplicationBlock::mSchemeParameters) {
                mSchemeInput = mNodeStack.top();
                mNodeStack.pop();
                mProgram = new FSequentialNode(mSchemeInput, mScheme);
            }
        }

        // -------------------------------------------------------------------------------------------------------------

        Parser::ASTNode *NewFSchemeGenerator::getChild(Parser::FunctionalProgram *aFuncProgram, const size_t childNum) {
            switch (childNum) {
                case Parser::FunctionalProgram::mDataDefinitions: {
                    return nullptr;
                    //return aFuncProgram->getDataDefinitions();
                }
                case Parser::FunctionalProgram::mScheme: {
                    return aFuncProgram->getScheme();
                }
                case Parser::FunctionalProgram::mApplication: {
                    return aFuncProgram->getApplication()->getSchemeParameters();
                }
                default: {
                    return nullptr;
                }
            }
        }

        size_t NewFSchemeGenerator::getChildIndex(Parser::FunctionalProgram *aFuncProgram, Parser::ASTNode *child) {
            if (child == aFuncProgram->getScheme()) {
                return Parser::FunctionalProgram::mScheme;
            }
            if (child == aFuncProgram->getApplication()->getSchemeParameters()) {
                return Parser::FunctionalProgram::mApplication;
            }
            return -1;
        }

        void NewFSchemeGenerator::intermediateProcessing(Parser::FunctionalProgram *aFuncProgram, const size_t childNum) {
            if (childNum == Parser::FunctionalProgram::mDataDefinitions) {
                mConstructorGenerator.work(aFuncProgram);
                //return aFuncProgram->getDataDefinitions();
            }
        }

        void NewFSchemeGenerator::ChildHandled(Parser::FunctionalProgram *aFuncProgram, const size_t childNum) {
            switch (childNum) {
                case Parser::FunctionalProgram::mScheme: {
                    mScheme = mDefinitions[aFuncProgram->getScheme()->getFuncName().getStr()];
                    mProgram = mScheme;
                    break;
                }
                case Parser::FunctionalProgram::mApplication: {
                    mSchemeInput = mNodeStack.top();
                    mNodeStack.pop();

                    mProgram = new FSequentialNode(mSchemeInput, mScheme);
                    break;
                }
            }
        }
    }
}
