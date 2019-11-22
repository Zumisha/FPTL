#include <iostream>
#include <limits>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "jemalloc/jemalloc.h"

#include "../Parser/Support.h"
#include "FSchemeGenerator.h"
#include "Run.h"
#include "IntForm/Generator.h"
#include "IntForm/InternalForm.h"
#include "Parser/AST.h"
#include "Context.h"

#define BUILD_DATE __DATE__ " " __TIME__

namespace po = boost::program_options;

namespace FPTL {
namespace Parser {

void run(std::vector<std::string> &inputTuple, std::string &programPath, po::variables_map & vm)
{
	boost::timer::cpu_timer timer;

	std::ifstream programFile(programPath);
	if (!programFile.good())
	{
		std::cout << "Unable to open file : " << programPath << "\n";
		return;
	}
	std::string programStr;
	std::copy(std::istreambuf_iterator<char>(programFile), std::istreambuf_iterator<char>(), std::back_inserter(programStr));
	programFile.close();

	Support support;
	ASTNode * astRoot = support.getInternalForm(inputTuple, programStr);
	support.getErrorList(std::cout);

	// Генерируем внутренне представление.
	if (astRoot)
	{
		const bool info = vm["info"].as<bool>();
		const bool time = vm["time"].as<bool>();
		const size_t numCores = vm["num-cores"].as<size_t>();
		const bool Proactive = vm["proactive"].as<bool>() && (numCores != 1);
		Utils::FormatedOutput fo = Utils::FormatedOutput(vm["ansi"].as<bool>());

		if (info)
		{
			std::cout << "No syntax errors found.\n";
			std::cout << "Running program: " << programPath << " on " << numCores << " work threads...\n\n";
			if (!Proactive) std::cout << "Proactive calculations " << fo.Underlined("disabled") << ".\n\n";
		}

		Runtime::FSchemeGenerator schemeGenerator(astRoot);
		const std::unique_ptr<Runtime::FunctionalProgram> internalForm(Runtime::Generator::generate(schemeGenerator.getProgram(), Proactive));
		Runtime::IFExecutionContext ctx(internalForm->main().get());
		const auto interpTime = timer.elapsed();
		if (time) std::cout << "Interpretation time: " << boost::timer::format(interpTime, 3, "%ws\n");
		timer.resume();

		Runtime::GcConfig gcConfig;
		gcConfig.setEnabled(!vm["disable-gc"].as<bool>());
		gcConfig.setVerbose(vm["verbose-gc"].as<bool>());
		gcConfig.setYoungGenSize(vm["young-gen"].as<size_t>() * 1024 * 1024);
		gcConfig.setOldGenSize(vm["old-gen"].as<size_t>() * 1024 * 1024);
		gcConfig.setOldGenThreshold(vm["old-gen-ratio"].as<double>());

		Runtime::EvalConfig evalConfig;
		evalConfig.SetNumCores(numCores);
		evalConfig.SetInfo(vm["info"].as<bool>());
		evalConfig.SetProactive(Proactive);
		evalConfig.SetOutput(fo);

		Runtime::SchemeEvaluator evaluator;
		evaluator.setGcConfig(gcConfig);
		evaluator.setEvalConfig(evalConfig);

		evaluator.run(ctx);
		const auto evalTime = timer.elapsed();
		if (time) std::cout << "\n\nEvaluation time: " << boost::timer::format(evalTime, 3, "%ws\n");
	}

	delete astRoot;
}

}}

void * operator new (const std::size_t count)
{
	return ::je_malloc(count);
}

void * operator new[](const std::size_t count)
{
	return ::je_malloc(count);
}

void operator delete(void * ptr)
{
	::je_free(ptr);
}

void operator delete[](void * ptr)
{
	::je_free(ptr);
}

bool optionsVerification(po::variables_map &vm, Utils::FormatedOutput fo)
{
	bool noErrors = true;
	if (vm["num-cores"].as<size_t>() <= 0)
	{
		std::cout << "Number of work threads " << fo.Bold(fo.Red("must be positive integer!")) << "\n\n";
		noErrors = false;
	}
	if (vm["young-gen"].as<size_t>() <= 0)
	{
		std::cout << "Young generation size " << fo.Bold(fo.Red("must be positive integer!")) << "\n\n";
		noErrors = false;
	}
	if (vm["old-gen"].as<size_t>() <= 0)
	{
		std::cout << "Old generation size " << fo.Bold(fo.Red("must be positive integer!")) << "\n\n";
		noErrors = false;
	}
	if (vm["old-gen-ratio"].as<double>() <= 0 || vm["old-gen-ratio"].as<double>() > 1)
	{
		std::cout << "Old gen usage ratio " << fo.Bold(fo.Red("must be in the interval (0, 1]!")) << "\n\n";
		noErrors = false;
	}
	return noErrors;
}

bool infoOptions(po::variables_map &vm, po::options_description desc, Utils::FormatedOutput fo)
{
	bool options = false;
	if (vm.count("version"))
	{
		std::cout << "Version of the interpreter from " << fo.Bold(fo.Green(BUILD_DATE)) << ".\n\n";
		options = false;
	}
	if (vm.count("help"))
	{
		std::cout << desc << "\n";
		options = true;
	}
	return options;
}

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "ru-ru");
	std::cout.precision(std::numeric_limits<double>::max_digits10);

 	std::string programFile;
	std::vector<std::string> inputTuple;

	po::positional_options_description posOpt;
	posOpt.add("source-file", 1);
	posOpt.add("input-tuple", -1);

	po::options_description desc("Available options:");
	desc.add_options()
		("help,h", "Provides information about startup options.")
		("version,v", "Displays the date and time of the interpreter build.")
		("source-file,s", po::value<std::string>(&programFile)->required(), "Path to FPTL program file.")
		("num-cores,n", po::value<size_t>()->default_value(1), "Number of work threads.")
		("input-tuple,in", po::value<std::vector<std::string>>(&inputTuple)->multitoken(), "Input variables.")
		("time,t", po::bool_switch(), "Displays interpretation and evaluation times.")
		("info,i", po::bool_switch(), "Displays information about the interpretation and evaluation processes.")
		("proactive", po::bool_switch(), "Enable proactive calculations.")
		("ansi", po::bool_switch(), "Allow ANSI text formatting.")
		("disable-gc", po::bool_switch(), "Disable garbage collector.")
		("verbose-gc", po::bool_switch(), "Displays information about the work of the garbage collector.")
		("young-gen", po::value<size_t>()->default_value(20), "Young generation size in MiB.")
		("old-gen", po::value<size_t>()->default_value(100), "Old generation size in MiB.")
		("old-gen-ratio", po::value<double>()->default_value(0.75), "Old gen usage ratio to start full GC.");

	po::variables_map vm;
	try
	{
		po::store(po::command_line_parser(argc, argv).options(desc).positional(posOpt).run(), vm);
		const Utils::FormatedOutput fo = Utils::FormatedOutput(vm["ansi"].as<bool>());
		if (!optionsVerification(vm, fo) || infoOptions(vm, desc, fo)) return 1;
		po::notify(vm);
	}
	catch (std::exception & e)
	{
		std::cout << "Error: " << e.what() << std::endl
			<< "\nUse --help or -h to display all available options." << std::endl;
		return 1;
	}
	catch (...) // SEH not catch
	{
		std::cout << "Congratulations, you found the entrance to Narnia!" << std::endl
			<< "(Not std::exception error.)" << std::endl;
		return 1;
	}

	try
	{
		FPTL::Parser::run(inputTuple, programFile, vm);
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