#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayLenErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = 0.arrayLen.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 19, invalidOperation("int", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = 1.0.arrayLen.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 21, invalidOperation("double", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = true.arrayLen.print;)";
			
			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 22, invalidOperation("boolean", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = "Array[int]".arrayLen.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 30, invalidOperation("string", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayLenErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = (2*c_nil).c_cons.arrayLen.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 88, invalidOperation("List['t['t]]", "toArray"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayLenErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayLen.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}
