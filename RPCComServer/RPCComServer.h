/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */

// RPCComServer.cpp : Defines the exported functions for the DLL application.
//

#pragma once

#include <objbase.h>

#ifdef RPCCOMSERVER_EXPORTS
#define RPCCOMDLL_API __declspec(dllexport)
#else
#define RPCCOMDLL_API __declspec(dllimport)
#endif

#if defined(INPROC_SERVER)

RPCCOMDLL_API STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut);
RPCCOMDLL_API STDAPI DllCanUnloadNow(void);
RPCCOMDLL_API STDAPI DllRegisterServer(void);
RPCCOMDLL_API STDAPI DllUnregisterServer(void);

#endif
