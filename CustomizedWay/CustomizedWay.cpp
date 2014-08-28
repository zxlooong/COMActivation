// CustomizedWay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#import "..\Debug\Com.tlb" named_guids no_namespace
#import "..\Debug\ComDll.tlb" named_guids no_namespace

typedef HRESULT (STDAPICALLTYPE *DLLProc)(const CLSID& rclsid, const IID & riid, void ** ppv);
HRESULT CreateMyInProcHost(IDLLTestObject** ppResult)
{
	// Get the COM Server's full path
	wchar_t file[MAX_PATH] = {0};
	if (!GetModuleFileName(NULL, file, MAX_PATH))
		return E_FAIL;
	wchar_t drive[_MAX_DRIVE] = {0};
	wchar_t dir[_MAX_DIR] = {0};
	_wsplitpath_s(file, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
	_wmakepath_s(file, MAX_PATH, drive, dir, L"ComDll", L"dll");

	// Load DLL
	HMODULE hModule = ::LoadLibrary(file);
	if (!hModule) return E_FAIL;

	DLLProc DllGetClassObject;
	DllGetClassObject = (DLLProc)GetProcAddress(hModule, "DllGetClassObject");

	CComPtr<IClassFactory> pFactory;
	HRESULT hr = DllGetClassObject(CLSID_DLLTestObject, IID_IClassFactory, reinterpret_cast<void**>(&pFactory));
	if (FAILED(hr)) return hr;

	return pFactory->CreateInstance(NULL, __uuidof(*ppResult), reinterpret_cast<void**>(ppResult));

	return S_OK;

}

HRESULT CreateMyRemoteHost(ITestObject** ppResult)
{
	// Get the COM Server's full path
	wchar_t file[MAX_PATH] = {0};
	if (!GetModuleFileName(NULL, file, MAX_PATH))
		return E_FAIL;
	wchar_t drive[_MAX_DRIVE] = {0};
	wchar_t dir[_MAX_DIR] = {0};
	_wsplitpath_s(file, drive, _MAX_DRIVE, dir, _MAX_DIR, NULL, 0, NULL, 0);
	_wmakepath_s(file, MAX_PATH, drive, dir, L"Com", L"exe");


	// Start process
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	si.lpReserved = NULL;
	si.lpTitle = NULL;
	si.lpDesktop = NULL;
	si.dwX = si.dwY = si.dwYSize = si.dwXSize = 0;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	si.lpReserved2 = NULL;
	si.cbReserved2 = 0;
	BOOL ret = CreateProcess(file, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	if (!ret) return E_FAIL;
	WaitForInputIdle(pi.hProcess, 30000);


	// Get class factory (from class table)
	CComPtr<IClassFactory> pFactory;
	HRESULT hr = CoGetClassObject(CLSID_TestObject, CLSCTX_LOCAL_SERVER, NULL, __uuidof(pFactory), reinterpret_cast<void**>(&pFactory));
	if (FAILED(hr)) return hr;

	return pFactory->CreateInstance(NULL, __uuidof(*ppResult), reinterpret_cast<void**>(ppResult));

}


int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);

	// Out-Of-Proc Server
	ITestObjectPtr spTestObject;
	CreateMyRemoteHost(&spTestObject);

	spTestObject->Test();

	spTestObject.Detach()->Release();

	// In-Process Server
	IDLLTestObjectPtr spTestObject2;
	CreateMyInProcHost(&spTestObject2);
	spTestObject2->Test();
	spTestObject2.Detach()->Release();


	::CoUninitialize();
	return 0;
}

