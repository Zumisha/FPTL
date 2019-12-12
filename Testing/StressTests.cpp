#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(_Stress, ArrayCreate4Gb)
		{
			const size_t n = 540000000;

			std::stringstream innerCode;
			innerCode << "@ = ((" << n << " * 1).arrayCreate * " << n-1 << ").arrayGet.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}

		TEST(_Stress, ArrayCreateMaxSize_t)
		{
			const std::string innerCode = "@ = (9223372036854775808 * 0).arrayCreate.print;";

			const std::string expected = "Error: The size of the array must be greater than zero!\nIn function \"arrayCreate\". Line: 4. Column: 14.\nInput tuple type: (int * int)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}
