#include "../Shared.h"

namespace UnitTests
{
	namespace ArithmeticOperations
	{
		TEST(PerfomanceArithmetic, Add)
		{
			const size_t n = 1000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0 * 8899999999.832).Add.print;
			Add = ([1] *  
			)" << n << R"(
			).less -> ([2] * [2]).add * (([1] * 1).add * [2]).Add, [1];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
		TEST(PerfomanceArithmetic, Sub)
		{
			const size_t n = 1000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0 * 8899999999.832).Sub.print;
			Sub = ([1] *  
			)" << n << R"(
			).less -> ([2] * 5213637881.832).sub * (([1] * 1).add * [2]).Sub, [1];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
		TEST(PerfomanceArithmetic, Mul)
		{
			const size_t n = 1000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0 * 88999999.832).Mul.print;
			Mul = ([1] * 
			)" << n << R"(
			).less -> ([2] * [2]).mul * (([1] * 1).add * [2]).Mul, [1];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
		TEST(PerfomanceArithmetic, Div)
		{
			const size_t n = 1000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0 * 88999999.832).Div.print;
			Div = ([1] * 
			)" << n << R"(
			).less -> ([2] * 321989.32).div * (([1] * 1).add * [2]).Div, [1];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
		TEST(PerfomanceArithmetic, Mod)
		{
			const size_t n = 1000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = (0 * 88999999).Mod.print;
			Mod = ([1] * 
			)" << n << R"(
			).less -> ([2] * 321989).mod * (([1] * 1).add * [2]).Mod, [1];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}
	}
}