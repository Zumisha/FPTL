#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArraySet, Bool)
		{
			const std::string innerCode = R"(
			@ = (3 * true).arrayCreate.
				(print * 
				([1] * 0 * false).arraySet.print * 
				print);
			)";

			const std::string expected = "[true, true, true][false, true, true]";//[true, true, true]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, Int)
		{
			const std::string innerCode = R"(
			@ = (3 * -1).arrayCreate.
				(print * 
				([1] * 1 * 0).arraySet.print * 
				print);
			)";

			const std::string expected = "[-1, -1, -1][-1, 0, -1]";//[-1, -1, -1]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, Double)
		{
			const std::string innerCode = R"(
			@ = (3 * 1.0).arrayCreate.
				(print * 
				([1] * 2 * 0.0).arraySet.print * 
				print);
			)";

			const std::string expected = "[1, 1, 1][1, 1, 0]";//[1, 1, 1]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, String)
		{
			const std::string innerCode = R"(
			@ = (3 * "asd").arrayCreate.
				(print * 
				([1] * 1 * "qwe").arraySet.print * 
				print);
			)";

			const std::string expected = R"([asd, asd, asd][asd, qwe, asd])";//[asd, asd, asd])";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, Array)
		{
			const std::string innerCode = R"(
			@ = (3 * (2*0).arrayCreate).arrayCreate.
				(print * 
				([1] * 1 * (3*1).arrayCreate).arraySet.print * 
				print);
			)";

			const std::string expected = "[[0, 0],\n[0, 0],\n[0, 0]][[0, 0],\n[1, 1, 1],\n[0, 0]]";//[[0, 0],\n[0, 0],\n[0, 0]]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, ADT)
		{
			std::string innerCode = R"(
			@ = (3 * (2*c_nil).c_cons).arrayCreate.
				(print * 
				([1] * 1 * (3 * (1 * c_nil).c_cons).c_cons).arraySet.print * 
				print);
			)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "[(2*c_nil).c_cons, (2*c_nil).c_cons, (2*c_nil).c_cons][(2*c_nil).c_cons, (3*(1*c_nil).c_cons).c_cons, (2*c_nil).c_cons]";//[(2*c_nil).c_cons, (2*c_nil).c_cons, (2*c_nil).c_cons]";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ArraySet, ElementArrayChange)
		{
			const std::string innerCode = R"(
			@ = (3 * (2*0).arrayCreate).arrayCreate.
				(print * 
				(([1] * 1).arrayGet * 1 * 3).arraySet.print * 
				print);
			)";

			//const std::string expected = "[[0, 0],\n[0, 0],\n[0, 0]][0, 3][[0, 0],\n[0, 0],\n[0, 0]]";
			const std::string expected = "[[0, 0],\n[0, 0],\n[0, 0]][0, 3][[0, 0],\n[0, 3],\n[0, 0]]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArraySet, ElementADTChange)
		{
			std::string innerCode = R"(
			@ = (3 * (2*c_nil).c_cons).arrayCreate.
				(print * 
				([1] * 2).arrayGet.~c_cons.print * 
				print);
			)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "[(2*c_nil).c_cons, (2*c_nil).c_cons, (2*c_nil).c_cons]2 * c_nil[(2*c_nil).c_cons, (2*c_nil).c_cons, (2*c_nil).c_cons]";

			GeneralizedTest(standardInput, expected, innerCode);
		}
	}
}