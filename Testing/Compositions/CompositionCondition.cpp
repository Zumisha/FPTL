#include "../Shared.h"

namespace UnitTests
{
	namespace Composition
	{
		TEST(CondTest, Default)
		{
			std::string innerCode = "@ = (((0 * 1000000).Sum * 500000500001).less -> (1 * 1000000).Sum, (2 * 1000000).Sum).print;";
			innerCode = SumDefinition + MakeTestProgram(innerCode);

			const std::string expected = "500000500000";

			GeneralizedTest(standardInput, expected, innerCode);
		}

	}
}