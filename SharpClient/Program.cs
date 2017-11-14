namespace SharpClient
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var supaMunkiWrapper = new SupaMunkiWrapper())
            {
                var desktop = supaMunkiWrapper.GetElement(null, 0);
                var notepad = desktop.GetElement(new[] {"ControlType===Window", "ClassName===Notepad"}, 60000);
                var titleBar = notepad.GetElement(new[] {"ControlType===TitleBar"}, 0);
                var close = titleBar.GetElement(new[] {"ControlType===Button", "Name===Close"}, 0);
                close.Click();
            }
        }
    }
}
