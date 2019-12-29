#include "../Shared.h"

namespace UnitTests
{
	namespace Test_tuple
	{
		TEST(TupleTestErrors, TakeSomeInEmpty)
		{
			std::string innerCode = "@ = [1].print;";
			innerCode = MakeTestProgram(innerCode);
			
			const std::string expected = R"(
				attempt to get the [1] argument in a tuple of size 0
				Line: 6. Column: 5.
				Input tuple type: ()

				Execution aborted
			)";
			
			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TupleTestErrors, TakeZero)
		{
			std::string innerCode = R"(@ = (1 * 2.1 * true * "hello" * (2 * 0).arrayCreate*(true*(true*c_nil).c_cons).c_cons).[0].print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);
			
			const std::string expected = R"(
				attempt to get the [0] argument in a tuple of size 6
				Line: 93. Column: 5.
				Input tuple type: (int * double * boolean * string * array[int] * List['t['t]])

				Execution aborted.
			)";
			
			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TupleTestErrors, TakeOutOfRange)
		{
			std::string innerCode = R"(@ = (1 * 2.1 * true * "hello" * (2 * 0).arrayCreate*(true*(true*c_nil).c_cons).c_cons).[7].print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);
			
			const std::string expected = R"(
				attempt to get the [7] argument in a tuple of size 6
				Line: 93. Column: 6.
				Input tuple type: (int * double * boolean * string * array[int] * List['t['t]])

				Execution aborted.
			)";
			
			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TupleTestErrors, TakeOutOfRangeMinus)
		{
			std::string innerCode = R"(@ = (1 * 2.0 * true * "hello" * (2 * 0).arrayCreate *  (true*(true*c_nil).c_cons).c_cons).[-7].print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);
			
				const std::string expected = R"(
				attempt to get the [0] argument in a tuple of size 6
				Line: 93. Column: 6.
				Input tuple type: (int * double * boolean * string * array[int] * List['t['t]])

				Execution aborted.
			)";
			
			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode), 1);
		}
	}
}