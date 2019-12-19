#include "../Shared.h"

namespace UnitTests
{
	namespace Arrays
	{
		TEST(PerformanceArrays, ArrayCreate)
		{
			const size_t n = 540000000;

			std::stringstream innerCode;
			innerCode << "@ = ((" << n << " * 1).arrayCreate * " << n - 1 << ").arrayGet.print;";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}

		TEST(PerformanceArrays, ArrayGet)
		{
			const size_t n = 10000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = ((1 * 0).arrayCreate * 0).Get.print;
			Get = ([2] * 
			)" << n << R"(
			).less -> ([1] * 0).arrayGet * ([1] * ([2] * 1).add).Get, [2];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}

		TEST(PerformanceArrays, ArraySet)
		{
			const size_t n = 10000;

			std::stringstream innerCode;
			innerCode << R"(
			@ = ((1 * 0).arrayCreate * 0).Set.print;
			Set = ([2] * 
			)" << n << R"(
			).less -> (([1] * 0 * [2]).arraySet * ([2] * 1).add).Set, [2];
			)";

			const std::string expected = std::to_string(n);

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode.str()));
		}

		TEST(PerformanceArrays, ArraysCat)
		{
			const std::string innerCode = R"(
			@ = (	(140000000 * 1).arrayCreate * 
					(400000000 * 2).arrayCreate
				).arrayCat.(([1] * 0).arrayGet * ([1] * 140000000).arrayGet).print;
			)";

			const std::string expected = "1 * 2";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(PerformanceArrays, ArrayFromFile)
		{
			const std::string innerCode = R"(
			@ = (	(1000000 * 0.0).arrayCreate * 
					"../../Tests/Generalized/MergeSort/1000000.txt"
				).arrayFromFile.([1] * 0).arrayGet.print;
			)";

			const std::string expected = "0.8359131833708765";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}