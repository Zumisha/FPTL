#pragma once

#include "../Context.h"

namespace FPTL {
namespace Runtime {

class InternalForm;

class IFExecutionContext : public SExecutionContext
{
	const InternalForm * mInternalForm;

public:
	IFExecutionContext(const InternalForm * body);

	virtual void run(EvaluatorUnit * evaluator);

	IFExecutionContext * spawn(const InternalForm * fork);
};


}}