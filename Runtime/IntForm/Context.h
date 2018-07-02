#pragma once

#include "../Context.h"

namespace FPTL {
namespace Runtime {

class InternalForm;

class IFExecutionContext : public SExecutionContext
{
	InternalForm * mInternalForm;

public:
	IFExecutionContext(InternalForm * body);

	void run(EvaluatorUnit * evaluator) override;

	IFExecutionContext * spawn(InternalForm * fork);

	void cancel() override;
};


}}