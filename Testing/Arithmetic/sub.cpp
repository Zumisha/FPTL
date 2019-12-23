#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(sub, One1)
		{
			const std::string innerCode = "@ = (23 * 59).sub.print;";

			const std::string expected = "-36";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, One2)
		{
			const std::string innerCode = "@ = (1324.73 * 98.32).sub.print;";

			const std::string expected = "1226.4100000000001";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, One3)
		{
			const std::string innerCode = "@ = (-1324.73 * -95).sub.print;";

			const std::string expected = "-1229.73";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, One4)
		{
			const std::string innerCode = "@ = (175 * 3854.721).sub.print;";

			const std::string expected = "-3679.721";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(sub, Two1)
		{
			const std::string innerCode = "@ = (42949672951 * 4294967295).sub.print;";

			const std::string expected = "38654705656";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Two2)
		{
			const std::string innerCode = "@ = (42949672951.231 * -1294967295.512).sub.print;";

			const std::string expected = "44244640246.743004";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Two3)
		{
			const std::string innerCode = "@ = (10049672951.123 * -1294967295).sub.print;";

			const std::string expected = "11344640246.122999";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Two4)
		{
			const std::string innerCode = "@ = (170000000000031123.1 * 2.44).sub.print;";

			const std::string expected = "1.7000000000003114e+17";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Two5)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 9223372036854775802.2).sub.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Three)
		{
			const std::string innerCode = "@ = (0 * 0).sub.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(sub, Unusual)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 1).sub.print;";

			const std::string expected = "9223372036854775806";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}