#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

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

	void * operator new  (std::size_t count)
	{
		return ::je_malloc(count);
	}

	void * operator new[](std::size_t count)
	{
		return ::je_malloc(count);
	}

		void operator delete  (void * ptr)
	{
		::je_free(ptr);
	}

	void operator delete[](void * ptr)
	{
		::je_free(ptr);
	}

void run(const char * programPath, po::variables_map & vm)
{
	std::ifstream inpFile(programPath);

	if (!inpFile.good())
	{
		std::cout << "Unable to open file : " << programPath << "\n";
		return;
	}

	std::string inputStr;
	std::copy(std::istreambuf_iterator<char>(inpFile), std::istreambuf_iterator<char>(), std::back_inserter(inputStr));

	Support support;
	ASTNode * astRoot = support.getInternalForm(inputStr);
	support.getErrorList(std::cout);

	// Генерируем внутренне представление.
	if (astRoot)
	{
		std::cout << "No syntax errors found.\n";

		const size_t numCores = vm["num-cores"].as<size_t>();
		std::cout << "Running program: " << programPath << " on " << numCores << " work threads...\n\n";

		Runtime::FSchemeGenerator schemeGenerator(astRoot);

		Utils::FormatedOutput fo = Utils::FormatedOutput(vm["ansi"].as<bool>());

		const bool Proactive = vm["proactive"].as<bool>() && (numCores!=1);
		if (!Proactive)
			std::cout << "Proactive calculations " << fo.Underlined("disabled") << ".\n\n";

		const std::unique_ptr<Runtime::FunctionalProgram> internalForm(Runtime::Generator::generate(schemeGenerator.getProgram(), Proactive));

		Runtime::SchemeEvaluator evaluator;

		Runtime::GcConfig gcConfig;
		gcConfig.setEnabled(!vm["disable-gc"].as<bool>());
		gcConfig.setVerbose(vm["verbose-gc"].as<bool>());
		gcConfig.setYoungGenSize(vm["young-gen"].as<size_t>() * 1024 * 1024);
		gcConfig.setOldGenSize(vm["old-gen"].as<size_t>() * 1024 * 1024);
		gcConfig.setOldGenThreshold(vm["old-gen-ratio"].as<double>());
		evaluator.setGcConfig(gcConfig);

		Runtime::EvalConfig evalConfig;
		evalConfig.SetNumCores(numCores);
		evalConfig.SetProactive(Proactive);
		evalConfig.SetOutput(fo);
		evaluator.setEvalConfig(evalConfig);

		Runtime::IFExecutionContext ctx(internalForm->main().get());
		evaluator.run(ctx);
	}

	delete astRoot;
}

}}

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
	//setlocale(LC_ALL, "ru-ru");
	std::cout.precision(15);

 	std::string programFile;
	std::vector<std::string> inputTuple;

	po::positional_options_description posOpt;
	posOpt.add("source-file", 1);
	posOpt.add("input-tuple", 2);

	po::options_description desc("Available options:");
	desc.add_options()
		("help,h", "Provides information about startup options.")
		("version,v", "Displays the date and time of the interpreter build.")
		("source-file,s", po::value<std::string>(&programFile)->required(), "Path to FPTL program file.")
		("num-cores,n", po::value<size_t>()->default_value(1), "Number of work threads.")
		("input-tuple,in", po::value<std::vector<std::string>>(&inputTuple)->multitoken(), "Input variables.")
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
		FPTL::Parser::run(programFile.c_str(), vm);
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