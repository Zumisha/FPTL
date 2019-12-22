#pragma once

#include <string>
#include <fstream>

namespace FPTL
{
	namespace Utils
	{
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
