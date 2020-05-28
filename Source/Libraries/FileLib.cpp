#include <regex>
#include <fstream>
#include <experimental/filesystem>
#include <string>

#include <boost/thread/mutex.hpp>

#include "FileLib.h"
#include "Macros.h"
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
				const auto& fileName = aCtx.getArg(0);
				const auto& val = aCtx.getArg(1);

#if fptlDebugBuild
				if (fileName.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(fileName.getOps()->getType(fileName), __func__);
#endif

				std::fstream input;
				input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					input.open(fileName.mString->str());
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
				const auto & val = aCtx.getArg(0);
				const auto & file = aCtx.getArg(1);

#if fptlDebugBuild
				if (file.getOps() != StringOps::get())
					throw BaseOps::invalidOperation(file.getOps()->getType(file), __func__);
#endif

				const auto fileName = file.mString;
				Utils::setPermissions(fileName->str());

				std::fstream output;
				output.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					output.open(fileName->str(), mode);
					output.precision(std::numeric_limits<double>::max_digits10);
					val.getOps()->write(val, output);
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

		const std::map<std::string, TFunction> functions =
		{
			{"openFile", &openFile},
			{"createFile", &createFile},
			{"appendFile", &appendFile},
		};

		void FileLib::Register()
		{
			FunctionLibrary::addFunctions(functions);
		}
	}
}
