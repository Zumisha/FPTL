#pragma once

#include <string>
#include <fstream>

namespace FPTL
{
	namespace Utils
	{
		static void setPermissions(const std::string& fName)
		{
			if (std::filesystem::exists(fName))
			{
				std::filesystem::permissions(
					fName,
					std::filesystem::perms::owner_all | std::filesystem::perms::group_all,
					std::filesystem::perm_options::add
				);
			}
		}

		static std::string getfStreamError(std::fstream& input)
		{
			std::string errMsg;
			if (!input.is_open())
			{
				errMsg = std::system_category().message(errno);
			}
			else
			{
				if (input.bad())
					errMsg = "error while reading file";
				else if (input.fail())
					errMsg = "characters extracted could not be interpreted as a valid value of the appropriate type";
				input.close();
			}
			return errMsg;
		}
	}
}
