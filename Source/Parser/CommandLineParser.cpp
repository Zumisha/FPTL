#include <iostream>

#include "Macros.h"
#include "CommandLineParser.h"

namespace FPTL::Parser
{
		CommandLineParser::CommandLineParser() : mDesc("Available options:")
		{
			mDesc.add_options()
				("source-file,s", po::value<std::string>(&mProgramPath), "Path to FPTL program file.")
				("num-cores,n", po::value<long long>()->default_value(1)->required(), "Number of work threads.")
				("input-tuple,in", po::value<std::vector<std::string>>(&mInputTuple)->multitoken(), "Input variables.")
				("proactive,p", po::bool_switch(), "Enable proactive calculations.")

				("help,h", "Provides information about startup options.")
				("version,v", "Displays the date and time of the interpreter build.")
				("print-time,t", po::bool_switch(), "Displays interpretation and evaluation times.")
				("print-info,i", po::bool_switch(), "Displays information about the interpretation and evaluation processes.")
				("ansi,a", po::bool_switch(), "Allow ANSI text formatting.")
				("export-ast", po::bool_switch(),"Serialize AST to the file.")
				("export-scheme", po::bool_switch(), "Serialize functional schemes to the file.")
				("trace", po::bool_switch(), "Print runtime error stack trace (Slow down execution about 5 times).")
				("unsafe,u", po::bool_switch(), "Disable all runtime checks (Speed up execution about 10%).")

				("disable-gc", po::bool_switch(), "Disable garbage collector.")
				("verbose-gc", po::bool_switch(), "Displays information about the work of the garbage collector.")
				("young-gen", po::value<long long>()->default_value(20), "Young generation size in MiB.")
				("old-gen", po::value<long long>()->default_value(100), "Old generation size in MiB.")
				("old-gen-ratio", po::value<double>()->default_value(0.75), "Old gen usage ratio to start full GC.");
		}

		int CommandLineParser::Parse(const int argc, const char ** argv)
		{
			try
			{
				mProgramPath = "";
				mInputTuple = std::vector<std::string>();

				mVM.clear();
				auto parsed = po::command_line_parser(argc, argv).options(mDesc).run();
				po::store(parsed, mVM, false);
				if (!mVM.count("source-file"))
				{
					mPosOpt.add("source-file", 1);					
				}
				mPosOpt.add("input-tuple", -1);

				mVM.clear();
				parsed = po::command_line_parser(argc, argv).options(mDesc).positional(mPosOpt).run();
				po::store(parsed, mVM, false);
				Utils::FormattedOutput fo = GetFormattedOutput();

				if (!optionsVerification(mVM, fo)) return 1;
				if (mVM.count("version"))
					std::cout << "Version of the interpreter from " << fo.Bold(fo.Green(BUILD_DATE)) << "." << std::endl << std::endl;
				if (mVM.count("help"))
				{
					std::cout << mDesc << std::endl << std::endl;
					return -1;
				}
				po::notify(mVM);
				return 0;
			}
			catch (std::exception & e)
			{
				if (mVM.count("version") && mVM.size() == 1) return -1;
					std::cout << "Error: " << e.what() << std::endl
						<< "\nUse --help or -h to display all available options." << std::endl;
					return 1;
			}
		}

		bool CommandLineParser::optionsVerification(po::variables_map& vm, Utils::FormattedOutput& fo)
		{
			bool noErrors = true;
			if (vm["num-cores"].as<long long>() <= 0)
			{
				std::cout << "Number of work threads " << fo.Bold(fo.Red("must be positive integer!")) << std::endl << std::endl;
				noErrors = false;
			}
			if (vm["young-gen"].as<long long>() <= 0)
			{
				std::cout << "Young generation size " << fo.Bold(fo.Red("must be positive integer!")) << std::endl << std::endl;
				noErrors = false;
			}
			if (vm["old-gen"].as<long long>() <= 0)
			{
				std::cout << "Old generation size " << fo.Bold(fo.Red("must be positive integer!")) << std::endl << std::endl;
				noErrors = false;
			}
			if (vm["old-gen-ratio"].as<double>() <= 0 || vm["old-gen-ratio"].as<double>() > 1)
			{
				std::cout << "Old gen usage ratio " << fo.Bold(fo.Red("must be in the interval (0, 1]!")) << std::endl << std::endl;
				noErrors = false;
			}
			return noErrors;
		}
}
