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
		std::map<std::string, std::pair<TFunction, bool>> FunctionLibrary::mFunctions;
		
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

				support.printErrorList(std::cout);
				if (support.WasErrors() || !astRoot) return 1;

				if (CLParser.GetExportAST())
				{
					Parser::ASTSerializer serializer;
					serializer.serialize(astRoot);
				}

				auto evalConfig = CLParser.GetEvalConfig();

				if (evalConfig.printInfo)
				{
					std::cout << "No syntax errors found.\n";
					std::cout << "Running program: " << programPath << " on " << evalConfig.numCores << " work threads...\n\n";
					if (!evalConfig.proactiveEnabled) std::cout << "Proactive calculations " << evalConfig.output.Underlined("disabled") << ".\n\n";
				}

				FSchemeGenerator schemeGenerator(astRoot);
				//NewFSchemeGenerator schemeGenerator(astRoot);
				const auto FScheme = schemeGenerator.getProgram();

				if (CLParser.GetExportScheme())
				{
					FSchemeSerializer serializer;
					serializer.serialize(FScheme);
				}

				const std::unique_ptr<FunctionalProgram> internalForm(Generator::generate(FScheme, evalConfig));
				IFExecutionContext ctx(internalForm->main().get());

				const auto interpTime = timer.elapsed();
				if (evalConfig.printTime) std::cout << "Interpretation time: " << format(interpTime, 3, "%ws\n") << std::endl;
				timer.resume();

				const GcConfig gcConfig = CLParser.GetGcConfig();

				SchemeEvaluator evaluator;
				evaluator.setGcConfig(gcConfig);
				evaluator.setEvalConfig(evalConfig);

				evaluator.run(ctx);
				const auto evalTime = timer.elapsed();
				if (evalConfig.printTime) std::cout << "\n\nEvaluation time: " << boost::timer::format(evalTime, 3, "%ws\n");

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
