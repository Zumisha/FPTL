#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCreateErrors, ZeroSize)
		{
			const std::string innerCode = "@ = (0 * 0).arrayCreate.print;";

			const std::string expected = R"(Error: The size of the array must be greater than zero!
In function "arrayCreate". Line: 1. Column: 25.
Input tuple type: (int * int))";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, NegativeSize)
		{
			const std::string innerCode = "@ = (-1 * 0).arrayCreate.print;";

			const std::string expected = R"(Error: The size of the array must be greater than zero!
In function "arrayCreate". Line: 1. Column: 26.
Input tuple type: (int * int))";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, VeryBigNegativeSize)
		{
			const std::string innerCode = "@ = (-9223372036854775809 * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, VeryBigPositiveSize)
		{
			const std::string innerCode = "@ = (9223372036854775808 * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, BoolSize)
		{
			const std::string innerCode = "@ = (true * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, DoubleSize)
		{
			const std::string innerCode = "@ = (2.0 * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, StringSize)
		{
			const std::string innerCode = "@ = (\"asd\" * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ArraySize)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ADTSize)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0).arrayCreate.(print * printType);";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = R"(Error: int operation on not int value.
In function "arrayCreate". Line: 1. Column: 94.
Input tuple type: (List['t['t]] * int))";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArrayCreateErrors, OneArityInput)
		{
			const std::string innerCode = "@ = (1).arrayCreate.print;";

			const std::string expected = R"(Error: attempt to get the [2] argument in a tuple of size 1.
In function "arrayCreate". Line: 1. Column: 21.
Input tuple type: (int))";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayCreate.print;";

			const std::string expected = R"(Error: attempt to get the [1] argument in a tuple of size 0.
In function "arrayCreate". Line: 1. Column: 17.
Input tuple type: ())";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}