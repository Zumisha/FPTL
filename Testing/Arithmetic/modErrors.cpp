#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{

		TEST(modErrors, DivideByZero)
		{
			const std::string innerCode = R"(@ = (23 * 0).mod.print;)";
			
			std::stringstream expected;
			expected << R"(Line 1, ch 26: divide by zero)";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(modErrors, StringInsteadInt)
		{
			const std::string innerCode = R"(@ = (23 * "fptl").mod.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 31, invalidOperation("string", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(modErrors, BooleanInsteadInt)
		{
			const std::string innerCode = R"(@ = (23 * false).mod.print;)";

			// Runtime error: invalid operation on type boolean. In function "mod".Line: 1. Column : 19. Input tuple type : (int * boolean)


			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 30, invalidOperation("boolean", "combine with int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(modErrors, OneElemInput)
		{
			const std::string innerCode = R"(@ = (23).mod.print;)";
			// Runtime error: attempt to get the [2] argument in a tuple of size 1.In function "mul".Line: 1. Column : 10.Input tuple type : (int)

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 22, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(modErrors, OutOfRangeBoth)
		{
			const std::string innerCode = R"(@ = (-9223372036854775809 * 9223372036854775808).mod.print;)";
			
			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 1 ch 7 Error: constant is invalid or out of range : '' line 9 ch 30";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
		TEST(modErrors, OutOfRange)
		{
			const std::string innerCode = R"(@ = (-9223372036854775809 * 9223372036854775807).mod.print;)";

			std::stringstream expected;
			expected << "Error : constant is invalid or out of range : '' line 1 ch 7";

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}