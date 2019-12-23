#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(mul, One1)
		{
			const std::string innerCode = "@ = (23 * 59).mul.print;";

			const std::string expected = "1357";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, One2)
		{
			const std::string innerCode = "@ = (1324.73 * 98.32).mul.print;";

			const std::string expected = "130247.45359999999";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, One3)
		{
			const std::string innerCode = "@ = (-1324.73 * -95).mul.print;";

			const std::string expected = "125849.35000000001";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, One4)
		{
			const std::string innerCode = "@ = (175 * 3854.721).mul.print;";

			const std::string expected = "674576.17500000005";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(mul, Two1)
		{
			const std::string innerCode = "@ = (4294967295 * 429496729).mul.print;";

			const std::string expected = "1844674404364478055";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Two2)
		{
			const std::string innerCode = "@ = (42949672951.231 * -1294967295.512).mul.print;";

			const std::string expected = "-5.5618421824780517e+19";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Two3)
		{
			const std::string innerCode = "@ = (10049672951.123 * -1294967295).mul.print;";

			const std::string expected = "-1.3013997797150417e+19";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Two4)
		{
			const std::string innerCode = "@ = (170000000000031123.1 * 2.44).mul.print;";

			const std::string expected = "4.1480000000007597e+17";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Two5)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 9223372036854775802.2).mul.print;";

			const std::string expected = "8.5070591730234616e+37";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Three)
		{
			const std::string innerCode = "@ = (0 * 0).mul.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mul, Unusual)
		{
			const std::string innerCode = "@ = (4611686018427387903 * 2).mul.print;";

			const std::string expected = "9223372036854775806";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}