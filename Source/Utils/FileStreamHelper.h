#pragma once

#include <string>
#include <fstream>
#include <experimental/filesystem>

namespace FPTL
{
	namespace Utils
	{
		static void setPermissions(const std::string& fName)
		{
			if (std::experimental::filesystem::exists(std::experimental::filesystem::status(fName)))
			{
				std::experimental::filesystem::permissions(fName,
					std::experimental::filesystem::perms::add_perms | std::experimental::filesystem::perms::owner_all | std::experimental::filesystem::perms::group_all);
			}
		}

		static std::string getfStreamError(std::fstream& input)
		{
			std::string errMsg;
			if (!input.is_open())
			{
				const size_t error_len = 1024;
				char error_buf[error_len];
				strerror_s(error_buf, error_len, errno);
				errMsg = error_buf;
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
