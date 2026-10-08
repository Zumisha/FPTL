#include "File.h"

File::File(const char* path)
{
	file = fopen(path, "r");

	if (file == nullptr) {
		fprintf(stderr, "Error: %s: file not found\n", path);
		return;
	}
}

File::File(File&& other) noexcept
{
	std::swap(other.file, file);
	std::swap(other.position, position);
}

File& File::operator=(File&& other)
{
	if (this != &other)
	{
		close();
		std::swap(other.file, file);
		std::swap(other.position, position);
	}

	return *this;
}

#if defined(_WIN32) || defined(_WIN64)
#define portable_fseek _fseeki64
#define portable_ftell _ftelli64
#else
#define portable_fseek fseeko
#define portable_ftell ftello
#endif

size_t File::getFileSize() const
{
	const auto currentPos = portable_ftell(file);
	portable_fseek(file, 0, SEEK_END);
	const auto fileSize = portable_ftell(file);
	portable_fseek(file, currentPos, SEEK_SET);
	return static_cast<size_t>(fileSize);
}

const char* File::getNextStringToken()
{
	buffer.clear();
	while (true)
	{
		const int ch = getNextChar();
		position++;

		if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == -1) break;
		buffer.push_back(ch);
	}

	if (!buffer.empty())
	{
		return buffer.data();
	}
	return nullptr;
}
