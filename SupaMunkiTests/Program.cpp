#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TestCommon.h"


using namespace Tests;


TEST_CASE("ClickCloseButton", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow, *pTitleBar, *pClose;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);

	test.CreateElement({ L"ControlType===TitleBar" }, 0, pNotepadWindow, &pTitleBar);
	REQUIRE(pTitleBar != nullptr);

	test.CreateElement({ L"ControlType===Button", L"Name===Close" }, 0, pTitleBar, &pClose);
	REQUIRE(pClose != nullptr);

	pClose->Click();
	REQUIRE(!test.IsNotepadWindowOnScreen(5000, true));
}


TEST_CASE("FindWindowWithZeroTimeout", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 0, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);
}


TEST_CASE("FindWindowWithNonZeroTimeout", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);
}


TEST_CASE("FindWindowFromParent", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow, *pTitleBar;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);

	test.CreateElement({ L"ControlType===TitleBar" }, 0, pNotepadWindow, &pTitleBar);
	REQUIRE(pTitleBar != nullptr);
}


TEST_CASE("FindNonExistingWindowZeroTimeout", "[smoke]") {
	TestCommon test;

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 0, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow == nullptr);
}


TEST_CASE("FindNonExistingWindow", "[smoke]") {
	TestCommon test;

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow == nullptr);
}


TEST_CASE("FindWindowTwoTimes", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);

	pNotepadWindow = nullptr;
	
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);
}


TEST_CASE("FindWindowTwoTimesSecondTimeClosed", "[smoke]") {
	TestCommon test;
	test.OpenNotepad();

	ISupaMunkiElement* pNotepadWindow;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 5000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);

	test.KillNotepadProcesses();

	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 0, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow == nullptr);
}


TEST_CASE("InvokeFromScripts", "[smoke]") {
	TestCommon test;
	
	test.OpenNotepad();
	test.InvokeScript(L"test.js");
	REQUIRE(!test.IsNotepadWindowOnScreen());

	test.OpenNotepad();
	test.InvokeScript(L"test.vbs");
	REQUIRE(!test.IsNotepadWindowOnScreen());
}

// TODO: SetIntValue, SetStringValue, SetFocus, Expand, ContextMenu