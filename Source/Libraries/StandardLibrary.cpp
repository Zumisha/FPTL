﻿#define _USE_MATH_DEFINES

#include <iostream>
#include <regex>
#include <fstream>
#include <iterator>
#include <random>
#include <filesystem>
#include <cmath>

#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

#include "Macros.h"
#include "StandardLibrary.h"
#include "DataTypes/Values/Value.h"
#include "DataTypes/Ops/IntegerOps.h"
#include "DataTypes/Ops/BooleanOps.h"
#include "DataTypes/Ops/DoubleOps.h"
#include "DataTypes/Ops/StringOps.h"
#include "DataTypes/Ops/ArrayOps.h"

namespace FPTL {
namespace Runtime {

namespace {

void id(SExecutionContext& aCtx)
{
	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		aCtx.push(aCtx.getArg(i));
	}
}

void tupleLength(SExecutionContext& aCtx)
{
	aCtx.push(IntegerOps::Create(static_cast<int64_t>(aCtx.argNum)));
}

void Not(SExecutionContext& aCtx)
{
	const auto& arg = aCtx.getArg(0);

#if fptlDebugBuild
	BooleanOps::ValueCheck(arg);
#endif

	aCtx.push(BooleanOps::Create(!arg.ToBool()));
}

void And(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);

#if fptlDebugBuild
	BooleanOps::ValueCheck(arg0);
	BooleanOps::ValueCheck(arg1);
#endif

	aCtx.push(BooleanOps::Create(arg0.ToBool() && arg1.ToBool()));
}

void Or(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);

#if fptlDebugBuild
	BooleanOps::ValueCheck(arg0);
	BooleanOps::ValueCheck(arg1);
#endif

	aCtx.push(BooleanOps::Create(arg0.ToBool() || arg1.ToBool()));
}

void Xor(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1= aCtx.getArg(1);

#if fptlDebugBuild
	BooleanOps::ValueCheck(arg0);
	BooleanOps::ValueCheck(arg1);
#endif

	aCtx.push(BooleanOps::Create(arg0.ToBool() ^ arg1.ToBool()));
}

void equal(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(aCtx.getArg(0).EqualTo(aCtx.getArg(1))));
}

void notEqual(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(!aCtx.getArg(0).EqualTo(aCtx.getArg(1))));
}

void greater(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(aCtx.getArg(0).GreaterThan(aCtx.getArg(1))));
}

void greaterOrEqual(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(!aCtx.getArg(0).LessThan(aCtx.getArg(1))));
}

void less(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(aCtx.getArg(0).LessThan(aCtx.getArg(1))));
}

void lessOrEqual(SExecutionContext& aCtx)
{
	aCtx.push(BooleanOps::Create(!aCtx.getArg(0).GreaterThan(aCtx.getArg(1))));
}

void add(SExecutionContext& aCtx)
{
	aCtx.push(aCtx.getArg(0) + aCtx.getArg(1));
}

void sub(SExecutionContext& aCtx)
{
	aCtx.push(aCtx.getArg(0) - aCtx.getArg(1));
}

void mul(SExecutionContext& aCtx)
{
	const auto & lhs = aCtx.getArg(0);
	const auto & rhs = aCtx.getArg(1);
	aCtx.push(lhs.ops->Mul(lhs, rhs));
	//aCtx.push(aCtx.getArg(0) * aCtx.getArg(1));
}

void div(SExecutionContext& aCtx)
{
	aCtx.push(aCtx.getArg(0) / aCtx.getArg(1));
}

void mod(SExecutionContext& aCtx)
{
	aCtx.push(aCtx.getArg(0) % aCtx.getArg(1));
}

// Генерирует случайное вещественное число в диапазоне от 0 до 1.
void rand(SExecutionContext& aCtx)
{
	static thread_local std::random_device rd;
	static thread_local std::mt19937_64 gen(rd());
	static std::uniform_real_distribution realDistrib;
	aCtx.push(DoubleOps::Create(realDistrib(gen)));
}

void sqrt(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::sqrt(aCtx.getArg(0).ToDouble())));
}

void sin(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::sin(aCtx.getArg(0).ToDouble())));
}

void cos(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::cos(aCtx.getArg(0).ToDouble())));
}

void tan(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::tan(aCtx.getArg(0).ToDouble())));
}

void asin(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::asin(aCtx.getArg(0).ToDouble())));
}

void atan(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::atan(aCtx.getArg(0).ToDouble())));
}

void round(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::floor(aCtx.getArg(0).ToDouble() + 0.5)));
}

void log(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::log(aCtx.getArg(0).ToDouble())));
}

void exp(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(std::exp(aCtx.getArg(0).ToDouble())));
}

void loadPi(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(M_PI));
}

void loadE(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(M_E));
}

void abs(SExecutionContext& aCtx)
{
	aCtx.push(aCtx.getArg(0).Abs());
}

void print(const SExecutionContext& aCtx)
{
	static boost::mutex outputMutex;
	boost::lock_guard<boost::mutex> guard(outputMutex);

	aCtx.print(std::cout);
}

void printType(const SExecutionContext& aCtx)
{
	static boost::mutex outputMutex;
	boost::lock_guard<boost::mutex> guard(outputMutex);

	aCtx.printTypes(std::cout);
}

// Преобразование в вещественное число.
void toInteger(SExecutionContext& aCtx)
{
	aCtx.push(IntegerOps::Create(aCtx.getArg(0).ToInt()));
}

// Преобразование в целое число.
void toDouble(SExecutionContext& aCtx)
{
	aCtx.push(DoubleOps::Create(aCtx.getArg(0).ToDouble()));
}

// Преобразование в строку.
void toString(SExecutionContext& aCtx)
{
	aCtx.push(StringOps::Create(aCtx.getArg(0).ToString()));
}

// Конкатенация строк.
void concat(SExecutionContext& aCtx)
{
	std::stringstream strStream;

	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		const auto& arg = aCtx.getArg(i);
#if fptlDebugBuild
		StringOps::ValueCheck(arg);
#endif
		arg.Print(strStream);
	}

	aCtx.push(StringOps::Create(strStream.str()));
}

// Длина строки.
void length(SExecutionContext& aCtx)
{
	const auto& arg = aCtx.getArg(0);

	aCtx.push(IntegerOps::Create(static_cast<int64_t>(arg.Length())));
}

// Поиск по регулярному выражению.
void search(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);

#if fptlDebugBuild
	StringOps::ValueCheck(arg0);
	StringOps::ValueCheck(arg1);
#endif

	const auto& src = arg0.ToString();
	std::regex rx(arg1.ToString());
	std::smatch matchResults;

	if (std::regex_search(src, matchResults, rx))
	{
			const auto& prefix = StringOps::Create(matchResults.prefix());
			aCtx.push(prefix);
			const auto& suffix = StringOps::Create(matchResults.suffix());
			aCtx.push(suffix);
			for (size_t i = 0; i < rx.mark_count(); ++i)
			{
				const auto& m = matchResults[i + 1];
				const auto& val = StringOps::Create(m);
				aCtx.push(val);
			}
	}
	else
	{
		aCtx.push(BaseOps::Create());
	}
}

// Проверка соответствия по регулярному выражению.
void match(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);

#if fptlDebugBuild
	StringOps::ValueCheck(arg0);
	StringOps::ValueCheck(arg1);
#endif
	const auto& src = arg0.ToString();
	std::regex rx(arg1.ToString());

	std::smatch matchResults;

	if (std::regex_match(src, matchResults, rx))
	{
		for (size_t i = 0; i < rx.mark_count(); ++i)
		{
			const auto& m = matchResults[i+1];
			const auto& val = StringOps::Create(m);
			aCtx.push(val);
		}
	}
	else
	{
		aCtx.push(BaseOps::Create());
	}
}

// Замена по регулярному выражению.
void replace(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);
	const auto& arg2 = aCtx.getArg(2);

#if fptlDebugBuild
	StringOps::ValueCheck(arg0);
	StringOps::ValueCheck(arg1);
	StringOps::ValueCheck(arg2);
#endif

	const auto& src = arg0.ToString();
	std::regex rx(arg1.ToString());
	const auto& replacement = arg2.ToString();

	const auto& result = std::regex_replace(src, rx, replacement);
	aCtx.push(StringOps::Create(result));
}

// Выделение лексемы с начала строки.
void getToken(SExecutionContext& aCtx)
{
	const auto& arg0 = aCtx.getArg(0);
	const auto& arg1 = aCtx.getArg(1);

#if fptlDebugBuild
	StringOps::ValueCheck(arg0);
	StringOps::ValueCheck(arg1);
#endif

	const auto& src = arg0.ToString();
	const std::regex rx("^(?:\\s*)(" + arg1.ToString() + ")");
	std::smatch matchResults;

	if (std::regex_search(src, matchResults, rx))
	{
		const auto& suffix = StringOps::Create(matchResults.suffix());
		aCtx.push(suffix);

		const auto& result = StringOps::Create(matchResults[0]);
		aCtx.push(result);
	}
	else
	{
		aCtx.push(BaseOps::Create());
	}
}

// Чтение содержимого файла.
void readFile(SExecutionContext& aCtx)
{
	// Проверяем имя файла.
	const auto& arg = aCtx.getArg(0);

#if fptlDebugBuild
	StringOps::ValueCheck(arg);
#endif

	const auto& fileName = arg.ToString();

	std::ifstream input;
	input.open(fileName);
	if (input.is_open())
	{
		const std::string str((std::istreambuf_iterator<char>(input)),
			std::istreambuf_iterator<char>());
		aCtx.push(StringOps::Create(str));
	}
	else
	{
		aCtx.push(BaseOps::Create());
	}
}

void writeToFile(SExecutionContext& aCtx, std::ios::openmode mode)
{
	// Проверяем имя файла.
	const auto& val = aCtx.getArg(0);
	const auto& file = aCtx.getArg(1);

#if fptlDebugBuild
	StringOps::ValueCheck(file);
#endif

	const auto& fileName = file.ToString();

	if (exists(std::filesystem::status(fileName)))
	{
		permissions(fileName,
			std::filesystem::perms::owner_all | std::filesystem::perms::group_all,
			std::filesystem::perm_options::add);
	}
	std::ofstream output(fileName, mode);
	output.precision(std::numeric_limits<double>::max_digits10);
	if (output.is_open())
	{
		val.Print(output);
		aCtx.push(BooleanOps::Create(true));
	}
	else
	{
		aCtx.push(BooleanOps::Create(false));
	}
}

// Создание или перезапись файла.
void createFile(SExecutionContext& aCtx)
{
	writeToFile(aCtx, std::ios::out);
}

// Запись в конец файла.
void appendFile(SExecutionContext& aCtx)
{
	writeToFile(aCtx, std::ios::app);
}

// Создание массива.
void createArray(SExecutionContext& aCtx)
{
	const auto& sizeVal = aCtx.getArg(0);
	const auto& initialVal = aCtx.getArg(1);

#if fptlDebugBuild
	IntegerOps::ValueCheck(sizeVal);
#endif

	const auto size = sizeVal.ToInt();

#if fptlDebugBuild
	ArrayOps::SizeCheck(size);
#endif

	aCtx.push(ArrayOps::Create(size, initialVal));
}

// Чтение элемента из массива.
void getArrayElement(SExecutionContext& aCtx)
{
	const auto& arrVal = aCtx.getArg(0);
	const auto& posVal = aCtx.getArg(1);

#if fptlDebugBuild
	ArrayOps::ValueCheck(arrVal);
	IntegerOps::ValueCheck(posVal);
#endif

	const auto pos = posVal.ToInt();

#if fptlDebugBuild
	ArrayOps::IndexCheck(arrVal, pos);
#endif

	aCtx.push(arrVal[pos]);
}

// Запись элемента в массив.
void setArrayElement(SExecutionContext& aCtx)
{
	const auto& arrVal = aCtx.getArg(0);
	const auto& posVal = aCtx.getArg(1);
	const auto& val = aCtx.getArg(2);

#if fptlDebugBuild
	ArrayOps::ValueCheck(arrVal);
	IntegerOps::ValueCheck(posVal);
#endif

	const auto pos = posVal.ToInt();

#if fptlDebugBuild
	ArrayOps::IndexCheck(arrVal, pos);
	if (val.Type() != arrVal.Type().typeParameters[0])
	{
		std::stringstream error;
		error << "Cannot assign element of type " << val.Type() << " to an array of type " << arrVal.Type().typeParameters[0] << ".";
		throw std::runtime_error(error.str());
	}
#endif

	arrVal[pos] = val;
	aCtx.push(arrVal);
}

void ArrayConcat(SExecutionContext& aCtx)
{
#if fptlDebugBuild
	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		ArrayOps::ValueCheck(aCtx.getArg(i));
	}
#endif

	const auto& firstArr = aCtx.getArg(0);
	const auto& type = firstArr.Type();
	size_t len = firstArr.Length();

	for (size_t i = 1; i < aCtx.argNum; ++i)
	{
		const auto& arr = aCtx.getArg(i);
#if fptlDebugBuild
		if (arr.Type() != type)
		{
			std::stringstream error;
			error << "Cannot concat an array of type " << type << " with an array of type " << arr.Type();
			throw std::runtime_error(error.str());
		}
#endif
		len += arr.Length();
	}

	auto res = ArrayOps::Create(len, firstArr[0]);

	size_t curPos = 0;
	for (size_t i = 0; i < aCtx.argNum; ++i)
	{
		const auto& arr = aCtx.getArg(i);
		for (size_t j = 0; j < arr.Length(); ++j)
		{
			res[curPos + j] = arr[j];
		}
		curPos += arr.Length();
	}

	aCtx.push(res);
}

void ArrayDot(SExecutionContext & aCtx)
{
	const auto& arrVal1 = aCtx.getArg(0);
	const auto& arrVal2 = aCtx.getArg(1);

#if fptlDebugBuild
	ArrayOps::ValueCheck(arrVal1);
	ArrayOps::ValueCheck(arrVal2);

	const auto& arr1Type = arrVal1.Type();
	const auto& arr2Type = arrVal2.Type();
	if (arr1Type != arr2Type)
	{
		std::stringstream error;
		error << "Cannot find dot product of an array of type " << arr1Type << " and an array of type " << arr2Type;
		throw std::runtime_error(error.str());
	}

	const auto arr1Len = arrVal1.Length();
	const auto arr2Len = arrVal2.Length();

	if (arr1Len != arr2Len)
	{
		std::stringstream error;
		error << "Cannot find dot product of an array of size " << arr1Len << " and an array of size " << arr2Len;
		throw std::runtime_error(error.str());
	}
#endif

	auto res = arrVal1[0] * arrVal2[0];

	for (size_t i = 1; i < arrVal1.Length(); ++i)
	{
		res = res + arrVal1[i] * arrVal2[i];
	}

	aCtx.push(res);
}

// Запись элемента в массив.
void arrayFromFile(SExecutionContext & aCtx)
{
	const auto& arrVal = aCtx.getArg(0);
	const auto& fileVal = aCtx.getArg(1);

#if fptlDebugBuild
	ArrayOps::ValueCheck(arrVal);
	StringOps::ValueCheck(fileVal);
#endif

	const auto fileName = fileVal.ToString();
	auto res = arrVal.Copy();

	std::ifstream input(fileName);
	if (input.is_open())
	{
		res.Read(static_cast<std::istream&>(input));
		aCtx.push(res);
	}
	else
	{
		aCtx.push(BaseOps::Create());
	}
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
	{"arrayCat", &ArrayConcat},
	{"ArrayDot", &ArrayDot},
	{"arrayFromFile", &arrayFromFile}
};

StandardLibrary::StandardLibrary() : FunctionLibrary("StdLib")
{
	addFunctions(mFunctions);
}

}} // FPTL::Runtime
