#pragma once

namespace FPTL
{
	namespace Runtime
	{
		class InternalForm;

		union ControlValue
		{
			const InternalForm * Ptr;
			struct
			{
				size_t ArgPos;
				size_t Size;
				size_t InArity;
				size_t OutArity;
			};

			ControlValue() = default;

			ControlValue(const InternalForm * ptr)
				: Ptr(ptr)
			{}

			ControlValue(size_t arity)
				: OutArity(arity)
			{}

			ControlValue(size_t argPos, size_t size, size_t inArity, size_t outArity)
				: ArgPos(argPos), Size(size), InArity(inArity), OutArity(outArity)
			{}
		};
	}
}
