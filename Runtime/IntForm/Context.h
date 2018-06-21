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

	virtual void run(EvaluatorUnit * evaluator);

	IFExecutionContext * spawn(InternalForm * fork);

	virtual void cancel();
};


}}