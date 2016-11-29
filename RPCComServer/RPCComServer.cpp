/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */

// RPCComServer.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "ServerInterface.h"
#include "RPCComServer_h.h"
#include "RPCComServer_i.c"
#include "COMServer.h"
#include "Registrar.h"
#include "ComFactory.h"

#if defined(INPROC_SERVER)

long g_cRefThisDll;
HANDLE g_module;

BOOL APIENTRY DllMain(HANDLE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_module = hModule;
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
    *ppvOut = NULL;
    if (IsEqualIID(rclsid, CLSID_ServerInterface))
    {
        // declare a classfactory for CmyInterface class 
        ComFactory<COMServer>* serverFactory = new ComFactory<COMServer>();
        return serverFactory->QueryInterface(riid, ppvOut);
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}

STDAPI  DllCanUnloadNow(void)
{
    return (g_cRefThisDll == 0 ? S_OK : S_FALSE);
}

STDAPI DllRegisterServer(void)
{
    CDllRegistrar registrar;  // this class should create standard entries in registry 
    char path[MAX_PATH];
    GetModuleFileName((HMODULE)g_module, path, MAX_PATH);
    return registrar.RegisterObject(CLSID_ServerInterface, "MineLib", "MathObj", path) ? S_OK : S_FALSE;
}

STDAPI DllUnregisterServer(void)
{
    CDllRegistrar registrar;
    return registrar.UnRegisterObject(CLSID_ServerInterface, "MineLib", "MathObj") ? S_OK : S_FALSE;
}

#elif defined(OUTPROC_SERVER)

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    CoInitialize(0);

    //Register proxy stub lib
    ITypeLib* pTLib = NULL;
    HRESULT hr = LoadTypeLibEx(L"RPCComServer.tlb", REGKIND_REGISTER, &pTLib);
    pTLib->Release();
    if (FAILED(hr))
    {
        exit(1);
    }

    ComFactory<COMServer> comFactory;

    DWORD regID = sizeof(void*);
    hr = CoRegisterClassObject(CLSID_COMServer, (IClassFactory*)&comFactory,
        CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &regID);

    if (FAILED(hr))
    {
        assert(false);
        CoUninitialize();
        return 1;
    }

    MSG ms;
    while (GetMessage(&ms, 0, 0, 0))
    {
        TranslateMessage(&ms);
        DispatchMessage(&ms);
    }

    CoRevokeClassObject(regID);
    CoUninitialize();

    return 0;
}


#endif