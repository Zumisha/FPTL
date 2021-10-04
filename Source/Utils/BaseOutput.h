#pragma once

#include <string>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace FPTL
{
	namespace Utils
	{
		class BaseOutput
		{

		public:
			BaseOutput() {}

			std::string Bold(const std::string& text) const { return text; }
			std::string Underlined(const std::string& text) const { return text; }
			std::string Reverse(const std::string& text) const { return text; }

			std::string Black(const std::string& text) const { text; }
			std::string Red(const std::string& text) const { return text; }
			std::string Green(const std::string& text) const { return text; }
			std::string Yellow(const std::string& text) const { return text; }
			std::string Blue(const std::string& text) const { return text; }
			std::string Magenta(const std::string& text) const { return text; }
			std::string Cyan(const std::string& text) const { return text; }
			std::string White(const std::string& text) const { return text; }

			std::string BackBlack(const std::string& text) const { return text; }
			std::string BackRed(const std::string& text) const { return text; }
			std::string BackGreen(const std::string& text) const { return text; }
			std::string BackYellow(const std::string& text) const { return text; }
			std::string BackBlue(const std::string& text) const { return text; }
			std::string BackMagenta(const std::string& text) const { return text; }
			std::string BackCyan(const std::string& text) const { return text; }
			std::string BackWhite(const std::string& text) const { return text; }
		};
	}
}
