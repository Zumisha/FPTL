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
#include "Parser/ASTSerializer.h"
#include "Macros.h"
#include "FScheme/NewFSchemeGenerator.h"

namespace FPTL
{
	namespace Runtime
	{
		std::map<const std::string, const TypedFunction> mFunctions;
		
		int Interpreter::Eval(const int argc, const char ** argv, const std::string& programText) const
		{
			//setlocale(LC_ALL, "ru-ru");
			std::cout.precision(std::numeric_limits<double>::max_digits10); 
			Parser::ASTNode * astRoot = nullptr;
#if !disableExceptionHandling
			try
			{
#endif
				boost::timer::cpu_timer timer;

				auto CLParser = Parser::CommandLineParser();

				const auto parseResult = CLParser.Parse(argc, argv);
				if (parseResult == -1) return 0;
				if (parseResult != 0) return parseResult;

				const Utils::FormattedOutput fo = CLParser.GetFormattedOutput();
				const std::string programPath = CLParser.GetProgramPath();
				std::vector<std::string> inputTuple = CLParser.GetInputTuple();

				std::string programStr;
				if (programText.empty())
				{
					std::ifstream programFile(programPath);
					if (!programFile.good())
					{
						std::cout << "Unable to open file : " << programPath << "\n";
						return 1;
					}
					std::copy(std::istreambuf_iterator<char>(programFile), std::istreambuf_iterator<char>(), std::back_inserter(programStr));
					programFile.close();
				}
				else
				{
					programStr = programText;
				}

				Parser::Support support;
				astRoot = support.getAST(inputTuple, programStr);

				support.getErrorList(std::cout);
				if (support.WasErrors() || !astRoot) return 1;

				if (CLParser.GetSaveAST())
				{
					Parser::ASTSerializer serializer;
					serializer.serialize(astRoot);
				}

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
				//NewFSchemeGenerator schemeGenerator(astRoot);
				const auto FScheme = schemeGenerator.getProgram();

				if (CLParser.GetSaveScheme())
				{
					FSchemeSerializer serializer;
					serializer.serialize(FScheme);
				}

				const std::unique_ptr<FunctionalProgram> internalForm(Generator::generate(FScheme, proactive));
				IFExecutionContext ctx(internalForm->main().get());

				const auto interpTime = timer.elapsed();
				if (showTime) std::cout << "Interpretation time: " << format(interpTime, 3, "%ws\n") << std::endl;
				timer.resume();

				const GcConfig gcConfig = CLParser.GetGcConfig();

				EvalConfig evalConfig;
				evalConfig.SetNumCores(numCores);
				evalConfig.SetInfo(showInfo);
				evalConfig.SetTime(showTime);
				evalConfig.SetProactive(proactive);
				evalConfig.SetOutput(fo);

				SchemeEvaluator evaluator;
				evaluator.setGcConfig(gcConfig);
				evaluator.setEvalConfig(evalConfig);

				evaluator.run(ctx);
				const auto evalTime = timer.elapsed();
				if (showTime) std::cout << "\n\nEvaluation time: " << boost::timer::format(evalTime, 3, "%ws\n");

				delete astRoot;
				if (evaluator.WasErrors()) return 1;
#if !disableExceptionHandling
			}
			catch (std::exception& e)
			{
				std::cerr << "Error: " << e.what() << std::endl
					<< "Execution aborted." << std::endl;
				delete astRoot;
				return 1;
			}
			catch (...)
			{
				std::cerr << "Congratulations, you found the entrance to Narnia!" << std::endl
					<< "(Not std::exception error.)" << std::endl
					<< "Execution aborted." << std::endl;
				delete astRoot;
				return 1;
			}
#endif

			return 0;
		}
	}
}
