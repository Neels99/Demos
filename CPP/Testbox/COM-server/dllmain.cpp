// dllmain.cpp: реализация DllMain.

#include "stdafx.h"
#include "resource.h"
#include "COMserver_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CCOMserverModule _AtlModule;

// Точка входа DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(hInstance, dwReason, lpReserved))
		return FALSE;
#endif
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
