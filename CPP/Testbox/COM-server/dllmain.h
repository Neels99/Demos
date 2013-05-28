// dllmain.h: объ€вление класса модул€.

class CCOMserverModule : public ATL::CAtlDllModuleT< CCOMserverModule >
{
public :
	DECLARE_LIBID(LIBID_COMserverLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMSERVER, "{924B90B3-62C2-4DE4-BEC2-4F159A0F1EDF}")
};

extern class CCOMserverModule _AtlModule;
