#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCatErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = 0.arrayCat.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 19, invalidOperation("int", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = ((3 * 1.0).arrayCreate * 1.0 * (3 * 1.0).arrayCreate).arrayCat.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 71, invalidOperation("double", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = true.arrayCat.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 22, invalidOperation("boolean", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = "Array[int]".arrayCat.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 30, invalidOperation("string", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = (2*c_nil).c_cons.arrayCat.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 88, invalidOperation("List['t['t]]", "toArray"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayCatErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayCat.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCatErrors, DifferentTypes)
		{
			const std::string innerCode = "@ = ((3 * (3 * 1).arrayCreate).arrayCreate * (3 * (3 * 1.0).arrayCreate).arrayCreate).arrayCat.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 99, FPTL::Runtime::ArrayValue::concatErrMsg("array[array[int]]", "array[array[double]]"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}
