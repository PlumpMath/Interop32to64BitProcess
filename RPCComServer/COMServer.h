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