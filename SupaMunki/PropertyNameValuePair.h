#pragma once
#include "Strings.h"


using namespace ATL;


class CPropertyNameValuePair
{
public:
	CPropertyNameValuePair(const std::wstring& strName, const std::wstring& strValue);
	~CPropertyNameValuePair();

	const LONG GetPropertyId();
	LPVARIANT GetValueVariant();
	LPBSTR GetValueBstr();
private:
	VARIANT m_varValue;
	BSTR m_bstrValue;
	PROPERTYID m_nPropertyId;

	void Init(const std::wstring& sName, const std::wstring& sValue);
	const LONG UiaControlTypeFromStr(const std::wstring& strValue);
};