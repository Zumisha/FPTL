#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayGetErrors, PositiveOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 3).arrayGet.print;)";

			const std::string expected = "Error: Array index is out of range.\nIn function \"arrayGet\". Line: 1. Column: 43.\nInput tuple type: (array[int] * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, NegativeOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * -1).arrayGet.print;)";

			const std::string expected = "Error: Array index is out of range.\nIn function \"arrayGet\". Line: 1. Column: 44.\nInput tuple type: (array[int] * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = (0 * 0).arrayGet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayGet\". Line: 1. Column: 25.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = (1.0 * 0).arrayGet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayGet\". Line: 1. Column: 27.\nInput tuple type: (double * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = (true * 0).arrayGet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayGet\". Line: 1. Column: 28.\nInput tuple type: (boolean * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = ("Array[int]" * 0).arrayGet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayGet\". Line: 1. Column: 36.\nInput tuple type: (string * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0).arrayGet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arrayGet\". Line: 1. Column: 94.\nInput tuple type: (List['t['t]] * int)";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArrayGetErrors, DoubleIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 0.0).arrayGet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, BoolIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * true).arrayGet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, StringIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * "1").arrayGet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ArrayIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * (3 * 0).arrayCreate).arrayGet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ADTIndex)
		{
			std::string innerCode = "@ = ((3 * 0).arrayCreate * (2*c_nil).c_cons).arrayGet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArrayGetErrors, OneArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate).arrayGet.print;";

			const std::string expected = "Error: attempt to get the [2] argument in a tuple of size 1.\nIn function \"arrayGet\". Line: 1. Column: 39.\nInput tuple type: (array[int])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayGet.print;";

			const std::string expected = "Error: attempt to get the [1] argument in a tuple of size 0.\nIn function \"arrayGet\". Line: 1. Column: 17.\nInput tuple type: ()";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}