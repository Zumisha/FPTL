#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArraySetErrors, PositiveOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 3 * 1).arraySet.print;)";

			const std::string expected = "Error: Array index is out of range.\nIn function \"arraySet\". Line: 1. Column: 47.\nInput tuple type: (array[int] * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, NegativeOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * -1 * 1).arraySet.print;)";

			const std::string expected = "Error: Array index is out of range.\nIn function \"arraySet\". Line: 1. Column: 48.\nInput tuple type: (array[int] * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = (0 * 0 * 1).arraySet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arraySet\". Line: 1. Column: 29.\nInput tuple type: (int * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = (1.0 * 0 * 1).arraySet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arraySet\". Line: 1. Column: 31.\nInput tuple type: (double * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = (true * 0 * 1).arraySet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arraySet\". Line: 1. Column: 32.\nInput tuple type: (boolean * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = ("Array[int]" * 0 * 1).arraySet.print;)";

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arraySet\". Line: 1. Column: 40.\nInput tuple type: (string * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0 * 1).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: Invalid operation on not array value.\nIn function \"arraySet\". Line: 1. Column: 98.\nInput tuple type: (List['t['t]] * int * int)";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArraySetErrors, DoubleIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 0.0 * 1).arraySet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, BoolIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * true * 1).arraySet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, StringIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * "1" * 1).arraySet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ArrayIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * (3 * 0).arrayCreate * 1).arraySet.print;)";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTIndex)
		{
			std::string innerCode = "@ = ((3 * 0).arrayCreate * (2*c_nil).c_cons * 1).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArraySetErrors, IntToArray)
		{
			const std::string innerCode = R"(@ = ((3 * (3 * 0).arrayCreate).arrayCreate * 1 * 1).arraySet.print;)";

			const std::string expected = "Error: cannot assign element of type int to an array of type array[int].\nIn function \"arraySet\". Line: 1. Column: 65.\nInput tuple type: (array[array[int]] * int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ArrayDoubleToArrayInt)
		{
			const std::string innerCode = R"(@ = ((3 * (3 * 0).arrayCreate).arrayCreate * 1 * (3 * 1.0).arrayCreate).arraySet.print;)";

			const std::string expected = "Error: cannot assign element of type array[double] to an array of type array[int].\nIn function \"arraySet\". Line: 1. Column: 85.\nInput tuple type: (array[array[int]] * int * array[double])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTToADT)
		{
			std::string innerCode = "@ = ((3 * (0*c_nil).c_cons).arrayCreate * 1 * (1.0*c_nil).c_cons).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ArraySetErrors, TwoArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate * 1).arraySet.print;";

			const std::string expected = "Error: attempt to get the [3] argument in a tuple of size 2.\nIn function \"arraySet\". Line: 1. Column: 43.\nInput tuple type: (array[int] * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, OneArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate).arraySet.print;";

			const std::string expected = "Error: attempt to get the [2] argument in a tuple of size 1.\nIn function \"arraySet\". Line: 1. Column: 39.\nInput tuple type: (array[int])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arraySet.print;";

			const std::string expected = "Error: attempt to get the [1] argument in a tuple of size 0.\nIn function \"arraySet\". Line: 1. Column: 17.\nInput tuple type: ()";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}