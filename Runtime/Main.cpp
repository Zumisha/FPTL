#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <boost/lexical_cast.hpp>

#include "../Parser/Support.h"
#include "../Parser/Tokenizer.h"
#include "FSchemeGenerator.h"
#include "Run.h"

namespace FPTL {
namespace Parser {

void run(char * programPath, char * numProcessors)
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
		std::cout << "Running program: " << programPath << " on " << numProcessors << " processors...\n";

		Runtime::FSchemeGenerator schemeGenerator;
		schemeGenerator.process(astRoot);

		int processors = boost::lexical_cast<int>(numProcessors);

		Runtime::SchemeEvaluator evaluator;
		evaluator.runScheme(schemeGenerator.getFScheme(), schemeGenerator.getSchemeInput(), processors);
	}

	delete astRoot;
}

}}

int main(int argc, char ** argv)
{
	if (argc < 3)
	{
		std::cout << "Invalid command line arguments.\n Usage: fptl <source_file> <num_cores>\n";
		return -1;
	}

	FPTL::Parser::run(argv[1], argv[2]);

	return 0;
}