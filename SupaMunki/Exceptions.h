#pragma once
#include "stdafx.h"


#define MAX_MESSAGE 256


class PropertyNotSupportedException : std::exception
{
public:
	PropertyNotSupportedException()
	{
	}
	explicit PropertyNotSupportedException(std::wstring argument);

	const char* what() const throw() override;
private:
	std::wstring m_strArgument;
};


class ParsingErrorException : std::exception
{
public:
	ParsingErrorException()
	{
	}
	explicit ParsingErrorException(std::wstring argument);

	const char* what() const throw() override;
private:
	std::wstring m_strArgument;
};
