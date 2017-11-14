/////////////////////////////////////////////////////////////////////////////
//
//SearchProperties.h
//Contains the C++ class declarations for implementing the ISearchProperties 
//interface
//


#pragma once
#include    "IRapidFox.h"
#include	<map>


extern long g_nComObjsInUse;


class CSearchProperties :
	public ISearchProperties
{
public:
	// IDispatch
	ITypeInfo* m_pTypeInfo;

	HRESULT __stdcall GetTypeInfoCount(UINT *pctinfo);
	HRESULT __stdcall GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo **pptinfo);
	HRESULT __stdcall GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgdispid);
	HRESULT __stdcall Invoke(DISPID dispidMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS* pdispparams,
		VARIANT* pvarResult,
		EXCEPINFO* pexcepinfo,
		UINT* puArgErr);
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppObj);
	ULONG   __stdcall AddRef();
	ULONG   __stdcall Release();

	//ISearchProperties
	HRESULT __stdcall Add(BSTR key, BSTR value);
	HRESULT __stdcall Count(int *result);
	HRESULT	__stdcall Get(VARIANT *result);

private:
	std::map<std::wstring, std::wstring> m_searchProperties;
	long m_nRefCount;   //for managing the reference count

	HRESULT __stdcall GetTypeInfo();
};