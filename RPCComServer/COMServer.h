/* XCFrameworkEngine
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */

#pragma once

#include "RPCComServer_h.h"

class COMServer : public IServerInterface
{
public:
    COMServer()
        : m_refCount(0)
    {}
    ~COMServer() {}

    STDMETHOD(QueryInterface)(REFIID riid, LPVOID* ppToInterface);

    STDMETHOD(Square)(long *pVal);
    STDMETHOD(Cube)(long *pVal);

    STDMETHODIMP_(ULONG) AddRef()
    {
        return ::InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        long value = ::InterlockedDecrement(&m_refCount);

        if (!m_refCount)
        {
            delete this;
        }

        return value;
    }

private:
    long    m_refCount;
};