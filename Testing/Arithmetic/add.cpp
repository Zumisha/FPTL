#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(add, One1)
		{
			const std::string innerCode = "@ = (23 * 59).add.print;";

			const std::string expected = "82";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, One2)
		{
			const std::string innerCode = "@ = (1324.73 * 98.32).add.print;";

			const std::string expected = "1423.05";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, One3)
		{
			const std::string innerCode = "@ = (-1324.73 * -95).add.print;";

			const std::string expected = "-1419.73";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, One4)
		{
			const std::string innerCode = "@ = (175 * 3854.721).add.print;";

			const std::string expected = "4029.721";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(add, Two1)
		{
			const std::string innerCode = "@ = (42949672951 * 4294967295).add.print;";

			const std::string expected = "47244640246";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Two2)
		{
			const std::string innerCode = "@ = (42949672951.231 * -1294967295.512).add.print;";

			const std::string expected = "41654705655.719002";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Two3)
		{
			const std::string innerCode = "@ = (10049672951.123 * -1294967295).add.print;";

			const std::string expected = "8754705656.1229992";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Two4)
		{
			const std::string innerCode = "@ = (170000000000031123.1 * 2.44).add.print;";

			const std::string expected = "1.7000000000003114e+17";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Two5)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 9223372036854775806.2).add.print;";

			const std::string expected = "1.8446744073709552e+19";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Three)
		{
			const std::string innerCode = "@ = (0 * 0).add.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(add, Unusual)
		{
			const std::string innerCode = "@ = (9223372036854775806 * 1).add.print;";

			const std::string expected = "9223372036854775807";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}