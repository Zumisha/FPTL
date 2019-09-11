#include <cstdlib>
#include <iostream>
#include <regex>
#include <fstream>
#include <iterator>
#include <random>

#include "StandardLibrary.h"
#include "DataTypes/String.h"
#include "DataTypes/Array.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace FPTL {
namespace Runtime {

namespace {

const double pi = 3.141592653589793;
const double e = 2.718281828459045;

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

void not(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);

}

void and(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

}

void or (SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

}

void equal(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->equal(lhs, rhs));
}

void notEqual(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(
		DataBuilders::createBoolean(
			!lhs.getOps()->combine(rhs.getOps())->equal(lhs, rhs).mIntVal
		)
	);
}

void greater(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->greater(lhs, rhs));
}

void greaterOrEqual(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(
		DataBuilders::createBoolean(
			!lhs.getOps()->combine(rhs.getOps())->less(lhs, rhs).mIntVal
		)
	);
}

void less(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->less(lhs, rhs));
}

void lessOrEqual(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(
		DataBuilders::createBoolean(
			!lhs.getOps()->combine(rhs.getOps())->greater(lhs, rhs).mIntVal
		)
	);
}

void add(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->add(lhs, rhs));
}

void sub(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->sub(lhs, rhs));
}

void mul(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->mul(lhs, rhs));
}

void div(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->div(lhs, rhs));
}

void mod(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->mod(lhs, rhs));
}

// Генерирует случайное вещественное число в диапазоне от 0 до 1.
void rand(SExecutionContext & aCtx)
{
	static thread_local std::random_device rd;
	static thread_local std::mt19937_64 gen(rd());
	static const std::uniform_real_distribution<> realDistrib;
	aCtx.push(DataBuilders::createDouble(realDistrib(gen)));
}

void sqrt(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::sqrt(arg.getOps()->toDouble(arg))));
}

void sin(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::sin(arg.getOps()->toDouble(arg))));
}

void cos(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::cos(arg.getOps()->toDouble(arg))));
}

void tan(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::tan(arg.getOps()->toDouble(arg))));
}

void asin(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::asin(arg.getOps()->toDouble(arg))));
}

void atan(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::atan(arg.getOps()->toDouble(arg))));
}

void round(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::floor(arg.getOps()->toDouble(arg) + 0.5)));
}

void log(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::log(arg.getOps()->toDouble(arg))));
}

void exp(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(DataBuilders::createDouble(std::exp(arg.getOps()->toDouble(arg))));
}

void loadPi(SExecutionContext & aCtx)
{
	aCtx.push(DataBuilders::createDouble(pi));
}

void loadE(SExecutionContext & aCtx)
{
	aCtx.push(DataBuilders::createDouble(e));
}

void abs(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(arg.getOps()->abs(arg));
}

void print(SExecutionContext & aCtx)
{
	static boost::mutex outputMutex;
	boost::lock_guard<boost::mutex> guard(outputMutex);

	aCtx.print(std::cout);
}

void printType(SExecutionContext & aCtx)
{
	static boost::mutex outputMutex;
	boost::lock_guard<boost::mutex> guard(outputMutex);

	aCtx.printTypes(std::cout);
}

// Преобразование в строку.
void toString(SExecutionContext & aCtx)
{
	std::stringstream strStream;
	auto & arg = aCtx.getArg(0);

	arg.getOps()->print(arg, strStream);

	aCtx.push(StringBuilder::create(aCtx, strStream.str()));
}

// Преобразование в вещественное число.
void toInteger(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);

	aCtx.push(DataBuilders::createInt(arg.getOps()->toInt(arg)));
}

// Преобразование в целое число.
void toDouble(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);

	aCtx.push(DataBuilders::createDouble(arg.getOps()->toDouble(arg)));
}

// Конкатенация строк.
void concat(SExecutionContext & aCtx)
{
	size_t length = 0;
	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		auto & arg = aCtx.getArg(i);
		const auto inStr = arg.getOps()->toString(arg);
		length += inStr->length();
	}

	const auto val = StringBuilder::create(aCtx, length);
	const auto str = val.mString->getChars();
	size_t curPos = 0;

	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		auto & arg = aCtx.getArg(i);
		const auto inStr = arg.getOps()->toString(arg);
		std::memcpy(str + curPos, inStr->getChars(), inStr->length());
		curPos += inStr->length();
	}

	aCtx.push(val);
}

// Длина строки.
void length(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	const auto str = arg.getOps()->toString(arg);

	aCtx.push(DataBuilders::createInt(static_cast<long long>(str->length())));
}

// Поиск по регулярному выражению.
void search(SExecutionContext & aCtx)
{
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	const auto src = arg0.getOps()->toString(arg0);
	const auto regEx = arg1.getOps()->toString(arg1);

	std::regex rx(regEx->str());
	std::cmatch match;

	if (std::regex_search(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), match, rx))
	{		
		for (size_t i = 0; i < rx.mark_count(); i++)
		{
			auto & m = match[i+1];
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
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	const auto src = arg0.getOps()->toString(arg0);
	const auto regEx = arg1.getOps()->toString(arg1);

	std::regex rx(regEx->str());
	std::cmatch match;

	if (std::regex_match(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), match, rx))
	{
		for (size_t i = 0; i < rx.mark_count(); ++i)
		{
			auto & m = match[i+1];
			auto val = StringBuilder::create(aCtx, src, m.first - src->contents(), m.second - src->contents());
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
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);
	auto & arg2 = aCtx.getArg(2);


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
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	const auto src = arg0.getOps()->toString(arg0);
	const auto pattern = arg1.getOps()->toString(arg1);

	const std::regex rx("^(?:\\s*)(" + pattern->str() + ")");

	std::cmatch match;

	if (std::regex_search(static_cast<const char *>(src->getChars()), static_cast<const char *>(src->getChars() + src->length()), match, rx))
	{
		const auto prefix = StringBuilder::create(aCtx, src, match[1].first - src->contents(), match[1].second - src->contents());
		aCtx.push(prefix);

		const auto suffix = StringBuilder::create(aCtx, src, match.suffix().first - src->contents(), match.suffix().second - src->contents());
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
	auto & arg = aCtx.getArg(0);

	const auto fileName = arg.getOps()->toString(arg);

	std::ifstream input;
	input.exceptions(std::ios::failbit | std::ios::badbit);
	input.open(fileName->str(), std::ios::binary);

	// Вычисляем размер файла.
	const auto begin = input.tellg();
	input.seekg(0, std::ios::end);
	const auto size = input.tellg() - begin;
	input.seekg(0, std::ios::beg);

	// Резервируем память под файл.
	const auto val = StringBuilder::create(aCtx, size);

	// Читаем данные.
	std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), val.mString->getChars());

	aCtx.push(val);
}

// Создание массива.
void createArray(SExecutionContext & aCtx)
{
	const auto sizeVal = aCtx.getArg(0).getOps()->toInt(aCtx.getArg(0));
	auto & initialVal = aCtx.getArg(1);

	if (sizeVal <= 0) throw std::invalid_argument("Размер массива должен быть больше нуля!");

	const size_t size = static_cast<size_t>(sizeVal);
	aCtx.push(ArrayValue::create(aCtx, size, initialVal));
}

// Чтение элемента из массива.
void getArrayElement(SExecutionContext & aCtx)
{
	auto & arrVal = aCtx.getArg(0);
	auto & posVal = aCtx.getArg(1);

	const size_t pos = posVal.getOps()->toInt(posVal);

	aCtx.push(ArrayValue::get(arrVal, pos));
}

// Запись элемента в массив.
void setArrayElement(SExecutionContext & aCtx)
{
	auto & arrVal = aCtx.getArg(0);
	auto & posVal = aCtx.getArg(1);
	auto & val = aCtx.getArg(2);

	const size_t pos = posVal.getOps()->toInt(posVal);

	ArrayValue::set(const_cast<DataValue &>(arrVal), pos, val);

	aCtx.push(arrVal);
}

void getArrayLength(SExecutionContext & aCtx)
{
	auto & arrVal = aCtx.getArg(0);
	aCtx.push(DataBuilders::createInt(ArrayValue::getLen(arrVal)));
}

void ArrayConcat(SExecutionContext & aCtx)
{
	aCtx.push(ArrayValue::concat(aCtx));
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
	//{"not", &not},
	//{"and", &and},
	//{"or", &or},
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

	// Работа с массивами.
	{"arrayCreate", &createArray},
	{"arrayGet", &getArrayElement},
	{"arraySet", &setArrayElement},
	{"arrayLen", &getArrayLength},
	{"arrayCat", &ArrayConcat}
};

StandardLibrary::StandardLibrary() : FunctionLibrary("StdLib")
{
	addFunctions(mFunctions);
}

}} // FPTL::Runtime
