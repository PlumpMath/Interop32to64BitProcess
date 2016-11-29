/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */


#include <stdio.h>
#include <comdef.h>
#include <assert.h>

#include "..\RPCComServer\ComFactory.h"
#include "..\RPCComServer\COMServer.h"
#include "..\RPCComServer\RPCComServer_h.h"
#include "..\RPCComServer\RPCComServer_i.c"

void main()
{
    CoInitialize(0);
    HRESULT hr;
    ComFactory<COMServer>* interfaceFactory = nullptr;
    
    hr = CoGetClassObject(CLSID_COMServer,
        CLSCTX_LOCAL_SERVER,
        NULL,
        IID_IClassFactory,
        (void**)&interfaceFactory
        );

    if (FAILED(hr))
    {
        assert(false);
        return;
    }

    IServerInterface* srvInterface = nullptr;
    hr = interfaceFactory->CreateInstance(NULL, IID_IServerInterface, (void**)&srvInterface);

    if (FAILED(hr))
    {
        assert(false);
        return;
    }

    while (true)
    {
        //Keep on running and communicate with the 64 bit lib.
        long value = 3;
        srvInterface->Cube(&value);
        printf("Value : %d\n", value);
    };
}