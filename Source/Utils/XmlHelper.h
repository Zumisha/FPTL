#pragma once

#include <string>
#include <fstream>

namespace FPTL
{
	namespace Utils
	{
		static std::string OpenTag(const std::string& name)
		{
			return "<" + name + ">";
		}

		static void OpenTag(std::ostream& output, const std::string& name)
		{
			output << "<" << name << ">";
		}

		static std::string CloseTag(const std::string& name)
		{
			return "</" + name + ">";
		}

		static void CloseTag(std::ostream& output, const std::string& name)
		{
			output << "</" << name << ">";
		}
	}
}