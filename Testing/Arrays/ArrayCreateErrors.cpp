#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCreateErrors, ZeroSize)
		{
			const std::string innerCode = "@ = (0 * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 25, FPTL::Runtime::ArrayValue::negativeSizeMsg(0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, NegativeSize)
		{
			const std::string innerCode = "@ = (-1 * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 26, FPTL::Runtime::ArrayValue::negativeSizeMsg(-1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, VeryBigNegativeSize)
		{
			const std::string innerCode = "@ = (-9223372036854775807 * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 44, FPTL::Runtime::ArrayValue::negativeSizeMsg(-9223372036854775807));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, VeryBigPositiveSize)
		{
			const std::string innerCode = "@ = (9223372036854775807 * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 43, FPTL::Runtime::ArrayValue::overflowSizeMsg(9223372036854775807, "int"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, BoolSize)
		{
			const std::string innerCode = "@ = (true * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 28, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, DoubleSize)
		{
			const std::string innerCode = "@ = (2.0 * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 27, invalidOperation("double", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, StringSize)
		{
			const std::string innerCode = "@ = (\"1\" * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 27, invalidOperation("string", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ArraySize)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate * 0).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 43, invalidOperation("array[int]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ADTSize)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0).arrayCreate.(print * printType);";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 94, invalidOperation("List['t['t]]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayCreateErrors, OneArityInput)
		{
			const std::string innerCode = "@ = (1).arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 21, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayCreateErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayCreate.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printPositionalMessage(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}