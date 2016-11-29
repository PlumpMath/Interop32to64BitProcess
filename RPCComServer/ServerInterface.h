/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */

#pragma once

/*
#include <ComDef.h>

// GUID of our COM server
_declspec(selectany) GUID CLSID_ServerInterface = { 0xdc186800,
                                         0x657f,
                                         0x11d4,
                                         { 0xb0, 0xb5,  0x0,  0x50,  0xba,  0xbf,  0xc9,  0x5 }
                                         };

// interface definition
// for sample COM server just replace the uuid of interface and its name
// and add new method prototypes here ..
// 
interface __declspec(uuid("dc186800-657f-11d4-B0B5-0050BABFC905")) IServerInterface : public IUnknown
{
    IServerInterface()
        : m_refCount(0)
    {}

    STDMETHODIMP_(ULONG) AddRef()
    {
        return ::InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        long value = ::InterlockedDecrement(&m_refCount);

        if (!m_refCount)
            delete this;

        return value;
    }

    STDMETHOD(Square)(long *pVal)PURE;
    STDMETHOD(Cube)(long *pVal)PURE;

private:
    long        m_refCount;
};
*/