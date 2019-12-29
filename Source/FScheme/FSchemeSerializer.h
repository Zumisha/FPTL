#pragma once

#include <string>
#include <fstream>

#include "FScheme/FScheme.h"
#include "FSchemeVisitor.h"

namespace FPTL
{
	namespace Runtime
	{
		class FSchemeSerializer : public FSchemeVisitor
		{
		public:
			inline static const std::string serialization_path = "FScheme.xml";
			inline static const std::string CHILDS = "Childs";

			void serialize(const FSchemeNode* node);

		private:
			std::fstream mFile;
			std::unordered_map<const FSchemeNode*, int> visited;
			int id = 0;

			void tryVisit(const FSchemeNode* node);

			void visit(const FFunctionNode* node) override;
			void visit(const FParallelNode* node) override;
			void visit(const FSequentialNode* node) override;
			void visit(const FConditionNode* node) override;
			void visit(const FScheme* scheme) override;
			void visit(const FTakeNode* node) override;
			void visit(const FConstantNode* node) override;
			void visit(const FStringConstant* node) override;
		};
	}
}
