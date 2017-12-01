#include "stdafx.h"
#include "Exceptions.h"
#include "Strings.h"


PropertyNotSupportedException::PropertyNotSupportedException(std::wstring argument)
{
	m_strArgument = argument;
}


const char* PropertyNotSupportedException::what() const throw()
{
	char buffer[MAX_PATH] = "";
	return Strings::WstringToPChar(Strings::GetIds(IDS_ERROR_SEARCH_PROPETY_NOT_SUPPORTED, m_strArgument), &buffer[0]);
}


ParsingErrorException::ParsingErrorException(std::wstring argument)
{
	m_strArgument = argument;
}


const char* ParsingErrorException::what() const throw()
{
	char buffer[MAX_PATH] = "";
	return Strings::WstringToPChar(Strings::GetIds(IDS_ERROR_PARSING_PROPERTY_VALUE, m_strArgument), &buffer[0]);
}
