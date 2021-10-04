#pragma once

struct TraceInfo
{
	const std::string operationName;
	
	const std::pair<size_t, size_t> codePos;

	// Положение кортежа аргументов.
	const size_t argPos;

	// Количество аргументов во входном кортеже.
	const size_t argNum;
};
