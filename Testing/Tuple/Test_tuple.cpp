#include "../Shared.h"

namespace UnitTests
{
	namespace Test_tuple
	{
		TEST(TupleTest, OneToSix)
		{
			std::string innerCode = R"(@ = (1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * ((true*(true*c_nil).c_cons).c_cons)).([1]*[2]*[3]*[4]*[5]*[6]).print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);
			
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0] * (true*(true*c_nil).c_cons).c_cons)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		TEST(TupleTest, SixToOne)
		{
			std::string innerCode = R"(@ = (1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * ((true*(true*c_nil).c_cons).c_cons)).([-1]*[-2]*[-3]*[-4]*[-5]*[-6]).print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);
			
			const std::string expected = R"(true*(true*c_nil).c_cons).c_cons * [0, 0] * "hello" * true * 2 * 1)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TupleTest, TakeID)
		{
			std::string innerCode = R"(@ = (1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * ((true*(true*c_nil).c_cons).c_cons)).id.print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0] * (true*(true*c_nil).c_cons).c_cons)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		
		TEST(TupleTest, TakeEmptyID)
		{
			std::string innerCode = "@ = id.print;";
			innerCode = MakeTestProgram(innerCode);

			const std::string expected;

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		
		TEST(TupleTest, tupleLen)
		{
			std::string innerCode = R"(@ = (1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * ((true*(true*c_nil).c_cons).c_cons)).tupleLen.print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "6";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
		
		TEST(TupleTest, emptyTupleLen)
		{
			std::string innerCode = R"(@ = tupleLen.print;)";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "0";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}