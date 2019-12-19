#include "../Shared.h"
#include "DataTypes/Ops/ADTOps.h"

namespace UnitTests
{
	namespace ADT
	{
		TEST(ADTErrorsTest, InvalidTypeElemBool)
		{
			std::string innerCode = "@ = ((true * (2 * c_nil).c_cons).c_cons).print;";
			innerCode = "Data List{List = c_nil++ int * List.c_cons;}" + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 90, FPTL::Runtime::ADTOps::assignErrMsg("boolean", "int"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}
		

		TEST(ADTErrorsTest, InvalidTypeElemString)
		{
			std::string innerCode = "@ = ((\"str\" * (2 * c_nil).c_cons).c_cons).print;";
			innerCode = "Data List{List = c_nil++ int * List.c_cons;}" + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 91, FPTL::Runtime::ADTOps::assignErrMsg("string", "int"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		TEST(ADTErrorsTest, InvalidTypeElemDouble)
		{
			std::string innerCode = "@ = ((1.2 * (2 * c_nil).c_cons).c_cons).print;";
			innerCode = "Data List{List = c_nil++ int * List.c_cons;}" + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 89, FPTL::Runtime::ADTOps::assignErrMsg("double", "int"));

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}
		
		TEST(ADTErrorsTest, TwoSameConstrucotrs)
		{
			std::string innerCode = "@ = ((true * (2 * c_nil).c_cons).c_cons).print;";
			innerCode = ListDefinition + " Data List2 { List2 = c_nil ++ string * List2.c_cons1; }" + MakeTestProgram(innerCode);

			std::stringstream expected;
			FPTL::Parser::Support::printError(expected, 1, 76, std::string(FPTL::Parser::Support::getErrorString(FPTL::Parser::ParserErrTypes::DuplicateDefinition)) + "c_nil");

			GeneralizedTest(standardInput, expected.str(), innerCode, 1);
		}

		
	}
}
