#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "TestCommon.h"


using namespace Tests;


TEST_CASE("CloseNotepad", "[smoke]") {
	TestCommon test;

	test.OpenNotepad();
	REQUIRE(test.IsNotepadWindowOnScreen());

	ISupaMunkiElement* pNotepadWindow, *pTitleBar, *pClose;
	test.CreateElement({ L"ControlType===Window", L"ClassName===Notepad" }, 60000, nullptr, &pNotepadWindow);
	REQUIRE(pNotepadWindow != nullptr);

	test.CreateElement({ L"ControlType===TitleBar" }, 0, pNotepadWindow, &pTitleBar);
	REQUIRE(pTitleBar != nullptr);

	test.CreateElement({ L"ControlType===Button", L"Name===Close" }, 0, pTitleBar, &pClose);
	REQUIRE(pClose != nullptr);

	pClose->Click();
	REQUIRE(!test.IsNotepadWindowOnScreen());
}