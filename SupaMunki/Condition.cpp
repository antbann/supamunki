#include "logger.h"
#include "Strings.h"
#include "resource.h"
#include "PropertyNameValuePair.h"
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
	CPropertyNameValuePair propertyNameValuePair(sName, sValue);
	auto propertyId = propertyNameValuePair.GetPropertyId();
	auto pvarValue = propertyNameValuePair.GetValueVariant();

	LOG_DETAILED << "creating proprety condition with propertyId=" << propertyId << " and varValue at " << pvarValue;
	auto hr = m_puiAutomation->CreatePropertyConditionEx(propertyId, *pvarValue,
		PropertyConditionFlags_IgnoreCase, ppCondition);

	LOG_DETAILED << "created proprety condition 0x" << *ppCondition << ", HRESULT=" << hr;

	return hr;
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