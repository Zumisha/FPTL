#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../Source/Interpreter/Interpreter.h"

namespace UnitTests
{
	int main(int argc, char **argv) {
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
}
