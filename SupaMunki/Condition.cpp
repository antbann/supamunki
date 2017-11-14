#include "logger.h"
#include "Strings.h"
#include "resource.h"
#include "Condition.h"


CCondition::CCondition(IUIAutomation *puiAutomation)
{
	LOG_DETAILED << "creating CCondition with puiAutomation=0x" << puiAutomation;

	m_puiAutomation = puiAutomation;
	m_puiAutomationCondition = nullptr;
	m_pvConditions = new std::vector<IUIAutomationCondition*>;
}


CCondition::~CCondition()
{
	LOG_DETAILED << "destroying CCondition with puiAutomation=0x" << m_puiAutomation;

	if (m_pvConditions != nullptr) {
		LOG_VERBOSE << "m_pvConditions != nullptr, m_pvConditions=0x" << m_pvConditions;
		ClearPreviousConditions();
		delete m_pvConditions;
	}
}


IUIAutomationCondition *CCondition::GetAutomationCondition()
{
	return m_puiAutomationCondition;
}


STDMETHODIMP CCondition::CreateFromSpecification(std::vector<std::wstring> vSpecification)
{
	HRESULT hr;

	ClearPreviousConditions();

	IUIAutomationCondition *pCondition = nullptr;
	for (auto const& value : vSpecification)
	{
		LOG_VERBOSE << "raw search conditions string: " << value;

		auto str = Strings::Split(value, Strings::GetIds(IDS_SPECIFICATION_SEPARATOR));

		LOG_DETAILED << "condition for search, property=" << str[0] << ", value=" << str[1];

		hr = GetCondition(str[0], str[1], &pCondition);
		if (FAILED(hr)) {
			LOG_BASIC << "could not get condition with " << str[0] << ", " << str[1];
		}

		LOG_VERBOSE << "acquired intermediate condition 0x" << pCondition;

		m_pvConditions->push_back(pCondition);
	}

	hr = m_puiAutomation->CreateAndConditionFromNativeArray(m_pvConditions->data(), m_pvConditions->size(), &m_puiAutomationCondition);
	LOG_DETAILED << "acquired final condition for search at 0x" << m_puiAutomationCondition;

	return hr;
}


STDMETHODIMP CCondition::GetCondition(std::wstring sName, std::wstring sValue, IUIAutomationCondition** ppCondition)
{
	VARIANT varValue = { 0 };
	BSTR bstrValue;
	Strings::WstringToBstr(sValue, &bstrValue);
	HRESULT hr;

	PROPERTYID propertyId;
	if (sName == L"ControlType")
	{
		propertyId = UIA_ControlTypePropertyId;
		varValue.vt = VT_I4;
		hr = UiaControlTypeFromStr(sValue, &varValue.intVal);
	}
	else if (sName == L"ClassName")
	{
		propertyId = UIA_ClassNamePropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"Name")
	{
		propertyId = UIA_NamePropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"AutomationId")
	{
		propertyId = UIA_AutomationIdPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"AcceleratorKey")
	{
		propertyId = UIA_AcceleratorKeyPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"AccessKey")
	{
		propertyId = UIA_AccessKeyPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"Culture")
	{
		propertyId = UIA_CulturePropertyId;
		varValue.vt = VT_I4;
		varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"FrameworkId")
	{
		propertyId = UIA_FrameworkIdPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"HasKeyboardFocus")
	{
		propertyId = UIA_HasKeyboardFocusPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"HelpText")
	{
		propertyId = UIA_HelpTextPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"IsContentElement")
	{
		propertyId = UIA_IsContentElementPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsControlElement")
	{
		propertyId = UIA_IsControlElementPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsDockPatternAvailable")
	{
		propertyId = UIA_IsDockPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsEnabled")
	{
		propertyId = UIA_IsEnabledPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsExpandCollapsePatternAvailable")
	{
		propertyId = UIA_IsExpandCollapsePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsGridItemPatternAvailable")
	{
		propertyId = UIA_IsGridItemPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsGridPatternAvailable")
	{
		propertyId = UIA_IsGridPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsInvokePatternAvailable")
	{
		propertyId = UIA_IsInvokePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsKeyboardFocusable")
	{
		propertyId = UIA_IsKeyboardFocusablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsMultipleViewPatternAvailable")
	{
		propertyId = UIA_IsMultipleViewPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsOffscreen")
	{
		propertyId = UIA_IsOffscreenPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsPassword")
	{
		propertyId = UIA_IsPasswordPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsRangeValuePatternAvailable")
	{
		propertyId = UIA_IsRangeValuePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsRequiredForForm")
	{
		propertyId = UIA_IsRequiredForFormPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsScrollItemPatternAvailable")
	{
		propertyId = UIA_IsScrollItemPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsScrollPatternAvailable")
	{
		propertyId = UIA_IsScrollPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSelectionItemPatternAvailable")
	{
		propertyId = UIA_IsSelectionItemPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSelectionPatternAvailable")
	{
		propertyId = UIA_IsSelectionPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTableItemPatternAvailable")
	{
		propertyId = UIA_IsTableItemPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTablePatternAvailable")
	{
		propertyId = UIA_IsTablePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTextPatternAvailable")
	{
		propertyId = UIA_IsTextPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTogglePatternAvailable")
	{
		propertyId = UIA_IsTogglePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTransformPatternAvailable")
	{
		propertyId = UIA_IsTransformPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsValuePatternAvailable")
	{
		propertyId = UIA_IsValuePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsWindowPatternAvailable")
	{
		propertyId = UIA_IsWindowPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"ItemStatus")
	{
		propertyId = UIA_ItemStatusPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"ItemType")
	{
		propertyId = UIA_ItemTypePropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"LocalizedControlType")
	{
		propertyId = UIA_LocalizedControlTypePropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"NativeWindowHandle")
	{
		propertyId = UIA_NativeWindowHandlePropertyId;
		varValue.vt = VT_I4;
		varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"Orientation")
	{
		propertyId = UIA_OrientationPropertyId;
		varValue.vt = VT_I4;
		varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"ProcessId")
	{
		propertyId = UIA_ProcessIdPropertyId;
		varValue.vt = VT_I4;
		varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"IsLegacyIAccessiblePatternAvailable")
	{
		propertyId = UIA_IsLegacyIAccessiblePatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsItemContainerPatternAvailable")
	{
		propertyId = UIA_IsItemContainerPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsVirtualizedItemPatternAvailable")
	{
		propertyId = UIA_IsVirtualizedItemPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSynchronizedInputPatternAvailable")
	{
		propertyId = UIA_IsSynchronizedInputPatternAvailablePropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"AriaRole")
	{
		propertyId = UIA_AriaRolePropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"AriaProperties")
	{
		propertyId = UIA_AriaPropertiesPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else if (sName == L"IsDataValidForForm")
	{
		propertyId = UIA_IsDataValidForFormPropertyId;
		varValue.vt = VT_BOOL;
		varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"ProviderDescription")
	{
		propertyId = UIA_ProviderDescriptionPropertyId;
		varValue.vt = VT_BSTR;
		varValue.bstrVal = bstrValue;
	}
	else
	{
		LOG_BASIC << "condition not supported: " << sName;
		SysFreeString(bstrValue);
		bstrValue = nullptr;
		return E_NOTIMPL;
	}

	LOG_DETAILED << "creating proprety condition with propertyId=" << propertyId << " and varValue=" << bstrValue;
	hr = m_puiAutomation->CreatePropertyConditionEx(propertyId, varValue,
		PropertyConditionFlags_IgnoreCase, ppCondition);

	LOG_DETAILED << "created proprety condition 0x" << *ppCondition << ", HRESULT=" << hr;

	// free allocated resources
	SysFreeString(bstrValue);
	bstrValue = nullptr;
	return hr;
}


STDMETHODIMP CCondition::UiaControlTypeFromStr(std::wstring strValue, PINT pnResult)
{
	if (strValue == L"Button") *pnResult = UIA_ButtonControlTypeId;
	if (strValue == L"Calendar") *pnResult = UIA_CalendarControlTypeId;
	if (strValue == L"CheckBox") *pnResult = UIA_CheckBoxControlTypeId;
	if (strValue == L"ComboBox") *pnResult = UIA_ComboBoxControlTypeId;
	if (strValue == L"Custom") *pnResult = UIA_CustomControlTypeId;
	if (strValue == L"DataGrid") *pnResult = UIA_DataGridControlTypeId;
	if (strValue == L"DataItem") *pnResult = UIA_DataItemControlTypeId;
	if (strValue == L"Document") *pnResult = UIA_DocumentControlTypeId;
	if (strValue == L"Edit") *pnResult = UIA_EditControlTypeId;
	if (strValue == L"Group") *pnResult = UIA_GroupControlTypeId;
	if (strValue == L"Header") *pnResult = UIA_HeaderControlTypeId;
	if (strValue == L"HeaderItem") *pnResult = UIA_HeaderItemControlTypeId;
	if (strValue == L"Hyperlink") *pnResult = UIA_HyperlinkControlTypeId;
	if (strValue == L"Image") *pnResult = UIA_ImageControlTypeId;
	if (strValue == L"List") *pnResult = UIA_ListControlTypeId;
	if (strValue == L"ListItem") *pnResult = UIA_ListItemControlTypeId;
	if (strValue == L"MenuBar") *pnResult = UIA_MenuBarControlTypeId;
	if (strValue == L"Menu") *pnResult = UIA_MenuControlTypeId;
	if (strValue == L"MenuItem") *pnResult = UIA_MenuItemControlTypeId;
	if (strValue == L"Pane") *pnResult = UIA_PaneControlTypeId;
	if (strValue == L"ProgressBar") *pnResult = UIA_ProgressBarControlTypeId;
	if (strValue == L"RadioButton") *pnResult = UIA_RadioButtonControlTypeId;
	if (strValue == L"ScrollBar") *pnResult = UIA_ScrollBarControlTypeId;
	if (strValue == L"Separator") *pnResult = UIA_SeparatorControlTypeId;
	if (strValue == L"Slider") *pnResult = UIA_SliderControlTypeId;
	if (strValue == L"Spinner") *pnResult = UIA_SpinnerControlTypeId;
	if (strValue == L"SplitButton") *pnResult = UIA_SplitButtonControlTypeId;
	if (strValue == L"StatusBar") *pnResult = UIA_StatusBarControlTypeId;
	if (strValue == L"Tab") *pnResult = UIA_TabControlTypeId;
	if (strValue == L"TabItem") *pnResult = UIA_TabItemControlTypeId;
	if (strValue == L"Table") *pnResult = UIA_TableControlTypeId;
	if (strValue == L"Text") *pnResult = UIA_TextControlTypeId;
	if (strValue == L"Thumb") *pnResult = UIA_ThumbControlTypeId;
	if (strValue == L"TitleBar") *pnResult = UIA_TitleBarControlTypeId;
	if (strValue == L"ToolBar") *pnResult = UIA_ToolBarControlTypeId;
	if (strValue == L"ToolTip") *pnResult = UIA_ToolTipControlTypeId;
	if (strValue == L"Tree") *pnResult = UIA_TreeControlTypeId;
	if (strValue == L"TreeItem") *pnResult = UIA_TreeItemControlTypeId;
	if (strValue == L"Window") *pnResult = UIA_WindowControlTypeId;

	if (*pnResult == 0) {
		LOG_BASIC << "invalid control type specified: " << strValue;
		return E_INVALIDARG;
	}

	LOG_DETAILED << "UIA type from " << strValue << " returned " << pnResult;

	return S_OK;
}


STDMETHODIMP CCondition::ClearPreviousConditions()
{
	LOG_DETAILED << "clearing previous conditions";

	if (m_puiAutomationCondition != nullptr) {
		LOG_VERBOSE << "releasing m_puiAutomationCondition at 0x" << m_puiAutomationCondition
			<< ", reference count " << m_puiAutomationCondition->Release();

		m_puiAutomationCondition = nullptr;
	}

	LOG_VERBOSE << "found " << m_pvConditions->size() << " intermediate condition(s)";
	for (auto it = m_pvConditions->begin(); it != m_pvConditions->end(); ++it)
	{
		auto currentCondition = *it;
		LOG_VERBOSE << "released intermediate condition 0x" << currentCondition
			<< ", reference count " << currentCondition->Release();
	}

	m_pvConditions->clear();

	return S_OK;
}