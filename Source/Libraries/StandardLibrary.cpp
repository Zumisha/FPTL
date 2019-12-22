#define _USE_MATH_DEFINES

#include <cstdlib>
#include <iostream>
#include <regex>
#include <fstream>
#include <iterator>
#include <random>
#include <experimental/filesystem>
#include <cmath>
#include <string>

#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include "Macros.h"
#include "StandardLibrary.h"
#include "DataTypes/Ops/Ops.h"
#include "DataTypes/Ops/StringOps.h"
#include "DataTypes/Ops/ArrayOps.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "Utils/FileStreamHelper.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {
			void id(SExecutionContext & aCtx)
			{
				// Копируем данные аргументы от начала фрейма.
				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					aCtx.push(aCtx.getArg(i));
				}
			}

			void tupleLength(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createInt(static_cast<long long>(aCtx.argNum)));
			}

			void Not(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

				aCtx.push(DataBuilders::createBoolean(!arg.getOps()->toInt(arg)));
			}

			void And(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) * rhs.getOps()->toInt(rhs))));
			}

			void Or(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) + rhs.getOps()->toInt(rhs))));
			}

			void Xor(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(DataBuilders::createBoolean((lhs.getOps()->toInt(lhs) ^ rhs.getOps()->toInt(rhs))));
			}

			void equal(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->equal(lhs, rhs));
			}

			void notEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(
					DataBuilders::createBoolean(
						!lhs.getOps()->combine(rhs.getOps())->equal(lhs, rhs).mIntVal
					)
				);
			}

			void greater(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->greater(lhs, rhs));
			}

			void greaterOrEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(
					DataBuilders::createBoolean(
						!lhs.getOps()->combine(rhs.getOps())->less(lhs, rhs).mIntVal
					)
				);
			}

			void less(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->less(lhs, rhs));
			}

			void lessOrEqual(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(
					DataBuilders::createBoolean(
						!lhs.getOps()->combine(rhs.getOps())->greater(lhs, rhs).mIntVal
					)
				);
			}

			void add(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->add(lhs, rhs));
			}

			void sub(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->sub(lhs, rhs));
			}

			void mul(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->mul(lhs, rhs));
			}

			void div(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->div(lhs, rhs));
			}

			void mod(SExecutionContext & aCtx)
			{
				const auto & lhs = aCtx.getArg(0);
				const auto & rhs = aCtx.getArg(1);

				aCtx.push(lhs.getOps()->combine(rhs.getOps())->mod(lhs, rhs));
			}

			// Генерирует случайное вещественное число в диапазоне от 0 до 1.
			void rand(SExecutionContext & aCtx)
			{
				static thread_local std::random_device rd;
				static thread_local std::mt19937_64 gen(rd());
				static std::uniform_real_distribution realDistrib;
				aCtx.push(DataBuilders::createDouble(realDistrib(gen)));
			}

			void sqrt(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::sqrt(arg.getOps()->toDouble(arg))));
			}

			void sin(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::sin(arg.getOps()->toDouble(arg))));
			}

			void cos(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::cos(arg.getOps()->toDouble(arg))));
			}

			void tan(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::tan(arg.getOps()->toDouble(arg))));
			}

			void asin(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::asin(arg.getOps()->toDouble(arg))));
			}

			void atan(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::atan(arg.getOps()->toDouble(arg))));
			}

			void round(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::floor(arg.getOps()->toDouble(arg) + 0.5)));
			}

			void log(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::log(arg.getOps()->toDouble(arg))));
			}

			void exp(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(DataBuilders::createDouble(std::exp(arg.getOps()->toDouble(arg))));
			}

			void loadPi(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createDouble(M_PI));
			}

			void loadE(SExecutionContext & aCtx)
			{
				aCtx.push(DataBuilders::createDouble(M_E));
			}

			void abs(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				aCtx.push(arg.getOps()->abs(arg));
			}

			void print(const SExecutionContext & aCtx)
			{
				static boost::mutex outputMutex;
				boost::lock_guard<boost::mutex> guard(outputMutex);

				aCtx.print(std::cout);
			}

			void printType(const SExecutionContext & aCtx)
			{
				static boost::mutex outputMutex;
				boost::lock_guard<boost::mutex> guard(outputMutex);

				aCtx.printTypes(std::cout);
			}

			// Преобразование в строку.
			void toString(SExecutionContext & aCtx)
			{
				std::stringstream strStream;
				const auto & arg = aCtx.getArg(0);

				arg.getOps()->print(arg, strStream);

				aCtx.push(StringBuilder::create(aCtx, strStream.str()));
			}

			// Преобразование в вещественное число.
			void toInteger(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

				aCtx.push(DataBuilders::createInt(arg.getOps()->toInt(arg)));
			}

			// Преобразование в целое число.
			void toDouble(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);

				aCtx.push(DataBuilders::createDouble(arg.getOps()->toDouble(arg)));
			}

			// Конкатенация строк.
			void concat(SExecutionContext & aCtx)
			{
				size_t len = 0;
				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					const auto & arg = aCtx.getArg(i);
					const auto inStr = arg.getOps()->toString(arg);
					len += inStr->length();
				}

				const auto val = StringBuilder::create(aCtx, len);
				const auto str = val.mString->getChars();
				size_t curPos = 0;

				for (size_t i = 0; i < aCtx.argNum; ++i)
				{
					const auto & arg = aCtx.getArg(i);
					const auto inStr = arg.getOps()->toString(arg);
					std::memcpy(str + curPos, inStr->getChars(), inStr->length());
					curPos += inStr->length();
				}

				aCtx.push(val);
			}

			// Длина строки.
			void length(SExecutionContext & aCtx)
			{
				const auto & arg = aCtx.getArg(0);
				const auto str = arg.getOps()->toString(arg);

				aCtx.push(DataBuilders::createInt(static_cast<long long>(str->length())));
			}

			// Поиск по регулярному выражению.
			void search(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);

				const auto src = arg0.getOps()->toString(arg0);
				const auto regEx = arg1.getOps()->toString(arg1);

				std::regex rx(regEx->str());
				std::cmatch matchResults;

				if (std::regex_search(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), matchResults, rx))
				{
					for (size_t i = 0; i < rx.mark_count(); i++)
					{
						auto & m = matchResults[i + 1];
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

				const auto src = arg0.getOps()->toString(arg0);
				const auto regEx = arg1.getOps()->toString(arg1);

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


				const auto src = arg0.getOps()->toString(arg0);
				const auto pattern = arg1.getOps()->toString(arg1);
				const auto format = arg2.getOps()->toString(arg2);

				const std::regex rx(pattern->str());
				const auto result = std::regex_replace(src->str(), rx, format->str());
				aCtx.push(StringBuilder::create(aCtx, result));
			}

			// Выделение лексемы с начала строки.
			void getToken(SExecutionContext & aCtx)
			{
				const auto & arg0 = aCtx.getArg(0);
				const auto & arg1 = aCtx.getArg(1);

				const auto src = arg0.getOps()->toString(arg0);
				const auto pattern = arg1.getOps()->toString(arg1);

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

			// Чтение содержимого файла.
			void readFile(SExecutionContext & aCtx)
			{
				// Проверяем имя файла.
				const auto & arg = aCtx.getArg(0);

				const auto fileName = arg.getOps()->toString(arg);
				
				DataValue val;
				std::string errMsg = "";
				std::fstream input;
				input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					// Вычисляем размер файла.
					const auto begin = input.tellg();
					input.seekg(0, std::ios::end);
					const auto size = input.tellg() - begin;
					input.seekg(0, std::ios::beg);

					// Резервируем память под файл.					
					val = StringBuilder::create(aCtx, size);
					// Читаем данные.
					std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), val.mString->getChars());
					input.close();
				}
				catch (const std::ios_base::failure& exc)
				{
					val = DataBuilders::createUndefinedValue();
					errMsg = Utils::getfStreamError(input);
					if (errMsg == "") errMsg = exc.what();
				}
				aCtx.push(val);
				aCtx.push(StringBuilder::create(aCtx, errMsg));
			}

			void writeToFile(SExecutionContext & aCtx, std::ios::openmode mode)
			{
				// Проверяем имя файла.
				const auto & val = aCtx.getArg(0);
				const auto & file = aCtx.getArg(1);

				const auto fileName = file.getOps()->toString(file);

				if (std::experimental::filesystem::exists(std::experimental::filesystem::status(fileName->str())))
				{
					std::experimental::filesystem::permissions(fileName->str(),
						std::experimental::filesystem::perms::add_perms | std::experimental::filesystem::perms::owner_all | std::experimental::filesystem::perms::group_all);
				}

				DataValue res;
				std::string errMsg = "";
				std::fstream output;
				output.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					output.open(fileName->str(), mode);
					output.precision(std::numeric_limits<double>::max_digits10);
					val.getOps()->write(val, output);
					res = DataBuilders::createBoolean(true);
					output.close();
				}
				catch (const std::ios_base::failure& exc)
				{
					res = DataBuilders::createBoolean(false);
					errMsg = Utils::getfStreamError(output);
					if (errMsg == "") errMsg = exc.what();
				}
				aCtx.push(res);
				aCtx.push(StringBuilder::create(aCtx, errMsg));
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

			// Создание массива.
			void createArray(SExecutionContext & aCtx)
			{
				const auto sizeVal = aCtx.getArg(0);
				const auto& initialVal = aCtx.getArg(1);

				const auto intSize = sizeVal.getOps()->toInt(sizeVal);

#if fptlDebugBuild
				if (sizeVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(sizeVal.getOps()->getType(sizeVal), "toInt");
				if (intSize <= 0) throw std::invalid_argument(ArrayValue::negativeSizeMsg(intSize));
#endif

				const auto size = static_cast<size_t>(intSize);
				aCtx.push(ArrayValue::create(aCtx, size, initialVal));
			}

			// Чтение элемента из массива.
			void getArrayElement(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				const auto & posVal = aCtx.getArg(1);

#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal);
				if (posVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(posVal.getOps()->getType(posVal), "toInt");
#endif

				const size_t pos = posVal.getOps()->toInt(posVal);
				aCtx.push(ArrayValue::get(arrVal, pos));
			}

			// Запись элемента в массив.
			void setArrayElement(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				const auto & posVal = aCtx.getArg(1);
				const auto & val = aCtx.getArg(2);

#if fptlDebugBuild
				ArrayValue::arrayValueCheck(arrVal);
				if (posVal.getOps() != IntegerOps::get())
					throw BaseOps::invalidOperation(posVal.getOps()->getType(posVal), "toInt");
#endif

				const size_t pos = posVal.getOps()->toInt(posVal);

				ArrayValue::set(const_cast<DataValue &>(arrVal), pos, val);

				aCtx.push(arrVal);
			}

			void getArrayLength(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				ArrayValue::arrayValueCheck(arrVal);
				aCtx.push(DataBuilders::createInt(ArrayValue::getLen(arrVal)));
			}

			void ArrayConcat(SExecutionContext & aCtx)
			{
				aCtx.push(ArrayValue::concat(aCtx));
			}

			void ArrayCopy(SExecutionContext & aCtx)
			{
				const auto & arrVal = aCtx.getArg(0);
				ArrayValue::arrayValueCheck(arrVal);
				aCtx.push(ArrayValue::copy(aCtx, arrVal));
			}

			void ArrayDot(SExecutionContext & aCtx)
			{
				const auto & arrVal1 = aCtx.getArg(0);
				const auto & arrVal2 = aCtx.getArg(1);
				ArrayValue::arrayValueCheck(arrVal1);
				ArrayValue::arrayValueCheck(arrVal2);
				aCtx.push(ArrayValue::dot(aCtx, arrVal1, arrVal2));
			}

			// Запись элемента в массив.
			void arrayFromFile(SExecutionContext & aCtx)
			{
				auto arrVal = aCtx.getArg(0);
				const auto fileVal = aCtx.getArg(1);

				ArrayValue::arrayValueCheck(arrVal);
				const auto fileName = fileVal.getOps()->toString(fileVal);

				std::string errMsg = "";
				std::fstream input;
				input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try
				{
					input.open(fileName->str());
					ArrayValue::fromString(arrVal, static_cast<std::istream&>(input));
					input.close();
				}
				catch (const std::ios_base::failure& exc)
				{
					arrVal = DataBuilders::createUndefinedValue();
					errMsg = Utils::getfStreamError(input);
					if (errMsg == "") errMsg = exc.what();
				}
				aCtx.push(arrVal);
				aCtx.push(StringBuilder::create(aCtx, errMsg));
			}
		} // anonymous namespace

		const std::map<std::string, TFunction> StandardLibrary::mFunctions =
		{
			// Работа с кортежем.
			{"id", &id},
			{"tupleLen", &tupleLength},

			// Арифметические.
			{"add",&add},
			{"sub", &sub},
			{"mul", &mul},
			{"div", &div},
			{"mod", &mod},
			{"abs", &abs},
			{"sqrt", &sqrt},
			{"exp", &exp},
			{"ln", &log},
			{"round", &round},
			{"sin", &sin},
			{"cos", &cos},
			{"tan", &tan},
			{"asin", &asin},
			{"atan", &atan},
			{"Pi", &loadPi},
			{"E", &loadE},
			{"rand", &rand},

			//Логические.
			{"not", &Not},
			{"and", &And},
			{"or", &Or },
			{"xor", &Xor },
			{"equal", &equal},
			{"nequal", &notEqual},
			{"greater", &greater},
			{"gequal", &greaterOrEqual},
			{"less", &less},
			{"lequal", &lessOrEqual},

			// Работа со строками.
			{"length", &length},
			{"cat", &concat},
			{"search", &search},
			{"replace", &replace},
			{"match", &match},
			{"getToken", &getToken},

			// Преобразования типов.
			{"toInt", &toInteger},
			{"toReal", &toDouble},
			{"toString", &toString},

			// Ввод / вывод.
			{"print", &print},
			{"printType", &printType},
			{"readFile", &readFile},
			{"createFile", &createFile},
			{"appendFile", &appendFile},

			// Работа с массивами.
			{"arrayCreate", &createArray},
			{"arrayGet", &getArrayElement},
			{"arraySet", &setArrayElement},
			{"arrayLen", &getArrayLength},
			{"arrayCat", &ArrayConcat},
			{"arrayCopy", &ArrayCopy},
			{"ArrayDot", &ArrayDot},
			{"arrayFromFile", &arrayFromFile}
		};

		StandardLibrary::StandardLibrary() : FunctionLibrary("StdLib")
		{
			addFunctions(mFunctions);
		}
	}
}
