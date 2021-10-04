#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		TEST(StringReplace, Null)
		{
			const std::string innerCode = "@ = (\"\" * \"([\\\\w])\" * \"\").replace.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringReplace, One)
		{
			const std::string innerCode = "@ = (\"a\" * \"([\\\\w])\" * \"\").replace.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringReplace, Onetwo)
		{
			const std::string innerCode = "@ = (\"a\" * \"([\\\\w])\" * \"b\").replace.print;";

			const std::string expected = "b";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringReplace, Full)
		{
			const std::string innerCode = "@ = (\"aa\" * \"([\\\\w])\" * \"b\").replace.print;";

			const std::string expected = "bb";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringReplace, ErrType)
		{
			const std::string innerCode = "@ = (\"abc\" * \"([\\\\w])\"  * true).replace.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 45, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringReplace, ErrNull)
		{
			const std::string innerCode = "@ = replace.print;";

			const std::string expected = R"(Line 1, ch 17: attempt to get the [1] argument in a tuple of size 0
In function "replace"
Input tuple type: ()
)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}