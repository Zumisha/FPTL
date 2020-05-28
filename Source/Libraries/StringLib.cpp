#include "StringLib.h"

#include <regex>
#include <string>

#include "Macros.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/StringOps.h"
#include "DataTypes/Ops/BooleanOps.h"
#include "LogicLib.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Длина строки.
			void length(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

#if fptlDebugBuild
				if (arg.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg.getOps()->getType(arg), __func__);
#endif

				aCtx.push(DataBuilders::createInt(static_cast<long long>(arg.mString->length())));
			}

			// Поиск по регулярному выражению.
			void search(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);

#if fptlDebugBuild
				if (arg0.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg0.getOps()->getType(arg0), __func__);
				if (arg1.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg1.getOps()->getType(arg1), __func__);
#endif

				auto* const src = arg0.mString;
				auto* const regEx = arg1.mString;

				std::regex rx(regEx->str());
				std::cmatch matchResults;

				if (std::regex_search(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), matchResults, rx))
				{
					for (size_t i = 0; i < rx.mark_count(); i++)
					{
						const auto& m = matchResults[i + 1];
						auto val = StringBuilder::create(aCtx, src, m.first - src->contents(), m.second - src->contents());
						aCtx.push(val);
					}
				}
				else
				{
					aCtx.push(DataBuilders::createUndefinedValue());
				}
			}

			// Проверка соответствия по регулярному выражению.
			void match(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);

#if fptlDebugBuild
				if (arg0.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg0.getOps()->getType(arg0), __func__);
				if (arg1.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg1.getOps()->getType(arg1), __func__);
#endif

				auto* const src = arg0.mString;
				auto* const regEx = arg1.mString;

				std::regex rx(regEx->str());
				std::cmatch match;

				if (std::regex_match(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), match, rx))
				{
					for (size_t i = 0; i < rx.mark_count(); ++i)
					{
						const auto & m = match[i + 1];
						const auto val = StringBuilder::create(aCtx, src, m.first - src->contents(), m.second - src->contents());
						aCtx.push(val);
					}
				}
				else
				{
					aCtx.push(DataBuilders::createUndefinedValue());
				}
			}

			// Замена по регулярному выражению.
			void replace(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);
				const auto & arg2 = aCtx.getArg(2);

#if fptlDebugBuild
				if (arg0.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg0.getOps()->getType(arg0), __func__);
				if (arg1.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg1.getOps()->getType(arg1), __func__);
				if (arg2.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg2.getOps()->getType(arg2), __func__);
#endif

				const auto src = arg0.mString;
				const auto pattern = arg1.mString;
				const auto format = arg2.mString;

				const std::regex rx(pattern->str());
				const auto result = std::regex_replace(src->str(), rx, format->str());
				aCtx.push(StringBuilder::create(aCtx, result));
			}

			// Выделение лексемы с начала строки.
			void getToken(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);

#if fptlDebugBuild
				if (arg0.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg0.getOps()->getType(arg0), __func__);
				if (arg1.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(arg1.getOps()->getType(arg1), __func__);
#endif

				const auto src = arg0.mString;
				const auto pattern = arg1.mString;

				const std::regex rx("^(?:\\s*)(" + pattern->str() + ")");

				std::cmatch matchResults;

				const auto first = static_cast<const char *>(src->getChars());
				const auto last = static_cast<const char *>(src->getChars() + src->length());

				if (std::regex_search(first, last, matchResults, rx))
				{
					const auto prefix = StringBuilder::create(aCtx, src, matchResults[1].first - src->contents(), matchResults[1].second - src->contents());
					aCtx.push(prefix);

					const auto suffix = StringBuilder::create(aCtx, src, matchResults.suffix().first - src->contents(), matchResults.suffix().second - src->contents());
					aCtx.push(suffix);
				}
				else
				{
					aCtx.push(DataBuilders::createUndefinedValue());
				}
			}

			// Преобразование в строку.
			void toString(SExecutionContext & aCtx)
			{
				std::stringstream strStream;
				const auto & arg = aCtx.getArg(0);

				arg.getOps()->write(arg, strStream);

				aCtx.push(StringBuilder::create(aCtx, strStream.str()));
			}
		} // anonymous namespace

		const std::map<std::string, TFunction> functions =
		{
			{"toString", &toString},
			
			{"length", &length},
			{"search", &search},
			{"replace", &replace},
			{"match", &match},
			{"getToken", &getToken}
		};

		void StringLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
