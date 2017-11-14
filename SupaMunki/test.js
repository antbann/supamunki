var oElement = new ActiveXObject('SupaMunki.Element').GetElement(null, 0);
WScript.Echo('Press ENTER to continue');
var input=WScript.StdIn.ReadLine();
var oNotepad = oElement.GetElement(['ControlType===Window', 'ClassName===Notepad'], 60000);
var oTitleBar = oNotepad.GetElement(['ControlType===TitleBar'], 0);
var oClose = oTitleBar.GetElement(['ControlType===Button', 'Name===Close'], 0);
oClose.Click();