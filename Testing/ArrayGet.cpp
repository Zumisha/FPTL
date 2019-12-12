#include "Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayGet, Bool)
		{
			const std::string innerCode = R"(
			@ = (((3 * true).arrayCreate * 1 * false).arraySet * 2 * false).arraySet.
				(print * 
				([1] * 0).arrayGet.print * 
				print);
			)";

			const std::string expected = "[true, false, false]true[true, false, false]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayGet, Int)
		{
			const std::string innerCode = R"(
			@ = (((3 * 1).arrayCreate * 1 * 2).arraySet * 2 * 3).arraySet.
				(print * 
				([1] * 1).arrayGet.print * 
				print);
			)";

			const std::string expected = "[1, 2, 3]2[1, 2, 3]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayGet, Double)
		{
			const std::string innerCode = R"(
			@ = (((3 * 1.0).arrayCreate * 1 * 2.0).arraySet * 2 * 3.0).arraySet.
				(print * 
				([1] * 2).arrayGet.print * 
				print);
			)";

			const std::string expected = "[1, 2, 3]3[1, 2, 3]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayGet, String)
		{
			const std::string innerCode = R"(
			@ = (((3 * "asd").arrayCreate * 1 * "sdf").arraySet * 2 * "dfg").arraySet.
				(print * 
				([1] * 1).arrayGet.print * 
				print);
			)";

			const std::string expected = "[asd, sdf, dfg]sdf[asd, sdf, dfg]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayGet, Array)
		{
			const std::string innerCode = R"(
			@ = (((3 * (2*1).arrayCreate).arrayCreate * 1 * (2*2).arrayCreate).arraySet * 2 * (2*3).arrayCreate).arraySet.
				(print * 
				([1] * 1).arrayGet.print * 
				print);
			)";

			const std::string expected = "[[1, 1],\n[2, 2],\n[3, 3]][2, 2][[1, 1],\n[2, 2],\n[3, 3]]";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayGet, ADT)
		{
			std::string innerCode = R"(
			@ = (((3 * (1*c_nil).c_cons).arrayCreate * 1 * (2*c_nil).c_cons).arraySet * 2 * (3*c_nil).c_cons).arraySet.
				(print * 
				([1] * 1).arrayGet.print * 
				print);
			)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "[(1*c_nil).c_cons, (2*c_nil).c_cons, (3*c_nil).c_cons](2*c_nil).c_cons[(1*c_nil).c_cons, (2*c_nil).c_cons, (3*c_nil).c_cons]";

			GeneralizedTest(standardInput, expected, innerCode);
		}
	}
}