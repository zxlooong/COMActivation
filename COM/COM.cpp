// COM.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "COM_i.h"
#include "dlldatax.h"


class CCOMModule : public CAtlExeModuleT< CCOMModule >
{
public :
	DECLARE_LIBID(LIBID_COMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_COM, "{2755C7A5-9942-43D7-9A88-79781C1EE1CA}")
};

CCOMModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
                                LPTSTR /*lpCmdLine*/, int nShowCmd)
{
    return _AtlModule.WinMain(nShowCmd);
}

