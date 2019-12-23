#include "FSchemeSerializer.h"
#include "Utils/FileStreamHelper.h"
#include "Utils/XmlHelper.h"

namespace FPTL
{
	namespace Runtime
	{
		void FSchemeSerializer::serialize(const FSchemeNode * node)
		{
			Utils::setPermissions(serialization_path);

			mFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				mFile.open(serialization_path, std::ios::out);
				node->accept(this);
				mFile.close();
			}
			catch (const std::ios_base::failure&)
			{
				throw std::runtime_error(Utils::getfStreamError(mFile));
			}
		}

		void FSchemeSerializer::visit(const FFunctionNode * node)
		{
			Utils::OpenTag(mFile, "Function");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";
				mFile << "<Name>" << node->name() << "</Name>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "Function");
		}

		void FSchemeSerializer::visit(const FParallelNode * node)
		{
			Utils::OpenTag(mFile, "Parallel");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "Left");
					node->left()->accept(this);
					Utils::CloseTag(mFile, "Left");

					Utils::OpenTag(mFile, "Right");
					node->right()->accept(this);
					Utils::CloseTag(mFile, "Right");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Parallel");
		}

		void FSchemeSerializer::visit(const FSequentialNode * node)
		{
			Utils::OpenTag(mFile, "Sequential");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "First");
					node->first()->accept(this);
					Utils::CloseTag(mFile, "First");

					Utils::OpenTag(mFile, "Second");
					node->second()->accept(this);
					Utils::CloseTag(mFile, "Second");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Sequential");
		}

		void FSchemeSerializer::visit(const FConditionNode * node)
		{
			Utils::OpenTag(mFile, "Condition");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "Condition");
					node->condition()->accept(this);
					Utils::CloseTag(mFile, "Condition");

					Utils::OpenTag(mFile, "Then");
					node->trueBranch()->accept(this);
					Utils::CloseTag(mFile, "Then");

					Utils::OpenTag(mFile, "Else");
					node->falseBranch()->accept(this);
					Utils::CloseTag(mFile, "Else");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Condition");
		}

		void FSchemeSerializer::visit(const FTakeNode * node)
		{
			Utils::OpenTag(mFile, "Take");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";
				mFile << "<Index>" << node->index() << "</Index>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "Take");
		}

		void FSchemeSerializer::visit(const FConstantNode* node)
		{
			Utils::OpenTag(mFile, "Constant");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";
				mFile << "<Type>" << node->type() << "</Type>";
				mFile << "<Value>";
				node->data().getOps()->print(node->data(), mFile);
				mFile << "</Value>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "Constant");
		}

		void FSchemeSerializer::visit(const FStringConstant* node)
		{
			Utils::OpenTag(mFile, "String");
			{
				mFile << "<Hard>" << node->isLong() << "</Hard>";
				mFile << "<Type>" << node->type() << "</Type>";
				mFile << "<Value>" << node->str() << "</Value>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "String");
		}

		void FSchemeSerializer::visit(const FScheme * scheme)
		{
			Utils::OpenTag(mFile, "Scheme");
			{
				mFile << "<Hard>" << scheme->isLong() << "</Hard>";
				mFile << "<Name>" << scheme->name() << "</Name>";
				Utils::OpenTag(mFile, CHILDS);
				{
					mFile << "<FirstNode>";
					scheme->firstNode()->accept(this);
					mFile << "</FirstNode>";
				}
				Utils::CloseTag(mFile, CHILDS);
				mFile << "<Definitions>";
				{
					for (auto element : scheme->mDefinitions)
					{
						Utils::OpenTag(mFile, element.first);
						Utils::CloseTag(mFile, element.first);
					}
				}
				mFile << "</Definitions>";
			}
			Utils::CloseTag(mFile, "Scheme");
		}
	}
}
