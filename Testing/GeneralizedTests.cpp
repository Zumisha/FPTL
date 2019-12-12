#include "Shared.h"

namespace UnitTests
{
	namespace Generalized
	{
		TEST(Generalized, ADT_List)
		{
			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\ADT_List_Concatenate_EqTransform.fptl)",
				"-n",
				"8" };

			const std::string expected = "(1*(2*(3*(4*c_nil).c_cons).c_cons).c_cons).c_cons";

			GeneralizedTest(input, expected);
		}

		TEST(Generalized, Integrate)
		{
			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\Parallel_Integral.fptl)",
				"-n", 
				"8",
				"8",
				"3"};

			const std::string expected = "0.021191";

			GeneralizedTest(input, expected);
		}

		TEST(Generalized, Sort)
		{
			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\MergeSort\MergeSort.fptl)",
				"-n",
				"8",
				"1000000",
				"8"};

			const std::string expected = "3.8710544663636201e-07";

			GeneralizedTest(input, expected);
		}

		TEST(Generalized, Matrix_Mul)
		{
			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\MatrixMul\MatrixMul.fptl)",
				"-n",
				"8",
				"100",
				"8" };

			const std::string expected = "22.146432180142053";

			GeneralizedTest(input, expected);
		}
	}
}
