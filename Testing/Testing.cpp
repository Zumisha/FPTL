#include "pch.h"

#include "gtest/gtest.h"

#include "../Source/Interpreter/Interpreter.h"

namespace UnitTests
{
	namespace Generalized
	{
		TEST(Generalized, Integrate)
		{
			setlocale(LC_ALL, "ru-ru");
			std::cout.precision(std::numeric_limits<double>::max_digits10);

			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\Parallel_Integral.fptl)",
				"-n", "8", "8", "3"};
			const std::string expected = "0.021191";

			const size_t argc = input.size();
			const char** argv = new const char*[argc];

			for (size_t i = 0; i < argc; ++i)
				argv[i] = input[i].c_str();

			testing::internal::CaptureStdout();
			FPTL::Runtime::Interpreter interpreter;
			const auto retVal = interpreter.Eval(argc, argv);
			EXPECT_EQ(retVal, 0);

			delete[] argv;

			const std::string output = testing::internal::GetCapturedStdout();
			const auto compare = output.find(expected);
			EXPECT_LT(compare, static_cast<size_t>(-1));

			std::cout << std::endl << output;
		}

		TEST(Generalized, Sort)
		{
			setlocale(LC_ALL, "ru-ru");
			std::cout.precision(std::numeric_limits<double>::max_digits10);
			testing::internal::CaptureStdout();

			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\MergeSort\MergeSort.fptl)",
				"-n", "8", "1000000", "8"};
			const std::string expected = "3.8710544663636201e-07";

			const size_t argc = input.size();
			const char** argv = new const char*[argc];
			for (size_t i = 0; i < argc; ++i)
				argv[i] = input[i].c_str();

			FPTL::Runtime::Interpreter interpreter;
			const auto retVal = interpreter.Eval(argc, argv);
			
			delete[] argv;

			const std::string output = testing::internal::GetCapturedStdout();			

			const auto compare = output.find(expected);
			EXPECT_EQ(retVal, 0);
			EXPECT_LT(compare, static_cast<size_t>(-1));

			std::cout << std::endl << output;
		}

		TEST(Generalized, Matrix_Mul)
		{
			setlocale(LC_ALL, "ru-ru");
			std::cout.precision(std::numeric_limits<double>::max_digits10);

			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\MatrixMul\MatrixMul.fptl)",
				"-n", "8", "100", "8" };
			const std::string expected = "22.146432180142053";

			const size_t argc = input.size();
			const char** argv = new const char*[argc];

			for (size_t i = 0; i < argc; ++i)
				argv[i] = input[i].c_str();

			testing::internal::CaptureStdout();
			FPTL::Runtime::Interpreter interpreter;
			const auto retVal = interpreter.Eval(argc, argv);
			EXPECT_EQ(retVal, 0);

			delete[] argv;

			const std::string output = testing::internal::GetCapturedStdout();
			const auto compare = output.find(expected);
			EXPECT_LT(compare, static_cast<size_t>(-1));

			std::cout << std::endl << output;
		}

		TEST(Generalized, ADT_List) 
		{
			setlocale(LC_ALL, "ru-ru");
			std::cout.precision(std::numeric_limits<double>::max_digits10);

			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)",
				R"(..\..\Tests\Generalized\ADT_List_Concatenate_EqTransform.fptl)",
				"-n", "8" };
			const std::string expected = "(1*(2*(3*(4*c_nil).c_cons).c_cons).c_cons).c_cons";

			const size_t argc = input.size();
			const char** argv = new const char*[argc];

			for (size_t i = 0; i < argc; ++i)
				argv[i] = input[i].c_str();

			FPTL::Runtime::Interpreter interpreter;
			testing::internal::CaptureStdout();
			const auto retVal = interpreter.Eval(argc, argv);
			EXPECT_EQ(retVal, 0);

			delete[] argv;

			const std::string output = testing::internal::GetCapturedStdout();
			const auto compare = output.find(expected);
			EXPECT_LT(compare, static_cast<size_t>(-1));

			std::cout << std::endl << output;
		}
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
