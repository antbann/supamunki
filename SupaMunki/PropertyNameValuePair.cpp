#include "stdafx.h"
#include "PropertyNameValuePair.h"
#include "logger.h"



CPropertyNameValuePair::CPropertyNameValuePair(const std::wstring& strName, const std::wstring& strValue)
{
	VariantInit(&m_varValue);
	Strings::WstringToBstr(strValue, &m_bstrValue);
	Init(strName, strValue);
}


CPropertyNameValuePair::~CPropertyNameValuePair()
{
	if (m_bstrValue != nullptr) {
		SysFreeString(m_bstrValue);
	}

	VariantClear(&m_varValue);
}


const LONG CPropertyNameValuePair::GetPropertyId()
{
	return m_nPropertyId;
}


LPVARIANT CPropertyNameValuePair::GetValueVariant()
{
	return &m_varValue;
}


LPBSTR CPropertyNameValuePair::GetValueBstr()
{
	return &m_bstrValue;
}


void CPropertyNameValuePair::Init(const std::wstring& sName, const std::wstring& sValue)
{
	if (sName == L"ControlType")
	{
		m_nPropertyId = UIA_ControlTypePropertyId;
		m_varValue.vt = VT_I4;
		m_varValue.intVal = UiaControlTypeFromStr(sValue);
	}
	else if (sName == L"ClassName")
	{
		m_nPropertyId = UIA_ClassNamePropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"Name")
	{
		m_nPropertyId = UIA_NamePropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"AutomationId")
	{
		m_nPropertyId = UIA_AutomationIdPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"AcceleratorKey")
	{
		m_nPropertyId = UIA_AcceleratorKeyPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"AccessKey")
	{
		m_nPropertyId = UIA_AccessKeyPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"Culture")
	{
		m_nPropertyId = UIA_CulturePropertyId;
		m_varValue.vt = VT_I4;
		m_varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"FrameworkId")
	{
		m_nPropertyId = UIA_FrameworkIdPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"HasKeyboardFocus")
	{
		m_nPropertyId = UIA_HasKeyboardFocusPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"HelpText")
	{
		m_nPropertyId = UIA_HelpTextPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"IsContentElement")
	{
		m_nPropertyId = UIA_IsContentElementPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsControlElement")
	{
		m_nPropertyId = UIA_IsControlElementPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsDockPatternAvailable")
	{
		m_nPropertyId = UIA_IsDockPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsEnabled")
	{
		m_nPropertyId = UIA_IsEnabledPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsExpandCollapsePatternAvailable")
	{
		m_nPropertyId = UIA_IsExpandCollapsePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsGridItemPatternAvailable")
	{
		m_nPropertyId = UIA_IsGridItemPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsGridPatternAvailable")
	{
		m_nPropertyId = UIA_IsGridPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsInvokePatternAvailable")
	{
		m_nPropertyId = UIA_IsInvokePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsKeyboardFocusable")
	{
		m_nPropertyId = UIA_IsKeyboardFocusablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsMultipleViewPatternAvailable")
	{
		m_nPropertyId = UIA_IsMultipleViewPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsOffscreen")
	{
		m_nPropertyId = UIA_IsOffscreenPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsPassword")
	{
		m_nPropertyId = UIA_IsPasswordPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsRangeValuePatternAvailable")
	{
		m_nPropertyId = UIA_IsRangeValuePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsRequiredForForm")
	{
		m_nPropertyId = UIA_IsRequiredForFormPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsScrollItemPatternAvailable")
	{
		m_nPropertyId = UIA_IsScrollItemPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsScrollPatternAvailable")
	{
		m_nPropertyId = UIA_IsScrollPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSelectionItemPatternAvailable")
	{
		m_nPropertyId = UIA_IsSelectionItemPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSelectionPatternAvailable")
	{
		m_nPropertyId = UIA_IsSelectionPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTableItemPatternAvailable")
	{
		m_nPropertyId = UIA_IsTableItemPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTablePatternAvailable")
	{
		m_nPropertyId = UIA_IsTablePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTextPatternAvailable")
	{
		m_nPropertyId = UIA_IsTextPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTogglePatternAvailable")
	{
		m_nPropertyId = UIA_IsTogglePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsTransformPatternAvailable")
	{
		m_nPropertyId = UIA_IsTransformPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsValuePatternAvailable")
	{
		m_nPropertyId = UIA_IsValuePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsWindowPatternAvailable")
	{
		m_nPropertyId = UIA_IsWindowPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"ItemStatus")
	{
		m_nPropertyId = UIA_ItemStatusPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"ItemType")
	{
		m_nPropertyId = UIA_ItemTypePropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"LocalizedControlType")
	{
		m_nPropertyId = UIA_LocalizedControlTypePropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"NativeWindowHandle")
	{
		m_nPropertyId = UIA_NativeWindowHandlePropertyId;
		m_varValue.vt = VT_I4;
		m_varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"Orientation")
	{
		m_nPropertyId = UIA_OrientationPropertyId;
		m_varValue.vt = VT_I4;
		m_varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"ProcessId")
	{
		m_nPropertyId = UIA_ProcessIdPropertyId;
		m_varValue.vt = VT_I4;
		m_varValue.intVal = Strings::FromString<int>(sValue);
	}
	else if (sName == L"IsLegacyIAccessiblePatternAvailable")
	{
		m_nPropertyId = UIA_IsLegacyIAccessiblePatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsItemContainerPatternAvailable")
	{
		m_nPropertyId = UIA_IsItemContainerPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsVirtualizedItemPatternAvailable")
	{
		m_nPropertyId = UIA_IsVirtualizedItemPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"IsSynchronizedInputPatternAvailable")
	{
		m_nPropertyId = UIA_IsSynchronizedInputPatternAvailablePropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"AriaRole")
	{
		m_nPropertyId = UIA_AriaRolePropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"AriaProperties")
	{
		m_nPropertyId = UIA_AriaPropertiesPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else if (sName == L"IsDataValidForForm")
	{
		m_nPropertyId = UIA_IsDataValidForFormPropertyId;
		m_varValue.vt = VT_BOOL;
		m_varValue.boolVal = Strings::FromString<bool>(sValue);
	}
	else if (sName == L"ProviderDescription")
	{
		m_nPropertyId = UIA_ProviderDescriptionPropertyId;
		m_varValue.vt = VT_BSTR;
		m_varValue.bstrVal = m_bstrValue;
	}
	else
	{
		LOG_BASIC << "property not supported: " << sName;
	}
}


const LONG CPropertyNameValuePair::UiaControlTypeFromStr(const std::wstring & strValue)
{
	if (strValue == L"Button") return UIA_ButtonControlTypeId;
	if (strValue == L"Calendar") return UIA_CalendarControlTypeId;
	if (strValue == L"CheckBox") return UIA_CheckBoxControlTypeId;
	if (strValue == L"ComboBox") return UIA_ComboBoxControlTypeId;
	if (strValue == L"Custom") return UIA_CustomControlTypeId;
	if (strValue == L"DataGrid") return UIA_DataGridControlTypeId;
	if (strValue == L"DataItem") return UIA_DataItemControlTypeId;
	if (strValue == L"Document") return UIA_DocumentControlTypeId;
	if (strValue == L"Edit") return UIA_EditControlTypeId;
	if (strValue == L"Group") return UIA_GroupControlTypeId;
	if (strValue == L"Header") return UIA_HeaderControlTypeId;
	if (strValue == L"HeaderItem") return UIA_HeaderItemControlTypeId;
	if (strValue == L"Hyperlink") return UIA_HyperlinkControlTypeId;
	if (strValue == L"Image") return UIA_ImageControlTypeId;
	if (strValue == L"List") return UIA_ListControlTypeId;
	if (strValue == L"ListItem") return UIA_ListItemControlTypeId;
	if (strValue == L"MenuBar") return UIA_MenuBarControlTypeId;
	if (strValue == L"Menu") return UIA_MenuControlTypeId;
	if (strValue == L"MenuItem") return UIA_MenuItemControlTypeId;
	if (strValue == L"Pane") return UIA_PaneControlTypeId;
	if (strValue == L"ProgressBar") return UIA_ProgressBarControlTypeId;
	if (strValue == L"RadioButton") return UIA_RadioButtonControlTypeId;
	if (strValue == L"ScrollBar") return UIA_ScrollBarControlTypeId;
	if (strValue == L"Separator") return UIA_SeparatorControlTypeId;
	if (strValue == L"Slider") return UIA_SliderControlTypeId;
	if (strValue == L"Spinner") return UIA_SpinnerControlTypeId;
	if (strValue == L"SplitButton") return UIA_SplitButtonControlTypeId;
	if (strValue == L"StatusBar") return UIA_StatusBarControlTypeId;
	if (strValue == L"Tab") return UIA_TabControlTypeId;
	if (strValue == L"TabItem") return UIA_TabItemControlTypeId;
	if (strValue == L"Table") return UIA_TableControlTypeId;
	if (strValue == L"Text") return UIA_TextControlTypeId;
	if (strValue == L"Thumb") return UIA_ThumbControlTypeId;
	if (strValue == L"TitleBar") return UIA_TitleBarControlTypeId;
	if (strValue == L"ToolBar") return UIA_ToolBarControlTypeId;
	if (strValue == L"ToolTip") return UIA_ToolTipControlTypeId;
	if (strValue == L"Tree") return UIA_TreeControlTypeId;
	if (strValue == L"TreeItem") return UIA_TreeItemControlTypeId;
	if (strValue == L"Window") return UIA_WindowControlTypeId;

	LOG_BASIC << "control type could not be parsed: " << strValue;

	return 0;
}
