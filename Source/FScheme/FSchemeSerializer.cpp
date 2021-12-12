#include "FSchemeSerializer.h"
#include "Utils/FileStreamHelper.h"
#include "DataTypes/Ops/Ops.h"

namespace FPTL::Runtime
{
		void FSchemeSerializer::serialize(const std::string& fName, const FSchemeNode* node)
		{
			Utils::setPermissions(fName);

			mFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			try
			{
				mFile.open(fName, std::ios::out);
				mFile << '[';
				tryVisit(node);
				mFile.seekp(-1, std::ios::end);
				mFile << ']';
				mFile.close();
			}
			catch (const std::ios_base::failure&)
			{
				throw std::runtime_error(Utils::getfStreamError(mFile));
			}
		}

		int FSchemeSerializer::tryVisit(const FSchemeNode* node)
		{
			const auto res = visited.insert(std::make_pair(node, id));
			if (!res.second)
			{
				return res.first->second;
			}

			const auto nodeId = id++;
			node->accept(this);
			return nodeId;
		}

		void FSchemeSerializer::visit(const FFunctionNode* node)
		{
			mFile << '{';
			mFile << "\"id\":" << id << ',';
			mFile << "\"type\":\"" << "Function" << "\",";
			mFile << "\"line\":" << node->line() << ',';
			mFile << "\"column\":" << node->col() << ',';
			mFile << "\"complex\":" << node->isLong() << ',';
			mFile << "\"name\":\"" << node->name() << '"';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FParallelNode* node)
		{
			const auto nodeId = id;
			const auto leftId = tryVisit(node->left());
			const auto rightId = tryVisit(node->right());

			mFile << '{';
			mFile << "\"id\":" << nodeId << ',';
			mFile << "\"type\":\"" << "Parallel" << "\",";
			mFile << "\"complex\":" << node->isLong() << ',';
			mFile << "\"children\":[" << leftId << ',' << rightId << ']';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FSequentialNode* node)
		{
			const auto nodeId = id;
			const auto firstId = tryVisit(node->first());
			const auto secondId = tryVisit(node->second());

			mFile << '{';
			mFile << "\"id\":" << nodeId << ',';
			mFile << "\"type\":\"" << "Sequential" << "\",";
			mFile << "\"complex\":" << node->isLong() << ',';
			mFile << "\"children\":[" << firstId << ',' << secondId << ']';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FConditionNode* node)
		{
			const auto nodeId = id;
			const auto condId = tryVisit(node->condition());
			const auto thenId = tryVisit(node->trueBranch());
			const auto elseId = tryVisit(node->falseBranch());

			mFile << '{';
			mFile << "\"id\":" << nodeId << ',';
			mFile << "\"type\":\"" << "Condition" << "\",";
			mFile << "\"complex\":" << node->isLong() << ',';
			mFile << "\"children\":[" << condId << ',' << thenId << ',' << elseId << ']';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FTakeNode* node)
		{
			mFile << '{';
			mFile << "\"id\":" << id << ',';
			mFile << "\"type\":\"" << "Take" << "\",";
			mFile << "\"line\":" << node->line() << ',';
			mFile << "\"column\":" << node->col() << ',';
			mFile << "\"from\":" << node->from() << ',';
			mFile << "\"to\":" << node->to();
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FConstantNode* node)
		{
			mFile << '{';
			mFile << "\"id\":" << id << ',';
			mFile << "\"type\":\"" << "Constant" << "\",";
			mFile << "\"line\":" << node->line() << ',';
			mFile << "\"column\":" << node->col() << ',';
			mFile << "\"valueType\":\"" << node->type() << "\",";
			mFile << "\"value\":\"";
			node->data().getOps()->print(node->data(), mFile);
			mFile << '"';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FStringConstant* node)
		{
			mFile << '{';
			mFile << "\"id\":" << id << ',';
			mFile << "\"type\":\"" << "String" << "\",";
			mFile << "\"line\":" << node->line() << ',';
			mFile << "\"column\":" << node->col() << ',';
			mFile << "\"value\":\"" << node->str() << '"';
			mFile << "},";
		}

		void FSchemeSerializer::visit(const FScheme* scheme)
		{
			const auto nodeId = id;
			std::vector<int> defIds;
			for (const auto& element : scheme->mDefinitions)
			{
				defIds.push_back(tryVisit(element.second));
			}
			const auto schemeId = tryVisit(scheme->firstNode());

			mFile << '{';
			mFile << "\"id\":" << nodeId << ',';
			mFile << "\"type\":\"" << "Scheme" << "\",";
			mFile << "\"complex\":" << scheme->isLong() << ',';
			mFile << "\"name\":\"" << scheme->name() << "\",";
			mFile << "\"children\":[";
			for (const auto defId : defIds)
			{
				mFile << defId << ',';
			}
			mFile << schemeId << ']';
			mFile << "},";
		}
}
