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

void run( int aArgc, char ** aArgv )
{
	for( int argId = 1; argId < aArgc; argId += 2 )
	{
		std::ifstream inpFile( aArgv[argId] );

		if( !inpFile.good() )
		{
			std::cout << "Unable to open file : " << aArgv[argId] << "\n";
			continue;
		}

		std::cout << "Running program: " << aArgv[argId] << " on " << aArgv[argId + 1] << " processors...\n";

		std::string inputStr;
		std::copy( std::istreambuf_iterator<char>(inpFile), std::istreambuf_iterator<char>(), std::back_inserter(inputStr) );

		Support support;
		Tokenizer tokenizer( inputStr );
		ASTNode * astRoot = support.getInternalForm( &tokenizer );

		if( astRoot )
		{
			std::cout << "No syntax errors found.\n";
		}

		support.getErrorList( std::cout );

		// Генерируем внутренне представление.
		if (astRoot)
		{
			Runtime::FSchemeGenerator schemeGenerator;

			schemeGenerator.process(astRoot);

			int numProcessors = (argId < aArgc) ? boost::lexical_cast<int>(aArgv[argId + 1]) : 1;

			Runtime::SchemeEvaluator evaluator;
			evaluator.runScheme(schemeGenerator.getFScheme(), schemeGenerator.getSchemeInput(), numProcessors);
		}

		delete astRoot;
	}
}

}}

int main( int argc, char ** argv )
{
	if (argc < 2)
	{
		std::cout << "Invalid command line arguments.\n Usage: fptl <source_file> <num_cores>";
		return -1;
	}

	FPTL::Parser::run(argc, argv);

	return 0;
}