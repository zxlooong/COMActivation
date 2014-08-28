// RegistryFreeWay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#import "..\Debug\Comdll.tlb" named_guids no_namespace


int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);

	IDLLTestObjectPtr spTestObject;
	HRESULT hr = spTestObject.CreateInstance(CLSID_DLLTestObject);
	ATLASSERT(SUCCEEDED(hr));
	if(SUCCEEDED(hr)) spTestObject->Test();

	spTestObject.Detach();

	::CoUninitialize();
	return 0;
}

