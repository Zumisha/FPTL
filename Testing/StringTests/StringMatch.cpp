#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		TEST(StringMatch, Null)
		{
			const std::string innerCode = "@ = (\"\" * \"\").match.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringMatch, One)
		{
			const std::string innerCode = "@ = (\"\123\" * \"([\\\\w])\").match.print;";

			const std::string expected = "S";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringMatch, Full)
		{
			const std::string innerCode = "@ = (\"\123\" * \"([\\\\w]+)\").match.print;";

			const std::string expected = "S";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringMatch, ErrType)
		{
			const std::string innerCode = "@ = (\"abc\" * true).match.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 32, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringMatch, ErrNull)
		{
			const std::string innerCode = "@ = match.print;";

			const std::string expected = R"(Line 1, ch 17: attempt to get the [1] argument in a tuple of size 0
In function "match"
Input tuple type: ()
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(StringMatch, ErrType2)
		{
			const std::string innerCode = "@ =  (1 * \"([\\\\w] + )\").match.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 37, invalidOperation("int", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringMatch, ErrOne)
		{
			const std::string innerCode = "@ =  (\"abc\").match.print";

			const std::string expected = R"(Line 1, ch 37: syntax error, unexpected '}', expecting ';')";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}