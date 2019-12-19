#include "../Shared.h"

namespace UnitTests
{
	namespace ADT
	{
		TEST(ADTDoubleParamErrorsTest, InvalidTypeElemBool)
		{
			std::string innerCode = "@ = ((true*3).c_pair).print;";
			innerCode = "Data TPair{TPair = int * int.c_pair;}" + MakeTestProgram(innerCode);

			const std::string expected = R"(Line 1, ch 64: type mismatch. Actual: boolean. Expected: int.
In function "c_pair"
Input tuple type: (boolean * int))";
			//FPTL::Parser::Support::printError(expected, 1, 28, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ADTDoubleParamErrorsTest, InvalidTypeElemDouble)
		{
			std::string innerCode = "@ = ((1.2*3).c_pair).print;";
			innerCode = "Data TPair{TPair = int * int.c_pair;}" + MakeTestProgram(innerCode);

			const std::string expected = R"(Line 1, ch 63: type mismatch. Actual: double. Expected: int.
In function "c_pair"
Input tuple type: (double * int))";
			//FPTL::Parser::Support::printError(expected, 1, 28, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ADTDoubleParamErrorsTest, InvalidTypeElemString)
		{
			std::string innerCode = "@ = ((\"str\"*3).c_pair).print;";
			innerCode = "Data TPair{TPair = int * int.c_pair;}" + MakeTestProgram(innerCode);

			const std::string expected = R"(Line 1, ch 65: type mismatch. Actual: string. Expected: int.
In function "c_pair"
Input tuple type: (string * int))";
			//FPTL::Parser::Support::printError(expected, 1, 28, invalidOperation("boolean", "toInt"));

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}

		TEST(ADTDoubleParamErrorsTest, TwoSameConstrucotrs)
		{
			std::string innerCode = "@ = ((3*2).c_pair).print;";
			innerCode = PairDefinition + "Data TPair2{TPair2 = int * int.c_pair;}" + MakeTestProgram(innerCode);

			const std::string expected = R"(Line 1, ch 76: identifier was defined before. c_pair)";
			//FPTL::Parser::Support::printError(expected, 1, 27, invalidOperation("double", "toInt"));

			GeneralizedTest(standardInput, expected, innerCode, 1);
		}


	}
}