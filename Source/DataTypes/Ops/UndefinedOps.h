#pragma once

#include <ostream>

namespace FPTL
{
	namespace Runtime
	{
		namespace
		{
			const std::string typeName = "Undefined";
			const std::string& getTypeName(void*)
			{
				return typeName;
			}

			// Вывод в поток.
			void print(void*, std::ostream & aStream)
			{
				aStream << typeName;
			}
			
			void rawPrint(void*, std::ostream & aStream)
			{
				aStream << typeName;
			}
		}

		
	}
}
