#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

#include "Evaluator/EvalConfig.h"
#include "GC/GarbageCollector.h"

namespace FPTL::Parser {
    class CommandLineParser
    {
        using OptionValue = std::variant<bool, long long, double, std::string, std::vector<std::string>>;

        struct OptionInfo {
            std::string longName;
            char shortName = '\0';
            std::string description;
            OptionValue value;
        };

        std::unordered_map<std::string, OptionInfo> mOptions;
        std::unordered_map<char, std::string> mShortToLong; // Мапа для сокращенных форм (-h -> --help)

        std::string mProgramPath;
        std::vector<std::string> mInputTuple;

        template<typename T>
        T getAs(const std::string& key) const {
            return std::get<T>(mOptions.at(key).value);
        }

    public:
        CommandLineParser();
        int Parse(int argc, const char ** argv);
        void PrintHelp() const;

        Utils::FormattedOutput GetFormattedOutput() const { return Utils::FormattedOutput(getAs<bool>("ansi")); }
        std::string GetProgramPath() const { return mProgramPath.empty() ? getAs<std::string>("program") : mProgramPath; }
        std::vector<std::string> GetInputTuple() const { return mInputTuple.empty() ? getAs<std::vector<std::string>>("args") : mInputTuple; }
        bool GetExportAST() const { return getAs<bool>("export-ast"); }
        bool GetExportScheme() const { return getAs<bool>("export-scheme"); }

        Runtime::EvalConfig GetEvalConfig() const
        {
            const size_t numCores = GetCoresNum();
            const bool proactive = GetAllowProactive() && (numCores != 1);
            return Runtime::EvalConfig{
                GetFormattedOutput(),
                numCores,
                GetPrintInfo(),
                GetPrintTime(),
                proactive,
                GetTraceError(),
                GetUnsafeMode()
            };
        }

        Runtime::GcConfig GetGcConfig() const
        {
            Runtime::GcConfig gcConfig;
            gcConfig.setEnabled(!getAs<bool>("disable-gc"));
            gcConfig.setVerbose(getAs<bool>("verbose-gc"));
            gcConfig.setYoungGenSize(static_cast<size_t>(getAs<long long>("young-gen")) * 1024 * 1024);
            gcConfig.setOldGenSize(static_cast<size_t>(getAs<long long>("old-gen")) * 1024 * 1024);
            gcConfig.setOldGenThreshold(getAs<double>("old-gen-ratio"));
            return gcConfig;
        }

    private:
        static bool optionsVerification(const std::unordered_map<std::string, OptionInfo> &options);
        size_t GetCoresNum() const { return getAs<long long>("num-cores"); }
        bool GetAllowProactive() const { return getAs<bool>("proactive"); }
        bool GetTraceError() const { return getAs<bool>("trace"); }
        bool GetPrintInfo() const { return getAs<bool>("print-info"); }
        bool GetPrintTime() const { return getAs<bool>("print-time"); }
        bool GetUnsafeMode() const { return getAs<bool>("unsafe"); }
    };
}
