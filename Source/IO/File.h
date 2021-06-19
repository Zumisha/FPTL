#pragma once

#include <string>
#include <vector>

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

	static std::string getNextStringToken();

	int getNextChar()
	{
		return 0;//getChar(position++);
	}
	
	void close()
	{
		if (file != nullptr) fclose(file);
		file = nullptr;
		position = 0;
	}	

protected:
	File() = default;
	~File() { close(); }
	
	FILE* file = nullptr;
	std::vector<char> buffer;
	size_t position = 0;
};
