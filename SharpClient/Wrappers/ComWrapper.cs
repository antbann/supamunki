using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace SharpClient.Wrappers
{
    public abstract class ComWrapper<T> : IDisposable
    {
        protected ComWrapper()
        {
            ComObject = CreateObjectByType();
        }

        protected ComWrapper(string progId)
        {
            ComObject = CreateObjectByProgId(progId);
        }

        protected ComWrapper(Guid guid)
        {
            ComObject = CreateObjectByGuid(guid.ToString());
        }

        protected ComWrapper(T copy)
        {
            ComObject = copy;
        }

        protected readonly T ComObject;
        private bool _disposed;

        public virtual void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public static implicit operator T(ComWrapper<T> wrapper)
        {
            return wrapper.ComObject;
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    FreeManagedResources();
                }

                if (ComObject != null)
                {
                    var count = Marshal.FinalReleaseComObject(ComObject);

                    Debug.Assert(count == 0, "COM object reference count > 0");
                }
            }

            _disposed = true;
        }

        public override string ToString()
        {
            if (ComObject == null)
            {
                return string.Empty;
            }

            if (!Marshal.IsComObject(ComObject))
            {
                return string.Empty;
            }

            if (!(ComObject is IDispatch dispatch))
            {
                return string.Empty;
            }

            ITypeInfo typeInfo = null;
            try
            {
                try
                {
                    dispatch.GetTypeInfo(0, 0, out typeInfo);
                }
                catch (Exception)
                {
                    return string.Empty;
                }

                return TryGetTypeName(typeInfo);
            }
            catch (Exception)
            {
                return string.Empty;
            }
            finally
            {
                if (typeInfo != null)
                {
                    Marshal.ReleaseComObject(typeInfo);
                }
            }
        }

        private void FreeManagedResources()
        {
            //TODO:
        }

        private static string TryGetTypeName(ITypeInfo typeInfo)
        {
            string typeName;
            try
            {
                typeInfo.GetDocumentation(-1, out typeName, out _,
                    out _, out _);
            }
            catch (Exception)
            {
                return string.Empty;
            }

            return typeName;
        }

        private T CreateObjectByProgId(string progId)
        {
            return CreateObject(CreationTypes.ByProgId, progId);
        }

        private T CreateObjectByType()
        {
            return CreateObject(CreationTypes.ByType, null);
        }

        private T CreateObjectByGuid(string guid)
        {
            return CreateObject(CreationTypes.ByGuid, guid);
        }

        private T CreateObject(CreationTypes creationType, string parameter)
        {
            T result;

            switch (creationType)
            {
                case CreationTypes.ByProgId:
                    result = (T)Activator.CreateInstance(Type.GetTypeFromProgID(parameter));
                    break;
                case CreationTypes.ByType:
                    result = (T)Activator.CreateInstance(typeof(T));
                    break;
                case CreationTypes.ByGuid:
                    result = (T)Activator.CreateInstance(Type.GetTypeFromCLSID(new Guid(parameter)));
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(creationType), creationType, null);
            }

            return result;
        }

        ~ComWrapper()
        {
            Dispose(false);
        }
    }
}