#pragma once

namespace FPTL {
namespace Runtime {

class InternalForm;

union ControlValue
{
	const InternalForm * Ptr;
	struct
	{
		size_t ArgPos;
		size_t Size;
		int InArity;
		int OutArity;
	};

	ControlValue()
	{}

	ControlValue(const InternalForm * ptr)
		: Ptr(ptr)
	{}

	ControlValue(int arity)
		: OutArity(arity)
	{}

	ControlValue(size_t argPos, size_t size, int inArity, int outArity)
		: ArgPos(argPos), Size(size), InArity(inArity), OutArity(outArity)
	{}
};


}}