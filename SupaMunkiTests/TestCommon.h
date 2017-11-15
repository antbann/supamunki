#pragma once
#include <vector>
#include <string>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <iostream>
#include <OleAuto.h>
#include "..\SupaMunki\SupaMunki_i.h"
#include "..\SupaMunki\SupaMunki_i.c"



namespace Tests {

	class TestCommon {
	public:
		ISupaMunkiElement *m_peDesktop;
		ISupaMunkiElement *m_pElement;

		TestCommon()
		{
			CoInitializeEx(nullptr, COINIT_MULTITHREADED);
			ISupaMunkiElement* pElement = nullptr;

			CLSID clsid;
			CLSIDFromProgID(OLESTR("SupaMunki.Element"), &clsid);

			auto hr = CoCreateInstance(
				clsid,
				nullptr,
				CLSCTX_INPROC_SERVER,
				IID_ISupaMunkiElement,
				reinterpret_cast<void **>(&pElement));

			if (SUCCEEDED(hr)) {
				ISupaMunkiElement *pDesktop;
				pElement->GetElement({ 0 }, 0, &pDesktop);

				m_peDesktop = pDesktop;
				m_pElement = pElement;
			}
			else {
				m_peDesktop = nullptr;
				m_pElement = nullptr;
			}
		}

		~TestCommon()
		{
			if (m_peDesktop != nullptr) {
				m_peDesktop->Release();
			}

			if (m_pElement != nullptr) {
				m_pElement->Release();
			}

			for (auto &v : m_vpElements) {
				if (v != nullptr) {
					v->Release();
					v = nullptr;
				}
			}

			m_vpElements.clear();

			CoUninitialize();

			KillNotepadProcesses();
		}

		HANDLE OpenNotepad()
		{
			LPSTR lpApplicationName = "C:\\windows\\system32\\notepad.exe";

			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			if (!CreateProcess(NULL,
				lpApplicationName,
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				&si,
				&pi))
			{
				std::cerr << "Uh-Oh! CreateProcess() failed to start program \"" << lpApplicationName << "\"\n";
				exit(1);
			}

			std::cout << "Started program \"" << lpApplicationName << "\" successfully\n";
			return pi.hProcess;
		}

		bool IsNotepadWindowOnScreen()
		{
			return (bool)(FindWindowEx(NULL, NULL, "Notepad", NULL));
		}

		void CreateElement(const std::vector<std::wstring> properties, ULONG ulTimeout, ISupaMunkiElement *pParent, ISupaMunkiElement **ppElement)
		{
			ISupaMunkiElement* pSomeElement;

			auto pProperties = CreateSearchProperties(properties);

			if (pParent == nullptr) {
				m_peDesktop->GetElement(pProperties, ulTimeout, &pSomeElement);
			}
			else {
				pParent->GetElement(pProperties, ulTimeout, &pSomeElement);
			}

			DestroyProperties(pProperties);

			*ppElement = pSomeElement;
			m_vpElements.insert(m_vpElements.begin(), pSomeElement);
		}

		void KillNotepadProcesses()
		{
			HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
			PROCESSENTRY32 pEntry;
			pEntry.dwSize = sizeof(pEntry);
			BOOL hRes = Process32First(hSnapShot, &pEntry);
			while (hRes)
			{
				if (strcmp(pEntry.szExeFile, "notepad.exe") == 0)
				{
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
						(DWORD)pEntry.th32ProcessID);
					if (hProcess != NULL && pEntry.th32ProcessID != GetCurrentProcessId())
					{
						TerminateProcess(hProcess, 9);
						CloseHandle(hProcess);
					}
				}
				hRes = Process32Next(hSnapShot, &pEntry);
			}
			CloseHandle(hSnapShot);
		}

	private:
		std::vector<ISupaMunkiElement*> m_vpElements;

		VARIANT CreateSearchProperties(const std::vector<std::wstring> properties)
		{
			int length = properties.size();

			SAFEARRAYBOUND saNamesBounds;
			saNamesBounds.cElements = length;
			saNamesBounds.lLbound = 0;
			auto psaNames = SafeArrayCreate(VT_BSTR, 1, &saNamesBounds);

			SafeArrayLock(psaNames);
			auto nameArray = static_cast<BSTR *>(psaNames->pvData);

			for (auto i = 0; i < length; i++)
			{
				nameArray[i] = SysAllocString(properties[i].c_str());
			}

			SafeArrayUnlock(psaNames);

			VARIANT ret;
			ret.vt = VT_ARRAY | VT_VARIANT;
			ret.parray = psaNames;

			return ret;
		}

		void DestroyProperties(VARIANT props)
		{
			if (props.vt == VT_NULL) {
				return;
			}

			SafeArrayDestroy(props.parray);
			VariantClear(&props);
		}
	};

}