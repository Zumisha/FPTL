#include <string>

namespace Utils {
	static class ColoredOutput
	{
	private:
		static std::string Set(std::string atr) { return "\033[" + atr + "m"; }

	public:
		static std::string Bold(std::string *text) { return Set("1") + *text + Set("21"); }
		static std::string Dim(std::string *text) { return Set("2") + *text + Set("22"); }
		static std::string Underlined(std::string *text) { return Set("4") + *text + Set("24"); }
		static std::string Blink(std::string *text) { return Set("5") + *text + Set("25"); }
		static std::string Reverse(std::string *text) { return Set("7") + *text + Set("27"); }
		static std::string Hidden(std::string *text) { return Set("8") + *text + Set("28"); }

		static std::string Red(std::string *text) { return Set("31") + *text + Set("39"); }
		static std::string Green(std::string *text) { return Set("32") + *text + Set("39"); }
		static std::string Yellow(std::string *text) { return Set("33") + *text + Set("39"); }
		static std::string Blue(std::string *text) { return Set("34") + *text + Set("39"); }
		static std::string Magenta(std::string *text) { return Set("35") + *text + Set("39"); }
		static std::string Cyan(std::string *text) { return Set("36") + *text + Set("39"); }
	};
}