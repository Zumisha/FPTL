#include <regex>
#include <fstream>
#include <experimental/filesystem>
#include <string>

#include <boost/thread/mutex.hpp>

#include "FileLib.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/StringOps.h"
#include "Utils/FileStreamHelper.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {

			// Чтение содержимого файла.
			void openFile(SExecutionContext & aCtx)
			{
				// Проверяем имя файла.
				const auto& fileNameVal = aCtx.getArg(0);
				const auto& val = aCtx.getArg(1);

				BaseOps::opsCheck(StringOps::get(), fileNameVal);

				std::fstream input;
				input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					input.open(fileNameVal.mString->str());
					val.getOps()->read(val, aCtx, input);
					input.close();
					aCtx.push(val);
				}
				catch (const std::ios_base::failure& exc)
				{
					aCtx.push(DataBuilders::createUndefinedValue());
					auto errMsg = Utils::getfStreamError(input);
					if (errMsg.empty()) errMsg = exc.what();
					aCtx.push(StringBuilder::create(aCtx, errMsg));
				}
			}

			void writeToFile(SExecutionContext & aCtx, std::ios::openmode mode)
			{
				// Проверяем имя файла.
				const auto& val = aCtx.getArg(0);
				const auto& fileNameVal = aCtx.getArg(1);

				BaseOps::opsCheck(StringOps::get(), fileNameVal);

				const auto& fileName = fileNameVal.mString->str();
				Utils::setPermissions(fileName);

				std::fstream output;
				output.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					output.open(fileName, mode);
					output.precision(std::numeric_limits<double>::max_digits10);
					val.getOps()->rawPrint(val, output);
					output.close();
					aCtx.push(DataBuilders::createBoolean(true));
				}
				catch (const std::ios_base::failure& exc)
				{
					aCtx.push(DataBuilders::createBoolean(false));
					auto errMsg = Utils::getfStreamError(output);
					if (errMsg.empty()) errMsg = exc.what();
					aCtx.push(StringBuilder::create(aCtx, errMsg));
				}
			}

			// Создание или перезапись файла.
			void createFile(SExecutionContext & aCtx)
			{
				writeToFile(aCtx, std::ios::out);
			}

			// Запись в конец файла.
			void appendFile(SExecutionContext & aCtx)
			{
				writeToFile(aCtx, std::ios::app);
			}
		} // anonymous namespace

		const std::map<std::string, std::pair<TFunction, bool>> functions =
		{
			// Работа с массивами.
			{ "openFile", std::make_pair(&openFile, true) },
			{ "createFile", std::make_pair(&createFile, true) },
			{ "appendFile", std::make_pair(&appendFile, true) },
		};

		void FileLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
