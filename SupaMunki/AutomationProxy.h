//
// AutomationProxy.h
//
// Defines class that proxies between IRapidFoxController and IUIControl
//

#pragma once
#include <map>
#include "uiautomation.h"


class AutomationProxy
{
public:
	AutomationProxy();
	~AutomationProxy();

	IUIAutomation *const m_piuiAutomation;
	IUIAutomationElement *const m_piuiAutomationElement;

	HRESULT GetCondition(std::wstring sName, std::wstring sValue, IUIAutomationCondition** ppCondition) const;

private:
	static int UiaControlTypeFromStr(std::wstring strValue);
};
