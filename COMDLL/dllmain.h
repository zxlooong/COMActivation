// dllmain.h : Declaration of module class.

class CCOMDLLModule : public CAtlDllModuleT< CCOMDLLModule >
{
public :
	DECLARE_LIBID(LIBID_COMDLLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COMDLL, "{203D5880-BB6A-4DC1-8D79-FEF5AF1EE87E}")
};

extern class CCOMDLLModule _AtlModule;
