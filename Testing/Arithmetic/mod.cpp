#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(mod, One1)
		{
			const std::string innerCode = "@ = (54 * 5).mod.print;";

			const std::string expected = "4";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, One2)
		{
			const std::string innerCode = "@ = (54 * -5).mod.print;";

			const std::string expected = "4";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, One3)
		{
			const std::string innerCode = "@ = (-54 * -5).mod.print;";

			const std::string expected = "-4";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(mod, Two1)
		{
			const std::string innerCode = "@ = (42949672951 * 42949672944).mod.print;";

			const std::string expected = "7";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, Two2)
		{
			const std::string innerCode = "@ = (42949672951 * -42949672944).mod.print;";

			const std::string expected = "7";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, Two3)
		{
			const std::string innerCode = "@ = (-42949672951 * -42949672944).mod.print;";

			const std::string expected = "-7";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, Two4)
		{
			const std::string innerCode = "@ = (-42949672944 * -42949672951).mod.print;";

			const std::string expected = "-42949672944";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(mod, Three1)
		{
			const std::string innerCode = "@ = (0 * -10).mod.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(mod, Three2)
		{
			const std::string innerCode = "@ = (0 * 23).mod.print;";

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}


		TEST(mod, Unusual1)
		{
			const std::string innerCode = "@ = (-9223372036854775808 * 9223372036854775807).mod.print;";

			const std::string expected = "-1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}