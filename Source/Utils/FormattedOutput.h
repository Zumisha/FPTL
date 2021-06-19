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
		class FormattedOutput
		{
		private:
			bool isEnabled;
			std::string Set(const std::string& atr) const { return isEnabled ? ("\033[" + atr + "m") : ""; }

		public:
			FormattedOutput() : isEnabled(false) {}
			FormattedOutput(bool state) : isEnabled(state)
			{
#ifdef _WIN32
				HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
				DWORD dwMode;

				if (state)
				{
					GetConsoleMode(hOutput, &dwMode);
					dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
					if (!SetConsoleMode(hOutput, dwMode)) 
					{
						isEnabled = false;
						std::cout << "Error when enable ansi support!" << std::endl << std::endl;
					}
				}
#endif
			}

			void enable() { isEnabled = true; }
			void disable() { isEnabled = false; }

			std::string Bold(const std::string& text) const { return Set("1") + text + Set("22"); }
			std::string Underlined(const std::string& text) const { return Set("4") + text + Set("24"); }
			std::string Reverse(const std::string& text) const { return Set("7") + text + Set("27"); }

			std::string Black(const std::string& text) const { return Set("30") + text + Set("39"); }
			std::string Red(const std::string& text) const { return Set("31") + text + Set("39"); }
			std::string Green(const std::string& text) const { return Set("32") + text + Set("39"); }
			std::string Yellow(const std::string& text) const { return Set("33") + text + Set("39"); }
			std::string Blue(const std::string& text) const { return Set("34") + text + Set("39"); }
			std::string Magenta(const std::string& text) const { return Set("35") + text + Set("39"); }
			std::string Cyan(const std::string& text) const { return Set("36") + text + Set("39"); }
			std::string White(const std::string& text) const { return Set("37") + text + Set("39"); }

			std::string BackBlack(const std::string& text) const { return Set("40") + text + Set("49"); }
			std::string BackRed(const std::string& text) const { return Set("41") + text + Set("49"); }
			std::string BackGreen(const std::string& text) const { return Set("42") + text + Set("49"); }
			std::string BackYellow(const std::string& text) const { return Set("43") + text + Set("49"); }
			std::string BackBlue(const std::string& text) const { return Set("44") + text + Set("49"); }
			std::string BackMagenta(const std::string& text) const { return Set("45") + text + Set("49"); }
			std::string BackCyan(const std::string& text) const { return Set("46") + text + Set("49"); }
			std::string BackWhite(const std::string& text) const { return Set("47") + text + Set("49"); }

			// Unsupported
			/*
			static std::string Dim(std::string text) { return Set("2") + text + Set("22"); }
			static std::string Italic(std::string text) { return Set("3") + text + Set("23"); }
			static std::string Blink(std::string text) { return Set("5") + text + Set("25"); }
			static std::string FastBlink(std::string text) { return Set("6") + text + Set("25"); }
			static std::string Hidden(std::string text) { return Set("8") + text + Set("28"); }
			static std::string Crossed(std::string text) { return Set("9") + text + Set("29"); }
			static std::string Framed(std::string text) { return Set("51") + text + Set("54"); }
			static std::string Surrounded(std::string text) { return Set("52") + text + Set("54"); }
			static std::string Spiked(std::string text) { return Set("53") + text + Set("55"); }
			*/
		};
	}
}
