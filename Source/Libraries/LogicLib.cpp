#include <regex>

#include "FunctionLibrary.h"
#include "DataTypes/TypedFunction.h"
#include "LogicLib.h"

#include "IO/File.h"

namespace FPTL
{
	namespace Runtime
	{
		namespace {
			
			// Преобразования типов.
			int64_t toInt(const bool& aVal)
			{
				return aVal;
			}

			double toDouble(const bool& aVal)
			{
				return aVal;
			}

			// Функции сравнения. Оба аргумента обязаны быть типа boolean.
			bool equal(const bool& aLhs, const bool& aRhs)
			{
				return aLhs == aRhs;
			}

			// Вывод в поток.
			void print(const bool& aVal, std::ostream & aStream)
			{
				aStream << (aVal ? "true" : "false");
			}

			// Вывод в поток.
			void rawPrint(const bool& aVal, std::ostream & aStream)
			{
				aStream << (aVal ? "1" : "0");
			}

			bool read(File& aFile)
			{
				return aFile.getNextBool();
			}

			bool Not(const bool& aVal)
			{
				return !aVal;
			}

			bool And(const bool& aLeft, const bool& aRight)
			{
				return aLeft && aRight;
			}

			bool Or(const bool& aLeft, const bool& aRight)
			{
				return aLeft || aRight;
			}

			bool Xor(const bool& aLeft, const bool& aRight)
			{
				return aLeft ^ aRight;
			}
		} // anonymous namespace

		void LogicLib::Register()
		{
			FunctionLibrary::addFunction("toInt", TypedFunction(&toInt, false, false));
			FunctionLibrary::addFunction("toDouble", TypedFunction(&toDouble, false, false));
			FunctionLibrary::addFunction("equal", TypedFunction(&equal, false, false));
			FunctionLibrary::addFunction("print", TypedFunction(&print, false, false));
			FunctionLibrary::addFunction("rawPrint", TypedFunction(&rawPrint, false, false));
			FunctionLibrary::addFunction("read", TypedFunction(&read, false, false));
			FunctionLibrary::addFunction("not", TypedFunction(&Not, false, false));
			FunctionLibrary::addFunction("and", TypedFunction(&And, false, false));
			FunctionLibrary::addFunction("or", TypedFunction(&Or, false, false));
			FunctionLibrary::addFunction("xor", TypedFunction(&Xor, false, false));
		}
	}
}
