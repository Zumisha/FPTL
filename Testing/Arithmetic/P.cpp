#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(P, One1)
		{
			const std::string innerCode = "@ = (Pi).cos.print;";

			const std::string expected = "-1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(P, One2)
		{
			const std::string innerCode = "@ = (Pi * 2).mul.sin.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(P, One3)
		{
			const std::string innerCode = "@ = (Pi * 2).div.sin.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(P, One4)
		{
			const std::string innerCode = "@ = (0 * Pi).sub.sin.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(P, One5)
		{
			const std::string innerCode = "@ = (Pi * 4).div.tan.print;";

			const std::string expected = "0.99999999999999989";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}