#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCat, One)
		{
			const std::string innerCode = "@ = (((3 * 1).arrayCreate * 1 * 2).arraySet * 2 * 3).arraySet.(id * arrayCat).(print * ([-1] * 0 * 0).arraySet.print * print);";

			const std::string expected = "[1, 2, 3]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayCat, Three)
		{
			const std::string innerCode = R"(
			@ = (	(1 * 1).arrayCreate * 
					((2 * 2).arrayCreate * 1 * 3).arraySet * 
					(((3 * 4).arrayCreate * 1 * 5).arraySet * 2 * 6).arraySet
				).arrayCat.print;)";

			const std::string expected = "[1, 2, 3, 4, 5, 6]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}