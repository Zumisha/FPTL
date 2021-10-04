#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{

		TEST(subErrors, StringInsteadDouble)
		{
			const std::string innerCode = R"(@ = ("fptl" * 2.3).sub.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 32, invalidOperation("double", "combine with string"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(subErrors, BooleanInsteadInt)
		{
			const std::string innerCode = R"(@ = (4 * true).sub.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 28, invalidOperation("boolean", "combine with int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(subErrors, OneElemInput)
		{
			const std::string innerCode = R"(@ = (4).sub.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 21, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(subErrors, OutOfRange)
		{
			const std::string innerCode = R"(@ = (9223372036854775808 * 1).sub.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 1 ch 7";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(subErrors, OutOfRangeBoth)
		{
			const std::string innerCode = R"(@ = (9223372036854775807 * 92233720368547758070).sub.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 1 ch 29";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}