#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{

		TEST(mulErrors, StringInsteadDouble)
		{
			const std::string innerCode = R"(@ = ("fptl" * 2.3).mul.print;)";
			// странно, что ругается на double, а не string, текст ошибки: 
			// Runtime error: invalid operation on type double.In function "mul".Line: 1. Column : 21. Input tuple type : (string * double)

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 32, invalidOperation("double", "combine with string"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(mulErrors, BooleanInsteadInt)
		{
			const std::string innerCode = R"(@ = (4 * true).mul.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 28, invalidOperation("boolean", "combine with int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(mulErrors, OneElemInput)
		{
			const std::string innerCode = R"(@ = (4).mul.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 21, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(mulErrors, OutOfRangeBoth)
		{
			const std::string innerCode = R"(@ = (9223372036854775808 * -9223372036854775809).mul.print;)";
			
			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 9 ch 7 Error: constant is invalid or out of range : '' line 9 ch 29";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(mulErrors, OutOfRange)
		{
			const std::string innerCode = R"(@ = (9223372036854775808 * 1).mul.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 9 ch 7";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(mulErrors, OutOfRangeResult)
		{
			const std::string innerCode = R"(@ = (4611686018427387904 * 2).mul.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 9 ch 7";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}