// RegistryWay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#import "..\Debug\Com.tlb" named_guids no_namespace
#import "..\Debug\ComDLL.tlb" named_guids no_namespace

int _tmain(int argc, _TCHAR* argv[])
{
	::CoInitialize(NULL);
	
	// Out-Of-Proc Server
	ITestObjectPtr spTestObject;
	HRESULT hr = spTestObject.CreateInstance(CLSID_TestObject);
	ATLASSERT(SUCCEEDED(hr));
	if(SUCCEEDED(hr)) spTestObject->Test();
	spTestObject.Detach()->Release();

	// In-Process Server
	IDLLTestObjectPtr spTestObject2;
	hr = spTestObject2.CreateInstance(CLSID_DLLTestObject);
	ATLASSERT(SUCCEEDED(hr));
	if(SUCCEEDED(hr)) spTestObject2->Test();
	spTestObject2.Detach()->Release();

	::CoUninitialize();
	return 0;
}

