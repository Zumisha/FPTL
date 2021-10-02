#include <iostream>

#include "jemalloc/jemalloc.h"

#include "Macros.h"
#include "Interpreter/Interpreter.h"

int** reserve = nullptr;

void * operator new (const std::size_t count)
{
#if fptlDebugBuild
	try
	{
		return je_malloc(count);
	}
	catch (std::exception& e)
	{
		throw;
	}
	catch (...)
	{
		delete reserve[0];
		for (int i = 1; i < 1000; ++i) delete reserve[i];
		delete[] reserve;
		std::cerr << "Stack Overflow Exception" << std::endl
			<< "Execution aborted." << std::endl;
		throw std::exception("Stack Overflow");
	}
#else
	return je_malloc(count);
#endif
}

void * operator new[](const std::size_t count)
{
#if fptlDebugBuild
	try
	{
		return je_malloc(count);
	}
	catch (std::exception& e)
	{
		throw;
	}
	catch (...)
	{
		delete reserve[0];
		for (int i = 1; i < 1000; ++i) delete reserve[i];
		delete[] reserve;
		std::cerr << "Stack Overflow Exception" << std::endl
			<< "Execution aborted." << std::endl;
		throw std::exception("Stack Overflow");
	}
#else
	return je_malloc(count);
#endif
}

void operator delete(void * ptr) noexcept
{
	je_free(ptr);
}

void operator delete[](void * ptr) noexcept
{
	je_free(ptr);
}

int main(const int argc, const char ** argv)
{
#if fptlDebugBuild
	reserve = new int*[1000];
	for (size_t i = 0; i < 1000; ++i)
		reserve[i] = new int;
#endif
	const FPTL::Runtime::Interpreter interpreter;
	return interpreter.Eval(argc, argv);
}