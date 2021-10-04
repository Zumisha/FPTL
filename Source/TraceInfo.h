#pragma once

struct TraceInfo
{
	const std::string operationName;
	
	const std::pair<size_t, size_t> codePos;

	// ��������� ������� ����������.
	const size_t argPos;

	// ���������� ���������� �� ������� �������.
	const size_t argNum;
};
