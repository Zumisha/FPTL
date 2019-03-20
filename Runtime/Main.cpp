#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

#include "../Parser/Support.h"
#include "FSchemeGenerator.h"
#include "Run.h"
#include "IntForm/Generator.h"
#include "IntForm/InternalForm.h"
#include "IntForm/Context.h"

#include "jemalloc/jemalloc.h"

#define BUILD_DATE __DATE__ " " __TIME__

namespace po = boost::program_options;

namespace FPTL {
namespace Parser {

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

		size_t numCores = vm["num-cores"].as<int>();
		std::cout << "Running program: " << programPath << " on " << numCores << " work threads...\n\n";

		Runtime::FSchemeGenerator schemeGenerator;
		schemeGenerator.process(astRoot);

		Utils::FormatedOutput fo = Utils::FormatedOutput(vm["ansi"].as<bool>());

		const bool Proactive = vm["proactive"].as<bool>() && (numCores!=1);
		if (!Proactive)
			std::cout << "Proactive calculations " << fo.Underlined("disabled") << ".\n\n";

		std::unique_ptr<Runtime::FunctionalProgram> internalForm(Runtime::Generator::generate(schemeGenerator.getProgram(), Proactive));

		Runtime::SchemeEvaluator evaluator;

		Runtime::GcConfig gcConfig;
		gcConfig.setEnabled(!vm["disable-gc"].as<bool>());
		gcConfig.setVerbose(vm["verbose-gc"].as<bool>());
		gcConfig.setYoungGenSize(vm["young-gen"].as<int>() * 1024 * 1024);
		gcConfig.setOldGenSize(vm["old-gen"].as<int>() * 1024 * 1024);
		gcConfig.setOldGenThreashold(vm["old-gen-ratio"].as<double>());
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

bool optionsVerification(po::variables_map &vm, Utils::FormatedOutput fo)
{
	bool noErrors = true;
	if (vm["num-cores"].as<int>() <= 0)
	{
		std::cout << "Number of work threads " << fo.Bold(fo.Red("must be positive integer!")) << "\n\n";
		noErrors = false;
	}
	if (vm["young-gen"].as<int>() <= 0)
	{
		std::cout << "Young generation size " << fo.Bold(fo.Red("must be positive integer!")) << "\n\n";
		noErrors = false;
	}
	if (vm["old-gen"].as<int>() <= 0)
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
 	std::string programFile;

	po::positional_options_description posOpt;
	posOpt.add("source-file", 1);

	po::options_description desc("Avilable options:");
	desc.add_options()
		("help,h", "Provides information about startup options.")
		("version,v", "Displays the date and time of the interpreter build.")
		("source-file,s", po::value<std::string>(&programFile)->required(), "Path to FPTL program file.")
		("num-cores,n", po::value<int>()->default_value(1), "Number of work threads.")
		("proactive", po::bool_switch(), "Enable proactive calculations.")
		("ansi", po::bool_switch(), "Allow ANSI text formatting.")
		("disable-gc", po::bool_switch(), "Disable garbage collector.")
		("verbose-gc", po::bool_switch(), "Displays information about the work of the garbage collector.")
		("young-gen", po::value<int>()->default_value(20), "Young generation size in MiB.")
		("old-gen", po::value<int>()->default_value(100), "Old generation size in MiB.")
		("old-gen-ratio", po::value<double>()->default_value(0.75), "Old gen usage ratio to start full GC.")
		;

	try
	{
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).positional(posOpt).run(), vm);		
		Utils::FormatedOutput fo = Utils::FormatedOutput(vm["ansi"].as<bool>());
		if (!optionsVerification(vm, fo) | infoOptions(vm, desc, fo)) return 1;
		po::notify(vm);

		FPTL::Parser::run(programFile.c_str(), vm);
	}
	catch (std::exception & e)
	{
		std::cout
			<< e.what() << std::endl
			<< desc << std::endl;
	}

	return 0;
}