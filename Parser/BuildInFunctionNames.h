// Имена встроенных функций.

#ifndef BUILDINFUNCTIONNAMES_H
#define BUILDINFUNCTIONNAMES_H

namespace FPTL
{
	namespace Parser
	{
		namespace BuildInFunctions
		{
			// Базовые функции.
			const char Id[]             = "id";
			const char Add[]            = "add";
			const char Subtract[]       = "sub";
			const char Multiply[]       = "mul";
			const char Divide[]         = "div";
			const char Modulus[]        = "mod";
			const char Equal[]          = "equal";
			const char NotEqual[]       = "nequal";
			const char Greater[]        = "greater";
			const char Less[]           = "less";
			const char GreaterOrEqual[] = "gequal";
			const char LessOrEqual[]    = "lequal";

			// Матемитические функции.
			const char Sqrt[]           = "sqrt";
			const char Sin[]            = "sin";
			const char Cos[]            = "cos";
			const char Tan[]            = "tan";
			const char Asin[]           = "asin";
			const char Atan[]           = "atan";
			const char Round[]          = "round";
			const char Exp[]            = "exp";
			const char Ln[]             = "ln";
			const char Abs[]            = "abs";
			const char Pi[]             = "pi";
			const char E[]              = "E";

			// Функции работы со строками.
			const char Cat[]            = "cat";
			const char Search[]         = "search";
			const char Match[]          = "match";
			const char Replace[]        = "replace";
			const char GetToken[]       = "getToken";
			const char Length[]         = "length";
			
			// Другие функции.
			const char Rand[]           = "rand";
			const char Print[]          = "print";
			const char PrintType[]      = "printType";

			// Преобразования типов.
			const char toString[]       = "toString";
			const char toInt[]          = "toInt";
			const char toReal[]         = "toReal";
			const char toLongInt[]      = "toLongInt";

			// Операции с файлами.
			const char readFile[]       = "readFile";
		}
	}
}

#endif