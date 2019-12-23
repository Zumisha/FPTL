#include "../Shared.h"

namespace UnitTests
{
	namespace ADT
	{
		TEST(ADTTest, Bool)
		{
			std::string innerCode = "@ = ((true*(true*c_nil).c_cons).c_cons).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(true*(true*c_nil).c_cons).c_cons";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTTest, String)
		{
			std::string innerCode = "@ = ((\"My\"*(\"name\"*c_nil). c_cons).c_cons).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(My*(name*c_nil).c_cons).c_cons";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTTest, Double)
		{
			std::string innerCode = "@ = ((1.2*(2.2*c_nil).c_cons).c_cons).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(1.2*(2.2000000000000002*c_nil).c_cons).c_cons";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTTest, ccons2)
		{
			std::string innerCode = "@ = (((3*(4*c_nil).c_cons).c_cons.~c_cons).[2]).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(4*c_nil).c_cons";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTTest, ccons1)
		{
			std::string innerCode = "@ = (((3*(4*c_nil).c_cons).c_cons.~c_cons).[1]).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "3";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTTest, cnil)
		{
			std::string innerCode = "@ = (c_nil).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "c_nil";

			GeneralizedTest(standardInput, expected, innerCode);
		}
		TEST(ADTTest, undcnil)
		{
			std::string innerCode = "@ = ((3*(2*c_nil).c_cons).c_cons.~c_nil).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "undefined";

			GeneralizedTest(standardInput, expected, innerCode);
		}
		TEST(ADTTest, undccons)
		{
			std::string innerCode = "@ = ((3*(4*c_nil).c_cons).~c_cons).print;";
			innerCode = ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "undefined";

			GeneralizedTest(standardInput, expected, innerCode);
		}
		TEST(ADTTest, twoADT)
		{
			std::string innerCode = "@ = ((3.c_succ*(4.c_succ*c_nil).c_cons).c_cons).print;";
			innerCode = NatDefinition + ListDefinition + MakeTestProgram(innerCode);

			const std::string expected = "((3).c_succ*((4).c_succ*c_nil).c_cons).c_cons";

			GeneralizedTest(standardInput, expected, innerCode);
		}

	}
}