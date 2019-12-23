#include "../Shared.h"

namespace UnitTests
{
	namespace ADT
	{
		TEST(ADTDblParamTest, Int)
		{
			std::string innerCode = "@ = ((3*2).c_pair).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(3*2).c_pair";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, Bool)
		{
			std::string innerCode = "@ = ((true*false).c_pair).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(true*false).c_pair";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, String)
		{
			
			std::string innerCode = R"(@ = (("st"*"r").c_pair).print;)";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(st*r).c_pair";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, Double)
		{
			std::string innerCode = "@ = ((3.2*2.2).c_pair).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(3.2000000000000002*2.2000000000000002).c_pair";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, cpair1)
		{
			std::string innerCode = "@ = (((3*2).c_pair).~c_pair.[1]).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "3";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, cpair2)
		{
			std::string innerCode = "@ = (((3*2).c_pair).~c_pair.[2]).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "2";

			GeneralizedTest(standardInput, expected, innerCode);
		}

		TEST(ADTDblParamTest, undcpair)
		{
			std::string innerCode = "@ = (3.~c_pair.[1]).print;";
			innerCode = PairDefinition + MakeTestProgram(innerCode);

			const std::string expected = "undefined";

			GeneralizedTest(standardInput, expected, innerCode);
		}
		
		TEST(ADTDblParamTest, twoADT)
		{
			std::string innerCode = "@ = ((2*3.c_succ).c_pair).print;";
			innerCode = PairDefinition + NatDefinition + MakeTestProgram(innerCode);

			const std::string expected = "(2*(3).c_succ).c_pair";

			GeneralizedTest(standardInput, expected, innerCode);
		}

	}
}