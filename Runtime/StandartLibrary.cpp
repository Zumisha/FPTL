#include <cstdlib>
#include <iostream>
#include <regex>
#include <fstream>
#include <iterator>
#include <random>

#include "FScheme.h"
#include "StandartLibrary.h"
#include "../Parser/BuildInFunctionNames.h"
#include "String.h"
#include "Array.h"

namespace FPTL {
namespace Runtime {

namespace {

void id(SExecutionContext & aCtx)
{
	// Копируем данные аргументы от начала фрейма.
	for (int i = 0; i < aCtx.argNum; ++i)
	{
		aCtx.push(aCtx.getArg(i));
	}
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

void equals(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->equal(lhs, rhs));
}

void less(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->less(lhs, rhs));
}

void greater(SExecutionContext & aCtx)
{
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	aCtx.push(lhs.getOps()->combine(rhs.getOps())->greater(lhs, rhs));
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

// Генерирует случайное вещественное число в диапазоне от 0 до 1.
void rand(SExecutionContext & aCtx)
{
	static thread_local std::random_device rd;
	static thread_local std::mt19937_64 gen(rd());
	static const std::uniform_real_distribution<> real_distrib;
	aCtx.push(DataBuilders::createDouble(real_distrib(gen)));
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
	aCtx.push(DataBuilders::createDouble(3.141592653589793));
}

void loadE(SExecutionContext & aCtx)
{
	aCtx.push(DataBuilders::createDouble(2.718281828459045));
}

void abs(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	aCtx.push(arg.getOps()->abs(arg));
}

void print(SExecutionContext & aCtx)
{
	auto numArgs = aCtx.stack.size() - aCtx.argPos - aCtx.arity;

	for (int i = 0; i < numArgs; ++i)
	{
		auto & arg = aCtx.getArg(i);
		arg.getOps()->print(arg, std::cout);
		if (i + 1 < numArgs)
		{
			std::cout << "*";
		}
	}
}

void printType(SExecutionContext & aCtx)
{
	auto numArgs = aCtx.stack.size() - aCtx.argPos - aCtx.arity;

	for (int i = 0; i < numArgs; ++i)
	{
		auto & arg = aCtx.getArg(i);

		std::cout << arg.getOps()->getType(arg)->TypeName;

		if (i + 1 < numArgs)
		{
			std::cout << "*";
		}
	}
}

// Преобразование в строку.
void toString(SExecutionContext & aCtx)
{
	std::stringstream sstream;
	auto & arg = aCtx.getArg(0);

	arg.getOps()->print(arg, sstream);

	aCtx.push(StringBuilder::create(aCtx, sstream.str()));
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
	auto & lhs = aCtx.getArg(0);
	auto & rhs = aCtx.getArg(1);

	auto lhsStr = lhs.getOps()->toString(lhs);
	auto rhsStr = rhs.getOps()->toString(rhs);

	int length = lhsStr->length() + rhsStr->length();

	auto val = StringBuilder::create(aCtx, length);
	char * str = val.mString->getChars();

	std::memcpy(str, lhsStr->getChars(), lhsStr->length());
	std::memcpy(str + lhsStr->length(), rhsStr->getChars(), rhsStr->length());

	aCtx.push(val);
}

// Длина строки.
void length(SExecutionContext & aCtx)
{
	auto & arg = aCtx.getArg(0);
	auto str = arg.getOps()->toString(arg);

	aCtx.push(DataBuilders::createInt(str->length()));
}

// Поиск по регулярному выражению.
void search(SExecutionContext & aCtx)
{
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	auto src = arg0.getOps()->toString(arg0);
	auto regEx = arg1.getOps()->toString(arg1);

	std::regex rx(regEx->str());
	std::cmatch match;

	if (std::regex_search((const char *)src->getChars(), (const char *)(src->getChars() + src->length()), match, rx))
	{		
		for (unsigned i = 0; i < rx.mark_count(); i++)
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

// Проверка соответсвия по регулярному выражению.
void match(SExecutionContext & aCtx)
{
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	auto src = arg0.getOps()->toString(arg0);
	auto regEx = arg1.getOps()->toString(arg1);

	std::regex rx(regEx->str());
	std::cmatch match;

	if (std::regex_match((const char *)src->getChars(), (const char *)(src->getChars() + src->length()), match, rx))
	{
		for (unsigned i = 0; i < rx.mark_count(); i++)
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


	auto src     = arg0.getOps()->toString(arg0);
	auto pattern = arg1.getOps()->toString(arg1);
	auto format  = arg2.getOps()->toString(arg2);

	std::regex rx(pattern->str());

	std::string result = std::regex_replace(src->str(), rx, format->str());

	aCtx.push(StringBuilder::create(aCtx, result));
}

// Выделение лексемы с начала строки.
void getToken(SExecutionContext & aCtx)
{
	auto & arg0 = aCtx.getArg(0);
	auto & arg1 = aCtx.getArg(1);

	auto src = arg0.getOps()->toString(arg0);
	auto pattern = arg1.getOps()->toString(arg1);

	std::regex rx("^(?:\\s*)(" + pattern->str() + ")");

	std::cmatch match;

	if (std::regex_search((const char *)src->getChars(), (const char *)(src->getChars() + src->length()), match, rx))
	{
		auto prefix = StringBuilder::create(aCtx, src, match[1].first - src->contents(), match[1].second - src->contents());
		aCtx.push(prefix);

		auto suffix = StringBuilder::create(aCtx, src, match.suffix().first - src->contents(), match.suffix().second - src->contents());
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

	auto fileName = arg.getOps()->toString(arg);

	std::ifstream input;
	input.exceptions(std::ios::failbit | std::ios::badbit);
	input.open(fileName->str(), std::ios::binary);

	// Вычисляем размер файла.
	auto begin = input.tellg();
	input.seekg(0, std::ios::end);
	auto size = input.tellg() - begin;
	input.seekg(0, std::ios::beg);

	// Резервируем память под файл.
	auto val = StringBuilder::create(aCtx, size);

	// Читаем данные.
	std::copy(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>(), val.mString->getChars());

	aCtx.push(val);
}

// Создание массива.
void createArray(SExecutionContext & aCtx)
{
	auto & sizeVal = aCtx.getArg(0);
	auto & initialVal = aCtx.getArg(1);

	int size = sizeVal.getOps()->toInt(sizeVal);

	aCtx.push(ArrayValue::create(aCtx, size, initialVal));
}

// Чтение элемента из массива.
void getArrayElement(SExecutionContext & aCtx)
{
	auto & arrVal = aCtx.getArg(0);
	auto & posVal = aCtx.getArg(1);

	int pos = posVal.getOps()->toInt(posVal);

	aCtx.push(ArrayValue::get(arrVal, pos));
}

// Запись элемента в массив.
void setArrayElement(SExecutionContext & aCtx)
{
	auto & arrVal = aCtx.getArg(0);
	auto & posVal = aCtx.getArg(1);
	auto & val = aCtx.getArg(2);

	int pos = posVal.getOps()->toInt(posVal);

	ArrayValue::set(const_cast<DataValue &>(arrVal), pos, val);

	aCtx.push(arrVal);
}

} // anonymous namespace

StandartLibrary::StandartLibrary() : FunctionLibrary("StdLib")
{
	addFunction(FPTL::Parser::BuildInFunctions::Id, &id);

	// Арифметические операции.
	addFunction(FPTL::Parser::BuildInFunctions::Add, &add);
	addFunction(FPTL::Parser::BuildInFunctions::Subtract, &sub);
	addFunction(FPTL::Parser::BuildInFunctions::Multiply, &mul);
	addFunction(FPTL::Parser::BuildInFunctions::Divide, &div);
	addFunction(FPTL::Parser::BuildInFunctions::Modulus, &mod);
	addFunction(FPTL::Parser::BuildInFunctions::Equal, &equals);
	addFunction(FPTL::Parser::BuildInFunctions::Less, &less);
	addFunction(FPTL::Parser::BuildInFunctions::Greater, &greater);
	addFunction(FPTL::Parser::BuildInFunctions::GreaterOrEqual, &greaterOrEqual);
	addFunction(FPTL::Parser::BuildInFunctions::LessOrEqual, &lessOrEqual);
	addFunction(FPTL::Parser::BuildInFunctions::NotEqual, &notEqual);
	addFunction(FPTL::Parser::BuildInFunctions::Abs, &abs);

	// Трансцендентные функции.
	addFunction(FPTL::Parser::BuildInFunctions::Rand, &rand);
	addFunction(FPTL::Parser::BuildInFunctions::Sqrt, &sqrt);
	addFunction(FPTL::Parser::BuildInFunctions::Sin, &sin);
	addFunction(FPTL::Parser::BuildInFunctions::Cos, &cos);
	addFunction(FPTL::Parser::BuildInFunctions::Tan, &tan);
	addFunction(FPTL::Parser::BuildInFunctions::Asin, &asin);
	addFunction(FPTL::Parser::BuildInFunctions::Atan, &atan);
	addFunction(FPTL::Parser::BuildInFunctions::Exp, &exp);
	addFunction(FPTL::Parser::BuildInFunctions::Ln, &log);
	addFunction(FPTL::Parser::BuildInFunctions::Round, &round);
	addFunction(FPTL::Parser::BuildInFunctions::Pi, &loadPi);
	addFunction(FPTL::Parser::BuildInFunctions::E, &loadE);

	addFunction(FPTL::Parser::BuildInFunctions::Print, &print);
	addFunction(FPTL::Parser::BuildInFunctions::PrintType, &printType);

	// Преобразование типов.
	addFunction(FPTL::Parser::BuildInFunctions::toString, &toString);
	addFunction(FPTL::Parser::BuildInFunctions::toInt, &toInteger);
	addFunction(FPTL::Parser::BuildInFunctions::toReal, &toDouble);

	// Работа со строками.
	addFunction(FPTL::Parser::BuildInFunctions::Cat, &concat);
	addFunction(FPTL::Parser::BuildInFunctions::Length, &length);
	addFunction(FPTL::Parser::BuildInFunctions::Search, &search);
	addFunction(FPTL::Parser::BuildInFunctions::readFile, &readFile);
	addFunction(FPTL::Parser::BuildInFunctions::Match, &match);
	addFunction(FPTL::Parser::BuildInFunctions::Replace, &replace);
	addFunction(FPTL::Parser::BuildInFunctions::GetToken, &getToken);

	// Работа с массивами.
	addFunction(FPTL::Parser::BuildInFunctions::arrCreate, &createArray);
	addFunction(FPTL::Parser::BuildInFunctions::arrGetElem, &getArrayElement);
	addFunction(FPTL::Parser::BuildInFunctions::arrSetElem, &setArrayElement);
}

}} // FPTL::Runtime
