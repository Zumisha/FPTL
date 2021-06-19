#include "FSchemeSerializer.h"
#include "Utils/FileStreamHelper.h"
#include "Utils/XmlHelper.h"
#include "DataTypes/Ops/Ops.h"

namespace FPTL::Runtime
{
		void FSchemeSerializer::serialize(const FSchemeNode* node)
		{
			Utils::setPermissions(serialization_path);

			mFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				mFile.open(serialization_path, std::ios::out);
				tryVisit(node);
				mFile.close();
			}
			catch (const std::ios_base::failure&)
			{
				throw std::runtime_error(Utils::getfStreamError(mFile));
			}
		}

		void FSchemeSerializer::tryVisit(const FSchemeNode* node)
		{
			const auto res = visited.insert(std::make_pair(node, id));
			if (res.second)
			{
				id++;
				node->accept(this);
			}
			else
			{
				Utils::OpenTag(mFile, "Reference");
				mFile << res.first->second;
				Utils::CloseTag(mFile, "Reference");
			}
		}

		void FSchemeSerializer::visit(const FFunctionNode* node)
		{
			Utils::OpenTag(mFile, "Function");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Hard>" << node->isLong() << "</Hard>";
				mFile << "<Name>" << node->name() << "</Name>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "Function");
		}

		void FSchemeSerializer::visit(const FParallelNode* node)
		{
			Utils::OpenTag(mFile, "Parallel");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "Left");
					tryVisit(node->left());
					Utils::CloseTag(mFile, "Left");

					Utils::OpenTag(mFile, "Right");
					tryVisit(node->right());
					Utils::CloseTag(mFile, "Right");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Parallel");
		}

		void FSchemeSerializer::visit(const FSequentialNode* node)
		{
			Utils::OpenTag(mFile, "Sequential");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "First");
					tryVisit(node->first());
					Utils::CloseTag(mFile, "First");

					Utils::OpenTag(mFile, "Second");
					tryVisit(node->second());
					Utils::CloseTag(mFile, "Second");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Sequential");
		}

		void FSchemeSerializer::visit(const FConditionNode* node)
		{
			Utils::OpenTag(mFile, "Condition");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Hard>" << node->isLong() << "</Hard>";

				Utils::OpenTag(mFile, CHILDS);
				{
					Utils::OpenTag(mFile, "Condition");
					tryVisit(node->condition());
					Utils::CloseTag(mFile, "Condition");

					Utils::OpenTag(mFile, "Then");
					tryVisit(node->trueBranch());
					Utils::CloseTag(mFile, "Then");

					Utils::OpenTag(mFile, "Else");
					tryVisit(node->falseBranch());
					Utils::CloseTag(mFile, "Else");
				}
				Utils::CloseTag(mFile, CHILDS);
			}
			Utils::CloseTag(mFile, "Condition");
		}

		void FSchemeSerializer::visit(const FTakeNode* node)
		{
			Utils::OpenTag(mFile, "Take");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<From>" << node->from() << "</From>";
				mFile << "<To>" << node->to() << "</To>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "Take");
		}

		void FSchemeSerializer::visit(const FConstantNode* node)
		{
			Utils::OpenTag(mFile, "Constant");
			{
				mFile << "<Id>" << id << "</Id>";
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
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Value>" << node->str() << "</Value>";
				mFile << "<Line>" << node->line() << "</Line>";
				mFile << "<Column>" << node->col() << "</Column>";
			}
			Utils::CloseTag(mFile, "String");
		}

		void FSchemeSerializer::visit(const FScheme* scheme)
		{
			Utils::OpenTag(mFile, "Scheme");
			{
				mFile << "<Id>" << id << "</Id>";
				mFile << "<Hard>" << scheme->isLong() << "</Hard>";
				mFile << "<Name>" << scheme->name() << "</Name>";
				Utils::OpenTag(mFile, CHILDS);
				{
					mFile << "<FirstNode>";
					tryVisit(scheme->firstNode());
					mFile << "</FirstNode>";
				}
				Utils::CloseTag(mFile, CHILDS);
				mFile << "<Definitions>";
				{
					for (auto element : scheme->mDefinitions)
					{
						Utils::OpenTag(mFile, element.first);
						tryVisit(element.second);
						Utils::CloseTag(mFile, element.first);
					}
				}
				mFile << "</Definitions>";
			}
			Utils::CloseTag(mFile, "Scheme");
		}
}
