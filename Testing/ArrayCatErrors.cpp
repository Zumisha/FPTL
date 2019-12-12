#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCatErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = 0.arrayCat.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayCat\". Line: 1. Column: 19.\nInput tuple type: (int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = 1.0.arrayCat.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayCat\". Line: 1. Column: 21.\nInput tuple type: (double)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = true.arrayCat.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayCat\". Line: 1. Column: 22.\nInput tuple type: (boolean)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = "Array[int]".arrayCat.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayCat\". Line: 1. Column: 30.\nInput tuple type: (string)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = (2*c_nil).c_cons.arrayCat.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayCat\". Line: 1. Column: 88.\nInput tuple type: (List['t['t]])";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArrayCatErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayCat.print;";

			const std::string expected = "Error: attempt to get the [1] argument in a tuple of size 0.\nIn function \"arrayCat\". Line: 1. Column: 17.\nInput tuple type: ()";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, DifferentTypes)
		{
			const std::string innerCode = "@ = ((3 * (3 * 1).arrayCreate).arrayCreate * (3 * (3 * 1.0).arrayCreate).arrayCreate).arrayCat.print;";

			const std::string expected = "Error: Cannot concat an array of type array[array[int]] with an array of type array[array[double]]\nIn function \"arrayCat\". Line: 1. Column: 99.\nInput tuple type: (array[array[int]] * array[array[double]])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}