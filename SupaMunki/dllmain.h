// dllmain.h : Declaration of module class.

class CSupaMunkiModule : public ATL::CAtlDllModuleT< CSupaMunkiModule >
{
public :
	DECLARE_LIBID(LIBID_SupaMunkiLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SUPAMUNKI, "{7c9aaaa5-ed08-49cb-bfd2-738c33731292}")
};

extern class CSupaMunkiModule _AtlModule;
