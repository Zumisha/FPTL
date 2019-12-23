#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{

		TEST(Rand, One)
		{
			const size_t n = 10000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0).Rand.print;
			Rand = ([1] * 
			)" << n << R"(
			).less -> ((rand * 1).greater -> (9999999).Rand, ([1] * 1).add.Rand), [1];
			)";
			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
	}
}