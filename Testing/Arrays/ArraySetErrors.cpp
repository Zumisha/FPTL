#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArraySetErrors, PositiveOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 3 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 47, FPTL::Runtime::ArrayValue::badIndexMsg(3, 3));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, NegativeOOR)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * -1 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 48, FPTL::Runtime::ArrayValue::badIndexMsg(3, -1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = (0 * 0 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 29, invalidOperation("int", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = (1.0 * 0 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 31, invalidOperation("double", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = (true * 0 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 32, invalidOperation("boolean", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = ("Array[int]" * 0 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 40, invalidOperation("string", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTInsteadArray)
		{
			std::string innerCode = "@ = ((2*c_nil).c_cons * 0 * 1).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 98, invalidOperation("List['t['t]]", "toArray"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArraySetErrors, DoubleIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * 0.0 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 49, invalidOperation("double", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, BoolIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * true * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 50, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, StringIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * "1" * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 49, invalidOperation("string", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ArrayIndex)
		{
			const std::string innerCode = R"(@ = ((3 * 0).arrayCreate * (3 * 0).arrayCreate * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 65, invalidOperation("array[int]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTIndex)
		{
			std::string innerCode = "@ = ((3 * 0).arrayCreate * (2*c_nil).c_cons * 1).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 116, invalidOperation("List['t['t]]", "toInt"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArraySetErrors, IntToArray)
		{
			const std::string innerCode = R"(@ = ((3 * (3 * 0).arrayCreate).arrayCreate * 1 * 1).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 65, FPTL::Runtime::ArrayValue::assignErrMsg("int", "array[int]"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ArrayDoubleToArrayInt)
		{
			const std::string innerCode = R"(@ = ((3 * (3 * 0).arrayCreate).arrayCreate * 1 * (3 * 1.0).arrayCreate).arraySet.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 85, FPTL::Runtime::ArrayValue::assignErrMsg("array[double]", "array[int]"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ADTToADT)
		{
			std::string innerCode = "@ = ((3 * (0*c_nil).c_cons).arrayCreate * 1 * (1.0*c_nil).c_cons).arraySet.print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 65, FPTL::Runtime::ArrayValue::assignErrMsg("List[double]", "List[int]"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArraySetErrors, TwoArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate * 1).arraySet.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 43, FPTL::Runtime::SExecutionContext::outOfRange(3, 2));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, OneArityInput)
		{
			const std::string innerCode = "@ = ((3 * 0).arrayCreate).arraySet.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 39, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArraySetErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arraySet.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}