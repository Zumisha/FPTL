#pragma once

#include <string> 

#include <boost/program_options.hpp>

#include "Utils/FormattedOutput.h"
#include "Evaluator/Run.h"

namespace FPTL 
{
	namespace Parser 
	{
		namespace po = boost::program_options;

		class CommandLineParser
		{
			po::positional_options_description mPosOpt;
			po::options_description mDesc;
			po::variables_map mVM;
			std::string mProgramPath;
			std::vector<std::string> mInputTuple;

		public:
			CommandLineParser();
			int Parse(int argc, const char ** argv);
			Utils::FormattedOutput GetFormattedOutput() const { return Utils::FormattedOutput(mVM["ansi"].as<bool>());	}
			std::string GetProgramPath() const { return mProgramPath; }
			std::vector<std::string> GetInputTuple() const { return mInputTuple; }
			bool GetShowInfo() const { return mVM["info"].as<bool>(); }
			bool GetShowTime() const { return mVM["time"].as<bool>(); }
			size_t GetCoresNum() const { return static_cast<size_t>(mVM["num-cores"].as<long long>()); }
			bool GetAllowProactive() const { return mVM["proactive"].as<bool>(); }

			Runtime::GcConfig GetGcConfig() const 
			{
				Runtime::GcConfig gcConfig;
				gcConfig.setEnabled(!mVM["disable-gc"].as<bool>());
				gcConfig.setVerbose(mVM["verbose-gc"].as<bool>());
				gcConfig.setYoungGenSize(static_cast<size_t>(mVM["young-gen"].as<long long>()) * 1024 * 1024);
				gcConfig.setOldGenSize(static_cast<size_t>(mVM["old-gen"].as<long long>()) * 1024 * 1024);
				gcConfig.setOldGenThreshold(mVM["old-gen-ratio"].as<double>());
				return gcConfig;
			}

		private:
			static bool optionsVerification(po::variables_map& vm, Utils::FormattedOutput& fo);
		};
	}
}
