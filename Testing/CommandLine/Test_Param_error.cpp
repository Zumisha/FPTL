#include "../Shared.h"

namespace UnitTests
{
	namespace Test_param_error
	{
		const static std::string innerCode = R"(@ = id.print.(1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * (true*(true*c_nil).c_cons).c_cons).([1]*[2]*[3]*[4]*[5]*[6]).print;)";
		
		TEST(TestParamError, NoParams)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)"
			};
				
			const std::string expected = R"(Error: the option '--source-file' is required but missing)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 1);
		}
		
		TEST(TestParamError, SourceFileAndPositionParams)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-s",
				R"(Test.fptl)",
				"1",
				"2"
			};
			//const std::string expected = R"(Error: option '--source-file' cannot be specified more than onceg)";
			// тут вроде ошибка о попытке 2-жды указать входной файл а должно отработать с входными 1 2
			const std::string expected = R"(1 * 21 * 2 * true * "hello" * [0, 0])";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 0);
		}
		TEST(TestParamError, SourceFileAndPositionParams2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"1",
				"2",
				"-s",
				R"(Test.fptl)"
			};
				
			// const std::string expected = R"(Error: option '--source-file' cannot be specified more than onceg)";
			// тут вроде ошибка о попытке 2-жды указать входной файл 
			// а должно отработать с входными 1 2
			const std::string expected = R"(1 * 21 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 0);
		}
		TEST(TestParamError, FileError)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"1",
				"2",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(Unable to open file : 1)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TestParamError, NumOfCoresError)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-n",
				"-1",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(Num of cores must be positive!)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TestParamError, EmptyInputTuple)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--input-tuple"
			};
				
			const std::string expected = R"(Error: the required argument for option '--input-tuple' is missing)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TestParamError, SourceFileError)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-s",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(Error: option '--source-file' cannot be specified more than once)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 1);
		}
		TEST(TestParamError, StringInPositionARGS)
		{
			//возможно накосячил с параметроми
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"--input-tuple",
				"3",
				"4",
				"-s",
				R"(Test.fptl)",
				R"("text")"

			};
			//тут вроде вылетает ошибка о двойном назначении файла
			//а должно отрабатывать
			const std::string expected = R"(3 * 4 * "text"1 * 2 * true * "hello" * [0, 0];)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode), 0);
		}
	}
}