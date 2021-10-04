#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		TEST(StringSearch, Null)
		{
			const std::string innerCode = "@ = (\"\" * \"\").search.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringSearch, One)
		{
			const std::string innerCode = "@ = (\"\123\" * \"([\\\\w])\").search.print;";

			const std::string expected = "S";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringSearch, Full)
		{
			const std::string innerCode = "@ = (\"\123\" * \"([\\\\w]+)\").search.print;";

			const std::string expected = "S";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringSearch, ErrType)
		{
			const std::string innerCode = "@ = (\"abc\" * true).search.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 32, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringSearch, ErrNull)
		{
			const std::string innerCode = "@ = search.print;";

			const std::string expected = R"(Line 1, ch 17: attempt to get the [1] argument in a tuple of size 0
In function "search"
Input tuple type: ()
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(StringSearch, ErrType2)
		{
			const std::string innerCode = "@ =  (1 * \"([\\\\w] + )\").search.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 37, invalidOperation("int", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringSearch, ErrOne)
		{
			const std::string innerCode = "@ =  (\"abc\").search.print";

			const std::string expected = R"(Line 1, ch 38: syntax error, unexpected '}', expecting ';')";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}