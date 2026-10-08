#include <iterator>
#include <memory>

#include "Parser/Nodes.h"
#include "ConstructorGenerator.h"
#include "DataTypes/Ops/ADTValue.h"

namespace FPTL::Runtime {
    ConstructorGenerator::ConstructorGenerator() : mCurrentData(nullptr) {
    }

    //------------------------------------------------------------------------------------------

    void ConstructorGenerator::work(const Parser::FunctionalProgram *aFuncProgram) {
        if (aFuncProgram->getDataDefinitions()) {
            process(aFuncProgram->getDataDefinitions());
        }
    }

    //-------------------------------------------------------------------------------------------
    void ConstructorGenerator::handle(Parser::DataNode *aData) {
        mCurrentData = aData;

        NodeVisitor::handle(aData);

        mTypeParameters.clear();
    }

    //-------------------------------------------------------------------------------------------
    void ConstructorGenerator::handle(Parser::NameRefNode *aNameReference) {
        if (aNameReference->getType() == Parser::ASTNode::Template) {
            mStack.push(mTypeTuple);
            mTypeTuple.clear();
        }

        NodeVisitor::handle(aNameReference);

        switch (aNameReference->getType()) {
            case Parser::ASTNode::TypeParamName:
            case Parser::ASTNode::BaseType:
            case Parser::ASTNode::Type: {
                mTypeTuple.emplace_back(aNameReference->getName().getStr());
                break;
            }

            case Parser::ASTNode::Template: {
                TypeInfo newType(aNameReference->getName().getStr());

                size_t i = 0;

                const auto *data = dynamic_cast<Parser::DataNode *>(aNameReference->mTarget);

                for (const auto &child: data->getTypeParams()->mChilds) {
                    const auto *paramName = dynamic_cast<Parser::DefinitionNode *>(child);
                    newType.typeParameters.emplace_back(paramName->getDefinitionName().getStr(), mTypeTuple[i]);
                    i++;
                }

                mTypeTuple = mStack.top();
                mStack.pop();
                mTypeTuple.push_back(newType);
                break;
            }
        }
    }

    void ConstructorGenerator::handle(Parser::DefinitionNode *aDefinition) {
        NodeVisitor::handle(aDefinition);

        if (aDefinition->getType() == Parser::ASTNode::TypeConstructorDefinition) {
            std::string dataName = mCurrentData->getDataName().getStr();
            std::string constructorName = aDefinition->getDefinitionName().getStr();

            Constructor *constructor = !mTypeTuple.empty()
                                           ? new Constructor(constructorName, dataName, mTypeTuple, mTypeParameters)
                                           : new EmptyConstructor(constructorName, dataName);

            mConstructors.insert(std::make_pair(constructorName, std::shared_ptr<Constructor>(constructor)));

            mTypeTuple.clear();
        } else if (aDefinition->getType() == Parser::ASTNode::TypeParameterDefinition) {
            mTypeParameters.push_back(aDefinition->getDefinitionName().getStr());
        }
    }

    Constructor *ConstructorGenerator::getConstructor(const std::string &aConstructorName) const {
        return mConstructors.at(aConstructorName).get();
    }

    std::vector<std::string> ConstructorGenerator::constructors() const {
        std::vector<std::string> result;

        result.reserve(mConstructors.size());
        for (const auto &[fst, snd]: mConstructors) {
            result.push_back(fst);
        }
        return result;
    }
}
