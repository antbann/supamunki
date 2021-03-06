#pragma once

#include "stdafx.h"


#define MAX_RAW_STRING 256


namespace fs = boost::filesystem;


class Strings
{
public:
	static char* WstringToPChar(std::wstring strString, OUT char* result);
	static HRESULT Strings::WstringToBstr(std::wstring strString, OUT BSTR* pbstrResult);
	static std::vector<std::wstring> Strings::Split(const std::wstring& text, const std::wstring& delims);
	static std::wstring Strings::VariantArrayToString(const LPVARIANT pSafeArray);
	static std::vector<std::wstring> Strings::VariantToStrVector(const LPVARIANT pVar);
	
	static inline std::wstring Strings::JoinPaths(const std::wstring& path1, const std::wstring& path2) {
		fs::path fsPath1(path1);
		fs::path fsPath2(path2);
		fs::path result = fsPath1 / fsPath2;

		return result.wstring();
	}

	static inline std::wstring Strings::ExtensionFromPath(const std::wstring& path) {
		std::wstring extension = fs::path(path).extension().wstring();
		std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

		return extension;
	}

	static inline std::wstring& Strings::ltrim(std::wstring &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	static inline std::wstring& Strings::rtrim(std::wstring &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	static inline std::wstring& Strings::trim(std::wstring &s) {
		return ltrim(rtrim(s));
	}

	template<typename... Args>
	static std::wstring GetIds(const int& ids, const Args&...);

	template<typename T>
	static std::wstring Format(const T& t);

	template<typename First, typename... Rest>
	static std::wstring Format(const First& first, const Rest&... rest);

	template <typename T>
	static T FromString(const std::wstring& str);
};
