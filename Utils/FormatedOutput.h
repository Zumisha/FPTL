#pragma once
#include <string>

namespace Utils {
	class FormatedOutput
	{
	private:
		bool isEnabled;
		std::string Set(std::string atr) { return isEnabled ? ("\033[" + atr + "m") : ""; }

	public:
		FormatedOutput() : isEnabled(false) {}
		FormatedOutput(bool state) : isEnabled(state) {}

		void enable() { isEnabled = true; }
		void disable() { isEnabled = false; }

		std::string Bold(std::string text) { return Set("1") + text + Set("22"); }		
		std::string Underlined(std::string text) { return Set("4") + text + Set("24"); }		
		std::string Reverse(std::string text) { return Set("7") + text + Set("27"); }

		std::string Black(std::string text) { return Set("30") + text + Set("39"); }
		std::string Red(std::string text) { return Set("31") + text + Set("39"); }
		std::string Green(std::string text) { return Set("32") + text + Set("39"); }
		std::string Yellow(std::string text) { return Set("33") + text + Set("39"); }
		std::string Blue(std::string text) { return Set("34") + text + Set("39"); }
		std::string Magenta(std::string text) { return Set("35") + text + Set("39"); }
		std::string Cyan(std::string text) { return Set("36") + text + Set("39"); }
		std::string White(std::string text) { return Set("37") + text + Set("39"); }

		std::string BackBlack(std::string text) { return Set("40") + text + Set("49"); }
		std::string BackRed(std::string text) { return Set("41") + text + Set("49"); }
		std::string BackGreen(std::string text) { return Set("42") + text + Set("49"); }
		std::string BackYellow(std::string text) { return Set("43") + text + Set("49"); }
		std::string BackBlue(std::string text) { return Set("44") + text + Set("49"); }
		std::string BackMagenta(std::string text) { return Set("45") + text + Set("49"); }
		std::string BackCyan(std::string text) { return Set("46") + text + Set("49"); }
		std::string BackWhite(std::string text) { return Set("47") + text + Set("49"); }

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
