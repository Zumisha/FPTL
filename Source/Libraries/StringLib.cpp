#include "StringLib.h"

#include <regex>
#include <string>
#include <variant>

#include "DataTypes/Ops/StringOps.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Длина строки.
			int64_t length(const std::string& str)
			{
				return str.size();
			}

			// Поиск по регулярному выражению.
			std::variant<std::tuple<std::string, std::string, std::string>, void*> search(const std::string& str, const std::string& regEx)
			{
				const std::regex rx(regEx);
				std::smatch matchResults;

				if (std::regex_search(str, matchResults, rx))
				{
					return std::make_tuple(matchResults.prefix(), matchResults.str(), matchResults.suffix());
				}
				return nullptr;
			}

			// Проверка соответствия по регулярному выражению.
			bool match(const std::string& str, const std::string& regEx)
			{
				std::regex rx(regEx);
				std::smatch match;

				if (std::regex_match(str, rx))
				{
					return true;
				}
				return false;
			}

			// Замена по регулярному выражению.
			std::string replace(const std::string& str, const std::string& regEx, const std::string& replacement)
			{
				const std::regex rx(regEx);
				return std::regex_replace(str, rx, replacement);
			}

			// Выделение лексемы с начала строки.
			std::variant<std::tuple<std::string, std::string>, void*> getToken(const std::string& str, const std::string& regEx)
			{
				const std::regex rx("^(?:\\s*)(" + regEx + ")");

				std::smatch matchResults;

				if (std::regex_search(str, matchResults, rx))
				{
					return std::make_tuple(matchResults[1].str(), matchResults.suffix());
				}
				return nullptr;
			}
		} // anonymous namespace

		void StringLib::Register()
		{
			FunctionLibrary::addFunction("length", TypedFunction(&length, false, false));
			FunctionLibrary::addFunction("search", TypedFunction(&search, false, false));
			FunctionLibrary::addFunction("replace", TypedFunction(&replace, false, false));
			FunctionLibrary::addFunction("match", TypedFunction(&match, false, false));
			FunctionLibrary::addFunction("getToken", TypedFunction(&getToken, false, false));
		}
	}
}
