#include "CommandLineParser.h"
#include <iomanip>

#include "Utils/FormattedOutput.h"

namespace FPTL::Parser {
    CommandLineParser::CommandLineParser() {
        const std::vector<OptionInfo> optionsList = {
            {"help", 'h', "produce help message", false},
            {"ansi", 'a', "use ansi formatting", false},
            {"export-ast", '\0', "export ast to file", false},
            {"export-scheme", '\0', "export intermediate scheme to file", false},
            {"disable-gc", '\0', "disable garbage collector", false},
            {"verbose-gc", '\0', "show garbage collector debug output", false},
            {"young-gen", '\0', "young generation size in MiB", 16LL},
            {"old-gen", '\0', "old generation size in MiB", 64LL},
            {"old-gen-ratio", '\0', "old generation usage ratio to trigger full GC", 0.7},
            {"num-cores", 'c', "number of execution cores", 1LL},
            {"proactive", 'p', "allow proactive calculations", false},
            {"trace", 't', "trace error evaluation", false},
            {"print-info", 'i', "print general evaluation info", false},
            {"print-time", 'm', "print evaluation time", false}, // в оригинале 'm' от "print-tiMe" или "meastime"
            {"unsafe", 'u', "allow unsafe values", false},
            {"program", '\0', "fptl program file", std::string("")},
            {"args", '\0', "input tuple", std::vector<std::string>{}}
        };

        for (const auto &opt: optionsList) {
            mOptions[opt.longName] = opt;
            if (opt.shortName != '\0') {
                mShortToLong[opt.shortName] = opt.longName;
            }
        }
    }


    void CommandLineParser::PrintHelp() const {
        std::cout << "FPTL Compiler/Runner\nAllowed options:\n\n";
        for (const auto &[key, info]: mOptions) {
            // Skip internal positional descriptions if you don't want them in main block
            if (key == "source-file" || key == "args") continue;

            std::string flagStr = "  --";
            flagStr += info.longName;
            if (info.shortName != '\0') {
                flagStr = "  -" + std::string(1, info.shortName) + " [ --" + info.longName + " ]";
            }
            std::cout << std::left << std::setw(30) << flagStr << info.description << "\n";
        }

        std::cout << "\nPositional options:\n"
                << "  --source-file arg             fptl program file\n"
                << "  --args arg                    input tuple\n";
    }

    int CommandLineParser::Parse(const int argc, const char **argv) {
        bool hasProgramPath = false;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            std::string key;
            bool isOption = false;

            if (arg.rfind("--", 0) == 0) {
                key = arg.substr(2);
                isOption = true;
            }
            else if (arg.rfind('-', 0) == 0 && arg.size() == 2) {
                char shortKey = arg[1];
                if (mShortToLong.find(shortKey) != mShortToLong.end()) {
                    key = mShortToLong[shortKey];
                    isOption = true;
                }
            }

            if (isOption) {
                if (mOptions.find(key) == mOptions.end()) {
                    std::cerr << "Error: Unknown option " << arg << "\n";
                    PrintHelp();
                    return 1;
                }

                if (std::holds_alternative<bool>(mOptions[key].value)) {
                    mOptions[key].value = true;
                } else {
                    if (i + 1 >= argc) {
                        std::cerr << "Error: Option " << arg << " requires a value.\n";
                        return 1;
                    }
                    std::string valStr = argv[++i];

                    if (std::holds_alternative<long long>(mOptions[key].value)) {
                        mOptions[key].value = std::stoll(valStr);
                    } else if (std::holds_alternative<double>(mOptions[key].value)) {
                        mOptions[key].value = std::stod(valStr);
                    } else if (std::holds_alternative<std::string>(mOptions[key].value)) {
                        mOptions[key].value = valStr;
                        if (key == "program") hasProgramPath = true;
                    } else if (std::holds_alternative<std::vector<std::string> >(mOptions[key].value)) {
                        std::get<std::vector<std::string> >(mOptions[key].value).push_back(valStr);
                    }
                }
            } else {
                if (!hasProgramPath && std::get<std::string>(mOptions["program"].value).empty() && mProgramPath.empty()) {
                    mProgramPath = arg;
                    mOptions["program"].value = arg;
                    hasProgramPath = true;
                } else {
                    mInputTuple.push_back(arg);
                    std::get<std::vector<std::string> >(mOptions["args"].value).push_back(arg);
                }
            }
        }

        if (getAs<bool>("help")) {
            PrintHelp();
            return 1;
        }

        if (!optionsVerification(mOptions)) {
            return 1;
        }

        return 0;
    }

    bool CommandLineParser::optionsVerification(const std::unordered_map<std::string, OptionInfo> &options) {
        const auto it = options.find("help");
        if (it != options.end() && std::get<bool>(it->second.value)) return true;

        if (std::get<std::string>(options.at("program").value).empty()) {
            std::cerr << "Error: Source file is not specified.\n";
            return false;
        }
        return true;
    }
}
