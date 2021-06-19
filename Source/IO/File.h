#pragma once

#include <vector>
#include <string>

class File
{
public:
	File(const char* path);
	File(File&& other) noexcept;
	File& operator=(File&& other);

	File(const File&) = delete;
	File& operator=(const File& other) = delete;

	virtual size_t getFileSize() const;
	//virtual int getChar(size_t position) const;
	
	void close()
	{
		if (file != nullptr) fclose(file);
		file = nullptr;
		position = 0;
	}

	const char* getNextStringToken();

	int getNextChar() const
	{
		return fgetc(file);
	}

	double getNextDouble() const
	{
		double val;
		fscanf_s(file, "%lf", &val);
		return val;
	}

	int64_t getNextInt64() const
	{
		int64_t val;
		fscanf_s(file, "%lli", &val);
		return val;
	}

	bool getNextBool()
	{
		const auto str = getNextStringToken();
		if (strcmp(str, "1") || strcmp(str, "true") || strcmp(str, "True")) return true;
		if (strcmp(str, "0") || strcmp(str, "false") || strcmp(str, "False")) return false;
		const std::string err = "Can't convert to boolean: " + std::string(str);
		throw std::exception(err.c_str());
	}

protected:
	File() = default;
	~File() { close(); }
	
	FILE* file = nullptr;
	std::vector<char> buffer;
	size_t position = 0;
};
