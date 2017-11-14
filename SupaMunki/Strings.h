#pragma once

#include <string>
#include <vector>
#include <objbase.h>
#include <vector>


#define MAX_RAW_STRING 256


class Strings
{
public:
	static char* WstringToPChar(std::wstring strString, OUT char* result);
	static HRESULT Strings::WstringToBstr(std::wstring strString, OUT BSTR* pbstrResult);
	static std::vector<std::wstring> Strings::Split(const std::wstring& text, const std::wstring& delims);
	static std::wstring Strings::VariantArrayToString(const VARIANT *pSafeArray);
	static std::vector<std::wstring> Strings::VariantToStrVector(const VARIANT *pVar);

	template<typename... Args>
	static std::wstring GetIds(const int& ids, const Args&...);

	template<typename T>
	static std::wstring Format(const T& t);

	template<typename First, typename... Rest>
	static std::wstring Format(const First& first, const Rest&... rest);

	template <typename T>
	static T FromString(const std::wstring& str);
};
