// SupaMunkiElement.h : Declaration of the CSupaMunkiElement

#pragma once
#include "stdafx.h"
#include "SupaMunki_i.h"
#include "_ISupaMunkiElementEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CSupaMunkiElement

class ATL_NO_VTABLE CSupaMunkiElement :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CSupaMunkiElement, &CLSID_SupaMunkiElement>,
	public IConnectionPointContainerImpl<CSupaMunkiElement>,
	public CProxy_ISupaMunkiElementEvents<CSupaMunkiElement>,
	public IDispatchImpl<ISupaMunkiElement, &IID_ISupaMunkiElement, &LIBID_SupaMunkiLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSupaMunkiElement();
	~CSupaMunkiElement();

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CSupaMunkiElement)
	COM_INTERFACE_ENTRY(ISupaMunkiElement)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CSupaMunkiElement)
	CONNECTION_POINT_ENTRY(__uuidof(_ISupaMunkiElementEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	HRESULT FinalConstruct()
	{
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;
	

public:

	STDMETHOD(GetElement)(VARIANT arrSpecification, ULONG ulTimeoutMs, ISupaMunkiElement **resultElement);
	STDMETHOD(Click)();
	STDMETHOD(SetIntValue)(INT nValue, VARIANT_BOOL *bResult);
	STDMETHOD(SetStringValue)(BSTR szValue, VARIANT_BOOL *bResult);
	STDMETHOD(SetFocus)(VARIANT_BOOL *bResult);
	STDMETHOD(WaitProperty)(BSTR szPropertyName, VARIANT oValue, ULONG ulTimeoutMs, VARIANT_BOOL *bResult);
	STDMETHOD(Expand)(VARIANT_BOOL bExpand);
	STDMETHOD(get_Parent)(ISupaMunkiElement **pVal);
	STDMETHOD(put_Parent)(ISupaMunkiElement *newVal);
	STDMETHOD(ContextMenu)(BSTR szMenuItem, VARIANT vSubmenuItems);
	STDMETHOD(GetStringValue)(BSTR *bResult);


private:
	IUIAutomation *m_piuiAutomation;
	IUIAutomationElement *m_piuiAutomationElement;
	ISupaMunkiElement *m_pParent;

	STDMETHOD(AcquireSupaMunkiInterface)(ISupaMunkiElement **oResult);
	STDMETHOD(GetRootElementSafe)(IUIAutomationElement **oResult);
};

OBJECT_ENTRY_AUTO(__uuidof(SupaMunkiElement), CSupaMunkiElement)