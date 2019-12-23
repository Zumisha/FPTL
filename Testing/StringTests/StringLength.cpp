#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		const std::string teststring = "abc123";

		TEST(StringLength, One)
		{
			const std::string innerCode = "@ = (\"1\").length.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringLength, Null)
		{
			const std::string innerCode = "@ = (\"\").length.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringLength, ErrType)
		{
			const std::string innerCode = "@ = 1.length.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 19, invalidOperation("int", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringLength, ErrNull)
		{
			const std::string innerCode = "@ = length.print;";

			const std::string expected = R"(Line 1, ch 17: attempt to get the [1] argument in a tuple of size 0
In function "length"
Input tuple type: ()
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}