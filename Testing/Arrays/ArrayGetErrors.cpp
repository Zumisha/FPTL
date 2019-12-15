#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayGetErrors, PositiveOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 3).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 43, FPTL::Runtime::ArrayValue::badIndexMsg(3, 3));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, NegativeOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * -1).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 44, FPTL::Runtime::ArrayValue::badIndexMsg(3, -1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = (0 * 0).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 25, invalidOperation("int", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = (1.0 * 0).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 27, invalidOperation("double", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = (true * 0).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 28, invalidOperation("boolean", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = ("Array[int]" * 0).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 36, invalidOperation("string", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0).arrayGet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 94, invalidOperation("List['t['t]]", "toArray"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayGetErrors, DoubleIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 0.0).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 45, invalidOperation("double", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, BoolIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * true).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 46, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, StringIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * "1").arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 45, invalidOperation("string", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ArrayIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * (3 * 0).arrayCreate).arrayGet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 61, invalidOperation("array[int]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ADTIndex)
		{
			std::string innerCode = "@ = ((3 * 0).arrayCreate * (2*c_nil).c_cons).arrayGet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 112, invalidOperation("List['t['t]]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayGetErrors, OneArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate).arrayGet.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 39, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayGetErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayGet.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}