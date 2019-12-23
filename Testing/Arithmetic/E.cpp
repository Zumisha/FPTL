#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(E, One1)
		{
			const std::string innerCode = "@ = (E).ln.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(E, One2)
		{
			const std::string innerCode = "@ = (0 * E).sub.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}