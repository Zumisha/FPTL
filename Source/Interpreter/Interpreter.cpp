#include <string> 
#include <vector>
#include <iostream>
#include <fstream>

#include <boost/timer/timer.hpp>

#include "Interpreter.h"
#include "Parser/CommandLineParser.h"
#include "Parser/AST.h"
#include "Parser/Support.h"
#include "FScheme/FSchemeGenerator.h"
#include "InternalForm/Generator.h"
#include "InternalForm/InternalForm.h"
#include "GC/GarbageCollector.h"
#include "Evaluator/Context.h"
#include "Evaluator/Run.h"

namespace FPTL 
{
	namespace Runtime 
	{
		int Interpreter::Eval(const int argc, const char ** argv) const
		{
			try
			{
				boost::timer::cpu_timer timer;

				auto CLParser = Parser::CommandLineParser();

				const auto parseResult = CLParser.Parse(argc, argv);
				if (parseResult == -1) return 0;
				if (parseResult != 0) return parseResult;

				const Utils::FormattedOutput fo = CLParser.GetFormattedOutput();
				const std::string programPath = CLParser.GetProgramPath();
				const std::vector<std::string> inputTuple = CLParser.GetInputTuple();

				std::ifstream programFile(programPath);
				if (!programFile.good())
				{
					std::cout << "Unable to open file : " << programPath << "\n";
					return 1;
				}
				std::string programStr;
				std::copy(std::istreambuf_iterator<char>(programFile), std::istreambuf_iterator<char>(), std::back_inserter(programStr));
				programFile.close();

				Parser::Support support;
				Parser::ASTNode * astRoot = support.getInternalForm(inputTuple, programStr);

				support.getErrorList(std::cout);
				if (support.WasErrors() || !astRoot) return 1;

				const bool showInfo = CLParser.GetShowInfo();
				const bool showTime = CLParser.GetShowTime();
				const size_t numCores = CLParser.GetCoresNum();
				const bool proactive = CLParser.GetAllowProactive() && (numCores != 1);

				if (showInfo)
				{
					std::cout << "No syntax errors found.\n";
					std::cout << "Running program: " << programPath << " on " << numCores << " work threads...\n\n";
					if (!proactive) std::cout << "Proactive calculations " << fo.Underlined("disabled") << ".\n\n";
				}

				FSchemeGenerator schemeGenerator(astRoot);
				const std::unique_ptr<FunctionalProgram> internalForm(Generator::generate(schemeGenerator.getProgram(), proactive));
				IFExecutionContext ctx(internalForm->main().get());
				const auto interpTime = timer.elapsed();
				if (showTime) std::cout << "Interpretation time: " << boost::timer::format(interpTime, 3, "%ws\n");
				timer.resume();

				const GcConfig gcConfig = CLParser.GetGcConfig();

				EvalConfig evalConfig;
				evalConfig.SetNumCores(numCores);
				evalConfig.SetInfo(showInfo);
				evalConfig.SetProactive(proactive);
				evalConfig.SetOutput(fo);

				SchemeEvaluator evaluator;
				evaluator.setGcConfig(gcConfig);
				evaluator.setEvalConfig(evalConfig);

				evaluator.run(ctx);
				const auto evalTime = timer.elapsed();
				if (showTime) std::cout << "\n\nEvaluation time: " << boost::timer::format(evalTime, 3, "%ws\n");

				delete astRoot;
			}
			catch (std::exception & e)
			{
				std::cout << "Error: " << e.what() << std::endl
					<< "Execution aborted." << std::endl;
				return 1;
			}
			catch (...) // SEH not catch
			{
				std::cout << "Congratulations, you found the entrance to Narnia!" << std::endl
					<< "(Not std::exception error.)" << std::endl
					<< "Execution aborted." << std::endl;
				return 1;
			}

			return 0;
		}
	}
}
