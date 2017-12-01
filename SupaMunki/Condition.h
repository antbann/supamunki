#pragma once
#include "stdafx.h"
#include "SupaMunki_i.h"


using namespace ATL;


class CCondition 
{
public:
	CCondition(IUIAutomation *puiAutomation);
	~CCondition();

	IUIAutomationCondition *GetAutomationCondition();
	STDMETHOD(CreateFromSpecification)(std::vector<std::wstring> vSpecification);
private:
	IUIAutomation *m_puiAutomation;
	IUIAutomationCondition *m_puiAutomationCondition;
	std::vector<IUIAutomationCondition*> *m_pvConditions;

	STDMETHOD(GetCondition)(std::wstring sName, std::wstring sValue, IUIAutomationCondition** ppCondition);
	STDMETHOD(ClearPreviousConditions)();
};