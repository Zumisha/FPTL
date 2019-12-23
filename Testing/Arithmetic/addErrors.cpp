#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(addErrors, StringInsteadDouble)
		{
			const std::string innerCode = R"(@ = ("fptl" * 2.3).add.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 21, invalidOperation("double", "combine with string"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(addErrors, BooleanInsteadInt)
		{
			const std::string innerCode = R"(@ = (4 * true).add.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 28, invalidOperation("boolean", "combine with int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(addErrors, OneElemInput)
		{
			const std::string innerCode = R"(@ = (4).add.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 21, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(addErrors, OutOfRange)
		{
			const std::string innerCode = R"(@ = (9223372036854775807 * 1).add.print;)";
			// Не знаю какой должен быть эксепшн, так как он не выдается

			std::stringstream expected;
			expected << "OOR";
			//FPTL::Parser::Support::printError(expected, 1, 10, FPTL::Runtime:::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(addErrors, OutOfRangeResult)
		{
			const std::string innerCode = R"(@ = (9223372036854775807 * 92233720368547758070).add.print;)";

			//Error: constant is invalid or out of range : '' line 1 ch 29

			std::stringstream expected;
			expected << "OOR";
			//FPTL::Parser::Support::printError(expected, 1, 10, FPTL::Runtime:::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}