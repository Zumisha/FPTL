#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "../Parser/Support.h"
#include "../Parser/Tokenizer.h"
#include "FSchemeGenerator.h"
#include "Run.h"

namespace po = boost::program_options;

namespace FPTL {
namespace Parser {

void run(const char * programPath, int numCores)
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

		Runtime::SchemeEvaluator evaluator;
		evaluator.runScheme(schemeGenerator.getFScheme(), schemeGenerator.getSchemeInput(), numCores);
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
		;

	try
	{
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		FPTL::Parser::run(programFile.c_str(), numCores);
	}
	catch (std::exception & e)
	{
		std::cout
			<< e.what() << std::endl
			<< desc << std::endl;
	}

	return 0;
}