var oElement = new ActiveXObject('SupaMunki.Element').GetElement(null, 0);
//Input();
var oNotepad = oElement.GetElement(['ControlType===Window', 'ClassName===Notepad'], 60000);
var oTitleBar = oNotepad.GetElement(['ControlType===TitleBar'], 0);
var oClose = oTitleBar.GetElement(['ControlType===Button', 'Name===Close'], 0);
oClose.Click();

function Input()
{
	WScript.Echo('Press ENTER to continue');
	WScript.StdIn.ReadLine();
}