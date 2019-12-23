#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(div, One1)
		{
			const std::string innerCode = "@ = (69 * -23).div.print;";

			const std::string expected = "-3";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, One2)
		{
			const std::string innerCode = "@ = (1324.73 * 98.32).div.print;";

			const std::string expected = "13.473657445077301";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, One3)
		{
			const std::string innerCode = "@ = (-1324.73 * -95).div.print;";

			const std::string expected = "13.944526315789474";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, One4)
		{
			const std::string innerCode = "@ = (175 * 3854.721).div.print;";

			const std::string expected = "0.045398875820065833";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(div, Two1)
		{
			const std::string innerCode = "@ = (4294967295 * 42949675).div.print;";

			const std::string expected = "99";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Two2)
		{
			const std::string innerCode = "@ = (42949672951.231 * -1294967295.512).div.print;";

			const std::string expected = "-33.166608222526342";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Two3)
		{
			const std::string innerCode = "@ = (10049672951.123 * -1294967295).div.print;";

			const std::string expected = "-7.7605612048472619";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Two4)
		{
			const std::string innerCode = "@ = (170000000000031123.1 * 2.44).div.print;";

			const std::string expected = "69672131147553744";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Two5)
		{
			const std::string innerCode = "@ = (9223372036854775806 * 2.2).div.print;";

			const std::string expected = "4.1924418349339889e+18";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(div, Three1)
		{
			const std::string innerCode = "@ = (0 * -121.5).div.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Three2)
		{
			const std::string innerCode = "@ = (0 * -121).div.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Three3)
		{
			const std::string innerCode = "@ = (-0 * 121).div.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(div, Unusual1)
		{
			const std::string innerCode = "@ = (9223372036854775807 * -9223372036854775808).div.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(div, Unusual2)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 9223372036854775807).div.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}