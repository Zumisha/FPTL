#include "../Shared.h"
#include <fstream>

namespace UnitTests
{
	namespace Arrays
	{
		TEST(ArrayFromFile, GoodFile)
		{
			const std::string innerCode = R"(
			@ = (	(100 * 0.0).arrayCreate * 
					"../../Tests/Generalized/MergeSort/100.txt"
				).arrayFromFile.print;
			)";

			std::ifstream fStream("../../Tests/Generalized/MergeSort/100.txt");
			std::stringstream expected;
			expected.precision(std::numeric_limits<double>::max_digits10);

			if (fStream.is_open())
			{
				expected << "[";
				double val;
				fStream >> val;
				expected << val;
				while (fStream >> val)
				{
					expected << ", " << val;
				}
				expected << "]";
			}

			GeneralizedTest(standardInput, expected.str(), MakeTestProgram(innerCode));
		}

		TEST(ArrayFromFile, BadFile)
		{
			const std::string innerCode = R"(
			@ = (	(100 * 0).arrayCreate * 
					"../../Tests/Generalized/MergeSort/MergeSort.fptl"
				).arrayFromFile.print;
			)";

			const std::string expected = R"(undefined * characters extracted could not be interpreted as a valid value of the appropriate type)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}

		TEST(ArrayFromFile, NotExist)
		{
			const std::string innerCode = R"(
			@ = (	(100 * 0.0).arrayCreate * 
					"Tests"
				).arrayFromFile.print;
			)";

			const std::string expected = R"(undefined * No such file or directory)";

			GeneralizedTest(standardInput, expected, MakeTestProgram(innerCode));
		}
	}
}
