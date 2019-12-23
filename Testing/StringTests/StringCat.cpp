#include "../Shared.h"

namespace UnitTests
{
	namespace Strings
	{
		const std::string teststring = "abc123";
		TEST(StringCat, One)
		{
			const std::string innerCode = "@ = (\"a\" * \"\").cat.print;";

			const std::string expected = "a";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringCat, Two)
		{
			const std::string innerCode = "@ = (\"a\" * \"b\").cat.print;";

			const std::string expected = "ab";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringCat, Three)
		{
			const std::string innerCode = "@ = (\"1\" * \"2\" * \"3\").cat.print;";

			const std::string expected = "123";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(StringCat, Null)
		{
			const std::string innerCode = "@ = (\"\" * \"\" * \"\").cat.print;";

			const std::string expected = "";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(StringCat, ErrType)
		{
			const std::string innerCode = "@ =  (\"a\" * true).cat.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 31, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(StringCat, ErrNull)
		{
			const std::string innerCode = "@ = (\"a\" * ).cat.print;";

			const std::string expected = R"(Line 1, ch 24: syntax error, unexpected ')')";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}