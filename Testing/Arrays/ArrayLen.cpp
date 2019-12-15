#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayLen, Len)
		{
			const std::string innerCode = "@ = (10 * 0).arrayCreate.arrayLen.print;";

			const std::string expected = "10";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}