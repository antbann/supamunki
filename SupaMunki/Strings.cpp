#include <algorithm>
#include <sstream>
#include "logger.h"
#include <memory>
#include <atlconv.h>
#include <oleauto.h>
#include "Exceptions.h"
#include "Strings.h"


char* Strings::WstringToPChar(std::wstring strString, OUT char* result)
{
	auto outputSize = strString.length() + 1; // +1 for null terminator
	size_t charsConverted = 0;
	auto inputW = strString.c_str();
	wcstombs_s(&charsConverted, result, outputSize, inputW, strString.length());

	return result;
}


HRESULT Strings::WstringToBstr(std::wstring strString, OUT BSTR* pbstrResult)
{
	*pbstrResult = SysAllocStringLen(strString.data(), strString.size());

	if (pbstrResult == nullptr)
	{
		LOG_BASIC << "WstringToBstr: out of memory, string=" << strString;
		return E_OUTOFMEMORY;
	}

	return S_OK;
}


std::vector<std::wstring> Strings::Split(const std::wstring& text, const std::wstring& delims)
{
	std::vector<std::wstring> tokens;
	size_t start = text.find_first_not_of(delims), end;

	while ((end = text.find_first_of(delims, start)) != std::wstring::npos)
	{
		tokens.push_back(text.substr(start, end - start));
		start = text.find_first_not_of(delims, end);
	}

	if (start != std::wstring::npos)
		tokens.push_back(text.substr(start));

	return tokens;
}


std::wstring Strings::VariantArrayToString(const VARIANT *pVar)
{
	if (pVar == nullptr || pVar->parray == nullptr) {
		return L"";
	}

	auto arrVector = VariantToStrVector(pVar);

	std::wstring result;
	for (auto const& value : arrVector)
	{
		result = result + value + L" ";
	}

	return result;
}


std::vector<std::wstring> Strings::VariantToStrVector(const VARIANT *pVar)
{
	std::vector<std::wstring> result;

	LOG_VERBOSE << "marshalling is " << pVar->vt;

	switch (pVar->vt) {

		case VT_DISPATCH:
			{
				if (pVar->pdispVal == nullptr) {
					break;
				}

				IDispatch *pDisp = pVar->pdispVal;
				pDisp->AddRef();

				DISPPARAMS dispparamsNoArgs = { NULL, NULL, 0, 0 };

				VARIANT var;
				VariantInit(&var);

				HRESULT hr = pDisp->Invoke(DISPID_NEWENUM, IID_NULL, GetUserDefaultLCID(),
					DISPATCH_PROPERTYGET, &dispparamsNoArgs, &var, NULL, NULL);
				if (SUCCEEDED(hr)) {
					if (var.vt == VT_UNKNOWN) {

						IEnumVARIANT *pEnum = NULL;
						if SUCCEEDED(var.punkVal->QueryInterface(IID_IEnumVARIANT, (void**)&pEnum)) {

							VARIANT item;
							VariantInit(&item);

							pEnum->Reset();
							while ((pEnum->Next(1, &item, NULL) && S_FALSE) != S_FALSE) {
								if (item.vt == VT_BSTR) {
									result.push_back(item.bstrVal);
								}
								VariantClear(&item);
							}
							pEnum->Release();
						}
						var.punkVal->Release();
						var.punkVal = nullptr;
					}
				}
				VariantClear(&var);
				pDisp->Release();
			}
			break;

		case VT_ARRAY | VT_BSTR:
		case VT_ARRAY | VT_VARIANT:
			{
				auto size = pVar->parray->rgsabound->cElements;

				for (ULONG i = 0; i < size; i++) {
					std::wstring nextValue = static_cast<BSTR*>(pVar->parray->pvData)[i];
					result.push_back(nextValue);
				}
			}
			break;

		case VT_BYREF | VT_VARIANT:
			{
				if (pVar == nullptr || pVar->parray == nullptr || pVar->pvarVal == nullptr) {
					break;
				}

				SAFEARRAY* saValues = pVar->pvarVal->parray;
				BSTR HUGEP* pRawVals;
				HRESULT hr = SafeArrayAccessData(saValues, (void HUGEP**)&pRawVals);
				if (SUCCEEDED(hr))
				{
					VARIANT* pVals = reinterpret_cast<VARIANT*>(pRawVals);

					long lowerBound, upperBound;
					SafeArrayGetLBound(saValues, 1, &lowerBound);
					SafeArrayGetUBound(saValues, 1, &upperBound);

					long cnt_elements = upperBound - lowerBound + 1;
					for (int i = 0; i < cnt_elements; ++i)
					{
						result.push_back(pVals[i].bstrVal);
					}

					SafeArrayUnaccessData(saValues);
				}
			}
			break;

		case VT_EMPTY:
		case VT_NULL:
			LOG_VERBOSE << "empty variant specified";
			break;

		default:
			LOG_BASIC << "unsupported marshalling for specification converter: " + pVar->vt;
	}

	return result;
}


template<typename... Args>
std::wstring Strings::GetIds(const int& ids, const Args&... args)
{
	TCHAR szBuffer[MAX_PATH];

	auto hInst = ::GetModuleHandle(L"SupaMunki.dll");
	auto loaded = ::LoadString(hInst, ids, szBuffer, sizeof(szBuffer) / sizeof(TCHAR));
	if (!loaded) {
		LOG_BASIC << "failed to load resource " + ids << ", GetLastError=" << ::GetLastError();
	}

	return Format(szBuffer, args...);
}

template std::wstring Strings::GetIds(const int&);
template std::wstring Strings::GetIds<std::wstring>(const int&, const std::wstring&);
template std::wstring Strings::GetIds<std::wstring, std::wstring>(const int&, const std::wstring&, const std::wstring&);


template<typename T>
static std::wstring Strings::Format(const T& t)
{
	std::basic_stringstream<wchar_t> stream(t);
	
	return stream.str();
}

template<typename First, typename... Rest>
static std::wstring Strings::Format(const First& first, const Rest&... rest)
{
	return Format(rest...);
}

template std::wstring Strings::Format<int>(const int&);
template std::wstring Strings::Format<int, std::wstring>(const int&, const std::wstring&);
template std::wstring Strings::Format<int, std::wstring, std::wstring>(const int&, const std::wstring&, const std::wstring&);


// ----------------- private methods ----------------
template <typename T>
T Strings::FromString(const std::wstring& str)
{
	std::basic_stringstream<wchar_t> stream(str);
	T res;
	return !(stream >> res) ? 0 : res;
}

template long Strings::FromString<long>(const std::wstring&);
template int Strings::FromString<int>(const std::wstring&);

template <>
bool Strings::FromString<bool>(const std::wstring& strString)
{
	std::wstring lower(strString);
	transform(lower.begin(), lower.end(), lower.begin(), tolower);

	if (lower == L"false")
	{
		return false;
	}
	if (lower == L"true")
	{
		return true;
	}

	LOG_BASIC << "value specified is not convertable to boolean: " << strString;
	return false;
}
