#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayCreate, Bool)
		{
			const std::string innerCode = "@ = (2 * true).arrayCreate.(print * printType);";

			const std::string expected = "[true, true](array[boolean])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayCreate, Int)
		{
			const std::string innerCode = "@ = (2 * -1).arrayCreate.(print * printType);";

			const std::string expected = "[-1, -1](array[int])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayCreate, Double)
		{
			const std::string innerCode = "@ = (2 * 1.0).arrayCreate.(print * printType);";

			const std::string expected = "[1, 1](array[double])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayCreate, String)
		{
			const std::string innerCode = R"(@ = (2 * "asd").arrayCreate.(print * printType);)";

			const std::string expected = R"([asd, asd](array[string]))";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayCreate, Array)
		{
			const std::string innerCode = "@ = (2*(2*0).arrayCreate).arrayCreate.(print * printType);";

			const std::string expected = "[[0, 0],\n[0, 0]](array[array[int]])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		
		TEST(ArrayCreate, ADT)
		{
			std::string innerCode = "@ = (2*(2*c_nil).c_cons).arrayCreate.(print * printType);";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "[(2*c_nil).c_cons, (2*c_nil).c_cons](array[List['t['t]]])";

			GeneralizedTest(standardInput, expected, innerCode);
		}
	}
}