#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		TEST(StringGetToken, Null)
		{
			const std::string innerCode = "@ = (\"\" * \"\").getToken.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringGetToken, One)
		{
			const std::string innerCode = "@ = (\"121\" * \"1\").getToken.print;";

			const std::string expected = "1 * 21";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringGetToken, Reg)
		{
			const std::string innerCode = "@ = (\"111\" * \"([\\\\w])\").getToken.print;";

			const std::string expected = "1 * 11";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringGetToken, ErrType)
		{
			const std::string innerCode = "@ = (\"abc\" * true).getToken.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 32, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringGetToken, ErrNull)
		{
			const std::string innerCode = "@ = getToken.print;";

			const std::string expected = R"(Line 1, ch 17: attempt to get the [1] argument in a tuple of size 0
In function "getToken"
Input tuple type: ()
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(StringGetToken, ErrType2)
		{
			const std::string innerCode = "@ =  (1 * \"([\\\\w] + )\").getToken.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 37, invalidOperation("int", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringGetToken, ErrOne)
		{
			const std::string innerCode = "@ =  (\"abc\").getToken.print;";

			const std::string expected = R"(Line 1, ch 26: attempt to get the [2] argument in a tuple of size 1
In function "getToken"
Input tuple type: (string)
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}