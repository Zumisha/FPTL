#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayFromFileErrors, IntInsteadArray)
		{
			const std::string innerCode = R"(@ = (0 * "Tests").arrayFromFile.print;)";
			
			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 31, invalidOperation("int", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, DoubleInsteadArray)
		{
			const std::string innerCode = R"(@ = (1.0 * "Tests").arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 33, invalidOperation("double", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, BoolInsteadArray)
		{
			const std::string innerCode = R"(@ = (true * "Tests").arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 34, invalidOperation("boolean", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, StringInsteadArray)
		{
			const std::string innerCode = R"(@ = ("Array[int]" * "Tests").arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 42, invalidOperation("string", "toArray"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, ADTInsteadArray)
		{
			std::string innerCode = R"(@ = ((2*c_nil).c_cons * "Tests").arrayFromFile.print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 100, invalidOperation("List['t['t]]", "toArray"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayFromFileErrors, IntInsteadString)
		{
			const std::string innerCode = R"(@ = ((100 * 0.0).arrayCreate * 1).arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 47, invalidOperation("int", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, DoubleInsteadString)
		{
			const std::string innerCode = R"(@ = ((100 * 0.0).arrayCreate * 1.0).arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 49, invalidOperation("double", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, BoolInsteadString)
		{
			const std::string innerCode = R"(@ = ((100 * 0.0).arrayCreate * true).arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 50, invalidOperation("boolean", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, ArrayInsteadString)
		{
			const std::string innerCode = R"(@ = ((100 * 0.0).arrayCreate * (100 * 0.0).arrayCreate).arrayFromFile.print;)";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 69, invalidOperation("array[double]", "toString"));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, ADTInsteadString)
		{
			std::string innerCode = R"(@ = ((100 * 0.0).arrayCreate * (2*c_nil).c_cons).arrayFromFile.print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 116, invalidOperation("List['t['t]]", "toString"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ArrayFromFileErrors, OneArityInput)
		{
			const std::string innerCode = "@ = (100 * 0.0).arrayCreate.arrayFromFile.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 41, FPTL::Runtime::SExecutionContext::outOfRange(2, 1));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}

		TEST(ArrayFromFileErrors, ZeroArityInput)
		{
			const std::string innerCode = "@ = arrayFromFile.print;";

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 17, FPTL::Runtime::SExecutionContext::outOfRange(1, 0));

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode), 1);
		}
	}
}
