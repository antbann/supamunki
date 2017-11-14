#include <stdio.h>
#include <vector>
#include "..\SupaMunki\SupaMunki_i.h"
#include "..\SupaMunki\SupaMunki_i.c"



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


int main()
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

	if (FAILED(hr))
	{
		printf("CoCreateInstance failed!");
		return int(hr);
	}

	ISupaMunkiElement *pDesktop, *pNotepadWindow, *pTitleBar, *pClose;

	pElement->GetElement({ 0 }, 0, &pDesktop);

	auto ppropNotepad = CreateSearchProperties({ L"ControlType===Window", L"ClassName===Notepad" });
	pDesktop->GetElement(ppropNotepad, 60000, &pNotepadWindow);
	DestroyProperties(ppropNotepad);

	auto ppropsTitleBar = CreateSearchProperties({ L"ControlType===TitleBar" });
	pNotepadWindow->GetElement(ppropsTitleBar, 0, &pTitleBar);
	DestroyProperties(ppropsTitleBar);

	auto ppropsClose = CreateSearchProperties({ L"ControlType===Button", L"Name===Close" });
	pTitleBar->GetElement(ppropsClose, 0, &pClose);
	DestroyProperties(ppropsClose);

	pClose->Click();

	//Cleanup
	if (pClose != nullptr)
	{
		pClose->Release();
	}

	if (pTitleBar != nullptr)
	{
		pTitleBar->Release();
	}

	if (pNotepadWindow != nullptr)
	{
		pNotepadWindow->Release();
	}

	if (pDesktop != nullptr)
	{
		pDesktop->Release();
	}

	pElement->Release();
	CoUninitialize();

	return 0;
}
