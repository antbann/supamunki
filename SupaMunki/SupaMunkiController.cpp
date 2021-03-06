// SupaMunkiController.cpp : Implementation of CSupaMunkiController

#include "stdafx.h"
#include "SupaMunkiController.h"
#include "SupaMunkiElement.h"
#include <map>
#include <vector>
#include "Strings.h"


// CSupaMunkiController


CSupaMunkiController::CSupaMunkiController()
{
	m_pUnkMarshaler = NULL;

	m_pAutomationProxy = new AutomationProxy;
}


CSupaMunkiController::~CSupaMunkiController()
{
	m_pUnkMarshaler = NULL;

	if (m_pAutomationProxy != nullptr)
	{
		delete m_pAutomationProxy;
		m_pAutomationProxy = nullptr;
	}
}
