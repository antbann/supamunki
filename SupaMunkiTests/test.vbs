Dim oSupaMunki
Set oSupaMunki = CreateObject("SupaMunki.Element")

'Input

Dim oDesktop
Set oDesktop = oSupaMunki.GetElement(Nothing, 0)

Dim oNotepad, oNotepadProps
oNotepadProps = Array("ControlType===Window", "ClassName===Notepad")
Set oNotepad = oDesktop.GetElement(oNotepadProps, 60000)

Dim oTitleBar, oTitleBarProps
oTitleBarProps = Array("ControlType===TitleBar")
Set oTitleBar = oNotepad.GetElement(oTitleBarProps, 0)

Dim oClose, oCloseProps
oCloseProps = Array("ControlType===Button", "Name===Close")
Set oClose = oTitleBar.GetElement(oCloseProps, 0)

oClose.Click()

Private Sub Input
	WScript.Echo "Press ENTER to continue"
	WScript.StdIn.ReadLine()
End Sub