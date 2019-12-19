#include "../Shared.h"

namespace UnitTests
{
	namespace ADT
	{
		TEST(PerformanceADT, ADT)
		{
			const size_t n = 10000000;

			std::stringstream innerCode;
			innerCode << "@ = (" << n << ".CreateList.~c_cons.[1]).print; " << 
				"Fun CreateList {@ = (id * 0).equal -> c_nil, (1 * (id * 1).sub.CreateList).c_cons;}";

			const std::string expected = "1";

			GeneralizedTest(standardInput, expected, ListDefinition + MakeTestProgram(innerCode.str()));
		}
	}
}