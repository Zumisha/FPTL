#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(divErrors, DivideByZero)
		{
			const std::string innerCode = R"(@ = (121 * 0).div.print;)";

			std::stringstream expected;
			expected << R"(Line 1, ch 27: divide by zero )";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(divErrors, StringInsteadDouble)
		{
			const std::string innerCode = R"(@ = (121.2 * "fptl").div.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 34, invalidOperation("string", "toDouble"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(divErrors, BooleanInsteadInt)
		{
			const std::string innerCode = R"(@ = (121 * false).div.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 20, invalidOperation("boolean", "combine with int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(divErrors, OneElemInput)
		{
			const std::string innerCode = R"(@ = (121).div.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 23, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(divErrors, OutOfRangeBoth)
		{
			const std::string innerCode = R"(@ = (9223372036854775808 * -9223372036854775809).div.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 8 ch 7 Error: constant is invalid or out of range : '' line 1 ch 29";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(divErrors, OutOfRange)
		{
			const std::string innerCode = R"(@ = (9223372036854775808 * 2).div.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 1 ch 7";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}