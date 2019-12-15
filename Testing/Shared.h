#pragma once

#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../Source/Interpreter/Interpreter.h"
#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "Parser/Support.h"
#include "Evaluator/Context.h"
#include "DataTypes/Ops/ArrayOps.h"

namespace UnitTests
{
	static std::string invalidOperation(const std::string& typeName, const std::string& funcName)
	{
		std::stringstream ss;
		ss << FPTL::Runtime::BaseOps::invalidOpsMsg << typeName << ": " << funcName;
		return ss.str();
	}

	const static std::string ListDefinition = "Data List['t] {List = c_nil ++ 't * List['t].c_cons;} ";

	std::string static MakeTestProgram(const std::string& innerCode)
	{
		const std::string begin = "Scheme Test {";
		const std::string end = "} Application %Test";
		return begin + innerCode + end;
	}

	const static std::vector<std::string> standardInput = {
		R"(..\x64\Release\FPTL.exe)",
		R"(Test.fptl)",
		"-n",
		"8" };

	void static GeneralizedTest(const std::vector<std::string>& input, const std::string& expected, const std::string& programText = "", const int expectedCode = 0)
	{
		const size_t argc = input.size();
		const auto** argv = new const char*[argc];
		for (size_t i = 0; i < argc; ++i)
			argv[i] = input[i].c_str();

		testing::internal::CaptureStdout();
		testing::internal::CaptureStderr();

		FPTL::Runtime::Interpreter interpreter;
		int retVal = interpreter.Eval(static_cast<int>(argc), argv, programText);

		std::string output = testing::internal::GetCapturedStderr() + testing::internal::GetCapturedStdout();

		delete[] argv;

		EXPECT_EQ(retVal, expectedCode);

		const auto compare = output.find(expected);

		EXPECT_LT(compare, static_cast<size_t>(-1));

		std::cout << std::endl << "Expected: " << std::endl << expected << std::endl;

		std::cout << std::endl << "Output: " << std::endl << output << std::endl;
	}
}
