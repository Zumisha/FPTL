#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "../Parser/Support.h"
#include "../Parser/Tokenizer.h"
#include "FSchemeGenerator.h"
#include "Run.h"
#include "IntForm/Generator.h"
#include "IntForm/InternalForm.h"
#include "IntForm/Context.h"

namespace po = boost::program_options;

namespace FPTL {
namespace Parser {

template <typename T> void setOption(const po::variable_value & val, std::function<void(T)> setter)
{
	if (!val.empty())
	{
		setter(val.as<T>());
	}
}

void run(const char * programPath, int numCores, po::variables_map & vm)
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
	Tokenizer tokenizer(inputStr);
	ASTNode * astRoot = support.getInternalForm(&tokenizer);

	if (astRoot)
	{
		std::cout << "No syntax errors found.\n";
	}

	support.getErrorList(std::cout);

	// Генерируем внутренне представление.
	if (astRoot)
	{
		std::cout << "Running program: " << programPath << " on " << numCores << " cores...\n";

		Runtime::FSchemeGenerator schemeGenerator;
		schemeGenerator.process(astRoot);


		std::unique_ptr<Runtime::FunctionalProgram> internalForm(Runtime::Generator::generate(schemeGenerator.getProgram()));

		Runtime::SchemeEvaluator evaluator;

		Runtime::GcConfig gcConfig;
		
		setOption<bool>(vm["disable-gc"], [&](bool v) {gcConfig.setEnabled(!v); });
		setOption<bool>(vm["verbose-gc"], [&](bool v) {gcConfig.setVerbose(v); });
		setOption<size_t>(vm["young-gen"], [&](size_t s) {gcConfig.setYoungGenSize(s * 1024 * 1024); });
		setOption<size_t>(vm["old-gen"], [&](size_t s) {gcConfig.setOldGenSize(s * 1024 * 1024); });

		evaluator.setGcConfig(gcConfig);

		Runtime::IFExecutionContext ctx(internalForm->main().get());
		evaluator.run(ctx, numCores);

		//evaluator.runScheme(schemeGenerator.getFScheme(), schemeGenerator.getSchemeInput(), numCores);
	}

	delete astRoot;
}

}}

int main(int argc, char ** argv)
{
	std::string programFile;
	int numCores;

	po::options_description desc("Avilable options");
	desc.add_options()
		("source-file", po::value<std::string>(&programFile)->required(), "fptl program file")
		("num-cores", po::value<int>(&numCores)->default_value(1), "number of cores")
		("disable-gc", po::bool_switch(), "disable garbage collector")
		("verbose-gc", po::bool_switch(), "print garbage collector info")
		("young-gen", po::value<size_t>(), "young generation size in MiB")
		("old-gen", po::value<size_t>(), "old generation size in MiB")
		;

	try
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		FPTL::Parser::run(programFile.c_str(), numCores, vm);
	}
	catch (std::exception & e)
	{
		std::cout
			<< e.what() << std::endl
			<< desc << std::endl;
	}

	return 0;
}