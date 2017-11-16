#pragma once
#include <vector>
#include <string>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <iostream>
#include <OleAuto.h>
#include <chrono>
#include <thread>
#include <boost/filesystem/path.hpp>
#include "..\SupaMunki\SupaMunki_i.h"
#include "..\SupaMunki\SupaMunki_i.c"
#include "..\SupaMunki\WinReg.h"
#include "..\SupaMunki\Strings.h"


namespace filesystem = boost::filesystem;
using namespace winreg;

namespace Tests {

	class TestCommon {
	public:
		ISupaMunkiElement * m_peDesktop;
		ISupaMunkiElement * m_pElement;

		TestCommon()
		{
			KillNotepadProcesses();

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

		void OpenNotepad()
		{
			LPWSTR lpApplicationName = L"C:\\windows\\system32\\notepad.exe";
			auto pi = RunProcess(lpApplicationName, L"");

			while (!IsNotepadWindowOnScreen())
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}

			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
		}

		void InvokeScript(std::wstring strScript)
		{
			std::wstring strInterpreter;
			std::wstring extension = filesystem::path(strScript).extension().wstring();
			std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

			const UINT MAX_SCRIPT_TIME_MS = 300000;
			const std::wstring regAppsPart = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\";

			if (extension == L".js" || extension == L".vbs") {
				strInterpreter = L"C:\\windows\\syswow64\\cscript.exe";
			}
			else if(extension == L".py") {
				RegKey key{ HKEY_LOCAL_MACHINE, regAppsPart + L"python.exe" };
				std::wstring result(key.GetStringValue(L"Path"));
				strInterpreter = result.c_str();
			}
			else if (extension == L".ps") {
				RegKey key{ HKEY_LOCAL_MACHINE, regAppsPart + L"powershell.exe" };
				std::wstring result(key.GetExpandStringValue(NULL));
				strInterpreter = result.c_str();
			}

			auto pi = RunProcess(strInterpreter, strScript);

			WaitForSingleObjectEx(pi.hProcess, MAX_SCRIPT_TIME_MS, false);
		}

		bool IsNotepadWindowOnScreen()
		{
			return (bool)(FindWindowEx(NULL, NULL, L"Notepad", NULL));
		}

		bool IsNotepadWindowOnScreen(ULONG ulTimeoutMs, bool checkShutdown)
		{
			bool result = false;
			auto timeout = std::chrono::system_clock::now() + std::chrono::milliseconds(ulTimeoutMs);
			do
			{
				result = IsNotepadWindowOnScreen();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			} while (checkShutdown ? result : !result && std::chrono::system_clock::now() < timeout);

			return result;
		}

		void CreateElement(const std::vector<std::wstring> properties, ULONG ulTimeout, ISupaMunkiElement *pParent, ISupaMunkiElement **ppElement)
		{
			ISupaMunkiElement* pSomeElement;

			auto pProperties = CreateSearchProperties(properties);

			if (pParent == nullptr) {
				m_pElement->GetElement({ 0 }, 0, &m_peDesktop);
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
				if (wcscmp(pEntry.szExeFile, L"notepad.exe") == 0)
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

		PROCESS_INFORMATION RunProcess(std::wstring strProcess, std::wstring strArguments)
		{
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof(si);
			ZeroMemory(&pi, sizeof(pi));

			auto command = Strings::trim(strProcess + L" " + strArguments);
			
			if (!CreateProcess(NULL,
				(LPWSTR)command.c_str(),
				NULL,
				NULL,
				FALSE,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi))
			{
				std::wcout << L"CreateProcess() failed to start program '" << strProcess
					<< "' with arguments '" << strArguments << "'";
				exit(1);
			}

			return pi;
		}

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