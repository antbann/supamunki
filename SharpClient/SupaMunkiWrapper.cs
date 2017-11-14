using SharpClient.Wrappers;
using SupaMunkiLib;


namespace SharpClient
{
    public class SupaMunkiWrapper : ComWrapper<ISupaMunkiElement>, ISupaMunkiElement
    {
        private const string ProgId = "SupaMunki.Element";

        public SupaMunkiElement Parent { get; set; }

        public SupaMunkiWrapper() : base(ProgId)
        {
        }

        public SupaMunkiElement GetElement(object arrSpecification, uint ulTimeoutMs)
        {
            return ComObject.GetElement(arrSpecification, ulTimeoutMs);
        }

        public bool SetIntValue(int nValue)
        {
            return ComObject.SetIntValue(nValue);
        }

        public bool SetStringValue(string szValue)
        {
            return ComObject.SetStringValue(szValue);
        }

        public bool SetFocus()
        {
            return ComObject.SetFocus();
        }

        public bool WaitProperty(string szPropertyName, object oValue, int nTimeoutMs)
        {
            return ComObject.WaitProperty(szPropertyName, oValue, nTimeoutMs);
        }

        public void Expand(bool bExpand)
        {
            ComObject.Expand(bExpand);
        }

        public void Click()
        {
            ComObject.Click();
        }
    }
}
