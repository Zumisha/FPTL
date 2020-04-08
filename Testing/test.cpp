#include "gtest/gtest.h"

#include "Interpreter/Interpreter.h"

namespace UnitTests
{
	namespace Generalized
	{
		TEST(Generalized, Integrate) {
			const std::vector<std::string> input = {
				R"(..\x64\Release\FPTL.exe)", 
				R"(..\x64\Release\Test.txt)", 
				"-n", "8", "-i", "-t" };
			const std::string expected = "0.021191";

			const size_t argc = input.size();
			const char** argv = new const char*[argc];

			for (size_t i = 0; i < argc; ++i)
				argv[i] = input[i].c_str();

			FPTL::Runtime::Interpreter interpreter;
			const auto retVal = interpreter.Eval(argc, argv);
			EXPECT_EQ(retVal, 0);

			delete[] argv;

			testing::internal::CaptureStdout();
			const std::string output = testing::internal::GetCapturedStdout();
			const auto compare = output.find(expected);
			EXPECT_GT(compare, static_cast<size_t>(-1));
		}		
	}
}

/*int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/
