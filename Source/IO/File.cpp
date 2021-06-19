#include "File.h"

File::File(const char* path)
{
	fopen_s(&file, path, "r");

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

size_t File::getFileSize() const
{
	const int fileDescriptor = _fileno(file);
	_fseeki64(file, 0, SEEK_END);
	const auto fileSize = _ftelli64(file);
	_fseeki64(file, position, SEEK_SET);
	return fileSize;
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
	return "";
}
