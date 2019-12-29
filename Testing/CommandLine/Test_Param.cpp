#include "../Shared.h"

namespace UnitTests
{
	namespace Test_param
	{
		const static std::string innerCode = R"(@ = id.print.(1 * 2.0 * true * "hello" * (2 * 0).arrayCreate * (true*(true*c_nil).c_cons).c_cons).([1]*[2]*[3]*[4]*[5]*[6]).print;)";
		
		TEST(TestParam, OnlyFile)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, OnlyHelp)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-h"
			};
				
			const std::string expected = R"(
				-h [ --help ]               Provides information about startup options.
				-v [ --version ]            Displays the date and time of the interpreter
											build.
				-s [ --source-file ] arg    Path to FPTL program file.
				-n [ --num-cores ] arg (=1) Number of work threads.
				--input-tuple arg           Input variables.
				-t [ --time ]               Displays interpretation and evaluation times.
				-i [ --info ]               Displays information about the interpretation and
											evaluation processes.
				--proactive                 Enable proactive calculations.
				--ansi                      Allow ANSI text formatting.
				--disable-gc                Disable garbage collector.
				--Verbose-gc                Displays information about the work of the
											garbage collector.
				--young-gen arg (=20)       Young generation size in MiB.
				--old-gen arg (=100)        Old generation size in MiB.
				--old-gen-ratio arg (=0,75) Old gen usage ratio to start full GC.
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, OnlyHelp2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"--help"
			};
				
			const std::string expected = R"(
				-h [ --help ]               Provides information about startup options.
				-v [ --version ]            Displays the date and time of the interpreter
											build.
				-s [ --source-file ] arg    Path to FPTL program file.
				-n [ --num-cores ] arg (=1) Number of work threads.
				--input-tuple arg           Input variables.
				-t [ --time ]               Displays interpretation and evaluation times.
				-i [ --info ]               Displays information about the interpretation and
											evaluation processes.
				--proactive                 Enable proactive calculations.
				--ansi                      Allow ANSI text formatting.
				--disable-gc                Disable garbage collector.
				--Verbose-gc                Displays information about the work of the
											garbage collector.
				--young-gen arg (=20)       Young generation size in MiB.
				--old-gen arg (=100)        Old generation size in MiB.
				--old-gen-ratio arg (=0,75) Old gen usage ratio to start full GC.
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Version)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-v"
			};
				
			const std::string expected = R"(
				Version of the interpreter from Dec 15 2019 05:39:51.

				1 * 2 * true * hello * [0, 0]
			)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Version2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--version"
			};
				
			const std::string expected = R"(
				Version of the interpreter from Dec 15 2019 05:39:51.

				1 * 2 * true * hello * [0, 0]
			)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Info)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-i"
			};
				
			const std::string expected = R"(
				No syntax errors found.
				Running program: Test.fptl on 1 work threads...

				Proactive calculations disabled.
	
				1 * 2 * true * hello * [0, 0]
				Thread ID = 6684. Jobs created: 1, completed: 1, stolen: 0.
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Info2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--info"
			};
				
			const std::string expected = R"(
				No syntax errors found.
				Running program: Test.fptl on 1 work threads...

				Proactive calculations disabled.
	
				1 * 2 * true * hello * [0, 0]
				Thread ID = 6684. Jobs created: 1, completed: 1, stolen: 0.
			)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, SourceFile)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-s",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, SourceFile2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"--source-file",
				R"(Test.fptl)"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, NumCores)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-n",
				"2"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, NumCores2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--num-cores",
				"2"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, InputTuple)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--input-tuple",
				R"(1*2*3)"
			};
				
			const std::string expected = R"(1 * 2 * 31 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Time)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-t"
			};
				
			const std::string expected = R"(
				Interpretation time: 0.001s
				1 * 2 * true * hello * [0, 0]

				Evaluation time: 0.034s

			)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, Time2)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--time"
			};
				
			const std::string expected = R"(
				Interpretation time: 0.001s
				1 * 2 * true * hello * [0, 0]

				Evaluation time: 0.034s

			)";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, ANSI)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--ansi"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, DisableGC)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--disable-gc"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, VerboseGC)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"--Verbose-gc"
			};
				
			const std::string expected = R"(1 * 2 * true * "hello" * [0, 0])";
			
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, HelpWithNum)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-h",
				R"(Test.fptl)",
				"-n",
				"2"
			};
				
			const std::string expected = R"(
				-h [ --help ]               Provides information about startup options.
				-v [ --version ]            Displays the date and time of the interpreter
											build.
				-s [ --source-file ] arg    Path to FPTL program file.
				-n [ --num-cores ] arg (=1) Number of work threads.
				--input-tuple arg           Input variables.
				-t [ --time ]               Displays interpretation and evaluation times.
				-i [ --info ]               Displays information about the interpretation and
											evaluation processes.
				--proactive                 Enable proactive calculations.
				--ansi                      Allow ANSI text formatting.
				--disable-gc                Disable garbage collector.
				--Verbose-gc                Displays information about the work of the
											garbage collector.
				--young-gen arg (=20)       Young generation size in MiB.
				--old-gen arg (=100)        Old generation size in MiB.
				--old-gen-ratio arg (=0,75) Old gen usage ratio to start full GC.
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, HelpWithInput)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				"-h",
				R"(Test.fptl)",
				R"(--input-tuple)",
				R"(1*2*3)"
			};
				
			const std::string expected = R"(
				-h [ --help ]               Provides information about startup options.
				-v [ --version ]            Displays the date and time of the interpreter
											build.
				-s [ --source-file ] arg    Path to FPTL program file.
				-n [ --num-cores ] arg (=1) Number of work threads.
				--input-tuple arg           Input variables.
				-t [ --time ]               Displays interpretation and evaluation times.
				-i [ --info ]               Displays information about the interpretation and
											evaluation processes.
				--proactive                 Enable proactive calculations.
				--ansi                      Allow ANSI text formatting.
				--disable-gc                Disable garbage collector.
				--Verbose-gc                Displays information about the work of the
											garbage collector.
				--young-gen arg (=20)       Young generation size in MiB.
				--old-gen arg (=100)        Old generation size in MiB.
				--old-gen-ratio arg (=0,75) Old gen usage ratio to start full GC.
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, NumCoresInputTime)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"-n",
				"2",
				R"(--input-tuple)",
				R"(1*2*3)",
				"-t"
			};
				
			const std::string expected = R"(
				Interpretation time: 0.000s
				1 * 2 * 31 * 2 * true * hello * [0, 0]

				Evaluation time: 0.031s
			)";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}

		TEST(TestParam, DoubleInput)
		{
			const static std::vector<std::string> testInput = {
				R"(..\x64\Release\FPTL.exe)",
				R"(Test.fptl)",
				"1",
				"2",
				R"(--input-tuple)",
				R"(1*2)"
			};
				
			const std::string expected = R"(1 * 2 * 1 * 21 * 2 * true * "hello" * [0, 0])";
			GeneralizedTest(testInput, expected, MakeTestProgram(innerCode));
		}
	}
}