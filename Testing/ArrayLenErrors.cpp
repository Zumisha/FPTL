#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayLenErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = 0.arrayLen.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayLen\". Line: 1. Column: 19.\nInput tuple type: (int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = 1.0.arrayLen.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayLen\". Line: 1. Column: 21.\nInput tuple type: (double)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = true.arrayLen.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayLen\". Line: 1. Column: 22.\nInput tuple type: (boolean)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = "Array[int]".arrayLen.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayLen\". Line: 1. Column: 30.\nInput tuple type: (string)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = (2*c_nil).c_cons.arrayLen.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayLen\". Line: 1. Column: 88.\nInput tuple type: (List['t['t]])";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArrayLenErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayLen.print;";

			const std::string expected = "Error: attempt to get the [1] argument in a tuple of size 0.\nIn function \"arrayLen\". Line: 1. Column: 17.\nInput tuple type: ()";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}