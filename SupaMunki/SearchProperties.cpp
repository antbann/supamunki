///////////////////////////////////////////////////////////////
//
//SearchProperties.cpp
//Contains the method  implementations of the ISearchProperties
//

#include "SearchProperties.h"


HRESULT __stdcall CSearchProperties::Add(BSTR key, BSTR value)
{
	m_searchProperties[key] = value;

	return S_OK;
}


HRESULT __stdcall CSearchProperties::Count(int* result)
{
	*result = m_searchProperties.size();

	return S_OK;
}


HRESULT	__stdcall CSearchProperties::Get(VARIANT *result)
{
	result->byref = &m_searchProperties;

	return S_OK;
}


///////////////////////////////////// IDispatch /////////////////////////////////////

HRESULT __stdcall CSearchProperties::QueryInterface(REFIID riid, void **ppObj)
{
	if ((riid == IID_IUnknown) || (riid == IID_ISearchProperties) || (riid == IID_IDispatch))
	{
		*ppObj = static_cast<CSearchProperties*>(this);
		AddRef();
		return S_OK;
	}

	*ppObj = NULL;
	return E_NOINTERFACE;
}


ULONG   __stdcall CSearchProperties::AddRef()
{
	return InterlockedIncrement(&m_nRefCount);
}


ULONG   __stdcall CSearchProperties::Release()
{
	long nRefCount = 0;

	nRefCount = InterlockedDecrement(&m_nRefCount);

	if (nRefCount == 0) {
		delete this;
	}

	return nRefCount;
}


STDMETHODIMP CSearchProperties::GetTypeInfo()
{
	if (m_pTypeInfo != NULL) return S_OK;

	ITypeLib *typeLib;
	LoadTypeLib(L"IRapidFox.tlb", &typeLib);
	typeLib->GetTypeInfoOfGuid(IID_ISearchProperties, &m_pTypeInfo);

	return S_OK;
}


STDMETHODIMP CSearchProperties::GetTypeInfoCount(UINT* pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}


STDMETHODIMP CSearchProperties::GetTypeInfo(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
{
	if (0 != itinfo)
		return E_INVALIDARG;

	GetTypeInfo();

	(*pptinfo = m_pTypeInfo)->AddRef();
	return S_OK;
}


STDMETHODIMP CSearchProperties::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid)
{
	GetTypeInfo();

	return m_pTypeInfo->GetIDsOfNames(rgszNames, cNames, rgdispid);
}


STDMETHODIMP CSearchProperties::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr)
{
	GetTypeInfo();

	return m_pTypeInfo->Invoke(static_cast<CSearchProperties*>(this), dispidMember, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
}