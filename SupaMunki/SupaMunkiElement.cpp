// SupaMunkiElement.cpp : Implementation of CSupaMunkiElement

#include "stdafx.h"
#include "SupaMunkiElement.h"
#include "Strings.h"
#include "logger.h"
#include "Condition.h"
#include "PropertyNameValuePair.h"


// CSupaMunkiElement


CSupaMunkiElement::CSupaMunkiElement()
{
	m_pUnkMarshaler = nullptr;
	m_pParent = nullptr;
	m_piuiAutomation = nullptr;
	m_piuiAutomationElement = nullptr;

	LOG_DETAILED << "creating new element";
	auto hr = CoCreateInstance(CLSID_CUIAutomation, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_piuiAutomation));
	if(FAILED(hr))
	{
		LOG_BASIC << Strings::GetIds(IDS_ERROR_UIA_INITIALIZATION);
	}

	LOG_VERBOSE << "m_piuiAutomation=0x" << m_piuiAutomation;
	LOG_DETAILED << "element created, instance address is 0x" << this;
}


CSupaMunkiElement::~CSupaMunkiElement()
{
	m_pUnkMarshaler = nullptr;

	LOG_DETAILED << "destructing element 0x" << this;
	if (m_piuiAutomationElement != nullptr)
	{
		LOG_VERBOSE << "releasing m_piuiAutomationElement=0x" << m_piuiAutomationElement;
		LOG_DETAILED << "m_piuiAutomationElement released, reference count " << m_piuiAutomationElement->Release();
		m_piuiAutomationElement = nullptr;
	}

	if (m_piuiAutomation != nullptr)
	{
		LOG_VERBOSE << "releasing m_piuiAutomation=0x" << m_piuiAutomation;
		LOG_DETAILED << "m_piuiAutomation released, reference count " << m_piuiAutomation->Release();
		m_piuiAutomation = nullptr;
	}

	boost::log::core::get()->remove_all_sinks();
}


STDMETHODIMP CSupaMunkiElement::GetElement(VARIANT arrSpecification, ULONG ulTimeoutMs, ISupaMunkiElement **oResult)
{
	*oResult = nullptr;
	HRESULT hr;

	LOG_GENERAL << "getting element within timeout of " << ulTimeoutMs
		<< "ms with " << Strings::VariantArrayToString(&arrSpecification);

	auto friendlySpec = Strings::VariantToStrVector(&arrSpecification);

	auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(ulTimeoutMs);
	do
	{
		if (arrSpecification.vt == VT_NULL || (arrSpecification.vt != VT_NULL && friendlySpec.size() == 0)) {
			LOG_DETAILED << "getting element from scratch, searching desktop...";
			hr = GetRootElementSafe(&m_piuiAutomationElement);
			if (FAILED(hr)) {
				LOG_BASIC << "cannot get root element from ui automation";
				return int(hr);
			}

			LOG_DETAILED << "root element is 0x" << m_piuiAutomationElement;

			hr = AcquireSupaMunkiInterface(oResult);
			break;
		}

		LOG_DETAILED << "getting element from existing element";

		CCondition condition(m_piuiAutomation);
		hr = condition.CreateFromSpecification(friendlySpec);
		if (FAILED(hr)) {
			LOG_BASIC << "could not create condition with requested properties";
			break;
		}

		ISupaMunkiElement *oParent = nullptr;
		hr = get_Parent(&oParent);
		if (FAILED(hr)) {
			LOG_BASIC << "parent ISupaMunki element is null";
			break;
		}

		auto oParentInstance = static_cast<CSupaMunkiElement*>(oParent);
		IUIAutomationElement* pAutomationElementParent = oParentInstance->m_piuiAutomationElement;
		if (pAutomationElementParent == nullptr) {
			LOG_BASIC << "parent automation element is null";
			break;
		}

		IUIAutomationElement* pFoundElement = nullptr;
		LOG_DETAILED << "finding element with pOverallCondition=0x" << condition.GetAutomationCondition()
			<< " and pAutomationElementParent=0x" << pAutomationElementParent;
		hr = pAutomationElementParent->FindFirst(TreeScope_Children, condition.GetAutomationCondition(), &pFoundElement);
		if (FAILED(hr)) {
			LOG_VERBOSE << "finding element NOT succeeded";
		}

		if (pFoundElement != nullptr) {
			m_piuiAutomationElement = pFoundElement;
			LOG_GENERAL << "element found, 0x" << m_piuiAutomationElement;

			hr = AcquireSupaMunkiInterface(oResult);
			break;
		}
		
		LOG_VERBOSE << "element not found, retrying...";

	} while (*oResult == nullptr && std::chrono::system_clock::now() < timeout);

	if (*oResult == nullptr) {
		LOG_BASIC << "resulting element is null, or timeout has expired";
		return E_FAIL;
	}

	return hr;
}


STDMETHODIMP CSupaMunkiElement::Click()
{
	LOG_BASIC << "invoking click";

	IUIAutomationInvokePattern* pInvokePattern = nullptr;
	HRESULT hr = m_piuiAutomationElement->GetCurrentPatternAs(UIA_InvokePatternId, IID_PPV_ARGS(&pInvokePattern));
	if (FAILED(hr))	{
		LOG_BASIC << "could not get InvokePattern";
		return hr;
	}

	LOG_GENERAL << "HRESULT of pInvokePattern->Invoke() is " << pInvokePattern->Invoke();
	LOG_DETAILED << "releasing invoke pattern, reference count " << pInvokePattern->Release();

	return hr;
}


STDMETHODIMP CSupaMunkiElement::SetIntValue(INT nValue, VARIANT_BOOL* bResult)
{
	LOG_BASIC << "invoking SetIntValue";

	auto strValue = std::to_wstring(nValue);

	BSTR bstrValue;
	HRESULT hr = Strings::WstringToBstr(strValue, &bstrValue);
	if (FAILED(hr)) {
		LOG_BASIC << "failed to convert value " << nValue << " to BSTR";
		return hr;
	}

	return SetStringValue(bstrValue, bResult);
}


STDMETHODIMP CSupaMunkiElement::SetStringValue(BSTR szValue, VARIANT_BOOL* bResult)
{
	LOG_BASIC << "invoking SetStringValue";

	IUIAutomationValuePattern* pValuePattern = nullptr;
	HRESULT hr = m_piuiAutomationElement->GetCurrentPatternAs(UIA_ValuePatternId, IID_PPV_ARGS(&pValuePattern));
	if (FAILED(hr)) {
		LOG_BASIC << "could not get ValuePattern";
		return hr;
	}

	pValuePattern->SetValue(szValue);

	return S_OK;
}


STDMETHODIMP CSupaMunkiElement::SetFocus(VARIANT_BOOL* bResult)
{
	LOG_BASIC << "Setting focus on element " << m_piuiAutomationElement;

	HRESULT hr = m_piuiAutomationElement->SetFocus();
	if (FAILED(hr)) {
		LOG_BASIC << "SetFocus operation failed";
		return false;
	}

	UIA_HWND hwndWindow = NULL;
	hr = m_piuiAutomationElement->get_CurrentNativeWindowHandle(&hwndWindow);
	if (FAILED(hr)) {
		LOG_BASIC << "failed to get window handle from element";
		return false;
	}

	BOOL result = SetForegroundWindow((HWND)hwndWindow);
	if (!result) {
		LOG_BASIC << "SetForegroundWindow operation failed";
		return false;
	}

	return GetForegroundWindow() == hwndWindow;
}


STDMETHODIMP CSupaMunkiElement::WaitProperty(BSTR szPropertyName, VARIANT oValue, ULONG ulTimeoutMs, VARIANT_BOOL* bResult)
{
	*bResult = false;
	HRESULT hr = S_OK;

	VARIANT varResult;
	VariantInit(&varResult);

	auto strValue = oValue.bstrVal;
	LOG_BASIC << "waiting for property " << szPropertyName << " to receive " 
		<< strValue << " value within " << ulTimeoutMs << "ms of timeout";

	CPropertyNameValuePair propertyNameValuePair(szPropertyName, strValue);
	auto propertyId = propertyNameValuePair.GetPropertyId();
	auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(ulTimeoutMs);
	do{
		hr = m_piuiAutomationElement->GetCurrentPropertyValueEx(propertyId, true, &varResult);
		if (FAILED(hr)) {
			LOG_BASIC << "failed to get current property value with propertyId=" << propertyId;
			break;
		}

		auto langid = GetSystemDefaultUILanguage();
		auto lcid = MAKELCID(langid, SORT_DEFAULT);
	
		if (VarCmp(&oValue, &varResult, lcid, NORM_IGNORECASE) == VARCMP_EQ) {
			*bResult = true;
			break;
		}
	} while (std::chrono::system_clock::now() < timeout);

	if (!*bResult) {
		LOG_BASIC << "result is false: " 
			<< (std::chrono::system_clock::now() >= timeout) ? ", timeout expired" : "timeout not expired";
		hr = E_FAIL;
	}

	VariantClear(&varResult);
	return hr;
}


STDMETHODIMP CSupaMunkiElement::Expand(VARIANT_BOOL bExpand)
{
	LOG_BASIC << "invoking Expand";

	IUIAutomationExpandCollapsePattern* pExpandCollapsePattern = nullptr;
	HRESULT hr = m_piuiAutomationElement->GetCurrentPatternAs(UIA_ExpandCollapsePatternId, 
		IID_PPV_ARGS(&pExpandCollapsePattern));
	if (FAILED(hr)) {
		LOG_BASIC << "could not get ExpandCollapsePattern";
		return hr;
	}

	ExpandCollapseState state;
	hr = pExpandCollapsePattern->get_CurrentExpandCollapseState(&state);
	if (FAILED(hr)) {
		LOG_BASIC << "could not get expand/collapse current state";
		return hr;
	}

	switch (state) {
	case ExpandCollapseState_Collapsed:
		if (bExpand) {
			pExpandCollapsePattern->Expand();
		}
		else {
			LOG_DETAILED << "element is collapsed, and was specified to collapse - nothing to do";
		}
		break;
	case ExpandCollapseState_Expanded:
		if (bExpand) {
			LOG_DETAILED << "element is expanded, and was specified to expand - nothing to do";
		}
		else {
			pExpandCollapsePattern->Collapse();
		}
		break;
	case ExpandCollapseState_LeafNode:
		LOG_DETAILED << "element is not expandable";
		return E_FAIL;
	}

	return S_OK;
}


STDMETHODIMP CSupaMunkiElement::ContextMenu(BSTR szMenuItem, VARIANT vSubmenuItems)
{
	// TODO: Add your implementation code here

	return E_NOTIMPL;
}


STDMETHODIMP CSupaMunkiElement::GetStringValue(BSTR *bResult)
{
	HRESULT hr = E_FAIL;

	LOG_BASIC << "invoking GetStringValue";

	_variant_t varResult;
	VariantInit(&varResult);

	try {
		CPropertyNameValuePair propertyNameValuePair(L"Value.Value", L"");
		auto propertyId = propertyNameValuePair.GetPropertyId();

		LOG_DETAILED << "getting property with id=" << propertyId;
		auto hr = m_piuiAutomationElement->GetCurrentPropertyValueEx(propertyId, true, &varResult);

		_bstr_t bstrtResult = (_bstr_t)varResult;

		LOG_VERBOSE << "bstrtResult=" << bstrtResult;
		*bResult = SysAllocString(bstrtResult);

		hr = S_OK;
	} catch (const _com_error& err) {
		LOG_BASIC << "could not parse property value as string: " << err.Description();
	}

	VariantClear(&varResult);

	return hr;
}


STDMETHODIMP CSupaMunkiElement::get_Parent(ISupaMunkiElement** pVal)
{
	*pVal = m_pParent;

	return S_OK;
}


STDMETHODIMP CSupaMunkiElement::put_Parent(ISupaMunkiElement* newVal)
{
	m_pParent = newVal;

	return S_OK;
}


// ------------ private methods ------------



STDMETHODIMP CSupaMunkiElement::AcquireSupaMunkiInterface(ISupaMunkiElement **oResult)
{
	HRESULT hr = QueryInterface(IID_PPV_ARGS(oResult));
	if (FAILED(hr)) {
		LOG_BASIC << "call to QueryInterface for " << oResult << " failed";
		return int(hr);
	}

	hr = put_Parent(*oResult);
	if (FAILED(hr)) {
		LOG_BASIC << "failed to write parent " << *oResult;
	}

	LOG_DETAILED << "interface successfully acquired, 0x" << *oResult;

	return hr;
}


STDMETHODIMP CSupaMunkiElement::GetRootElementSafe(IUIAutomationElement **oResult)
{
	IUIAutomation *pAutomation = nullptr;
	IUIAutomationElement *pRoot = nullptr;
	*oResult = nullptr;

	HRESULT hr = CoCreateInstance(CLSID_CUIAutomation, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pAutomation));
	if (SUCCEEDED(hr)) {
		hr = pAutomation->GetRootElement(&pRoot);
		pAutomation->Release();
		if (SUCCEEDED(hr)) {
			*oResult = pRoot;
		}
	}

	LOG_VERBOSE << "GetRootElementSafe: HRESULT=" << hr << ", oResult=0x" << *oResult;

	return hr;
}