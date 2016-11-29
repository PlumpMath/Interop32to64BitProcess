/* RPCComServer
 * Copyright (C) Abhishek Porwal, 2016
 * Any queries? Contact author <https://github.com/abhishekp314>
 * This program is complaint with GNU General Public License, version 3.
 * For complete license, read License.txt in source root directory. */

#pragma once

template<class InterfaceType>
class ComFactory : public IClassFactory
{
public:
    ComFactory()
        : m_obj(NULL)
        , m_refCount(0)
    {
    }

    STDMETHODIMP ComFactory::QueryInterface(REFIID riid, void** ppObj)
    {
        *ppObj = NULL;

        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IClassFactory))
        {
            *ppObj = (IClassFactory*) this;
            AddRef();
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    STDMETHODIMP ComFactory::CreateInstance(LPUNKNOWN pUnknow, REFIID riid, LPVOID* ppObj)
    {
        *ppObj = NULL;

        if (pUnknow)
            return CLASS_E_NOAGGREGATION;

        m_obj = new InterfaceType();

        HRESULT hr = m_obj->QueryInterface(riid, ppObj);

        if (hr != S_OK)
        {
            delete m_obj;
        }
        return hr;
    }


    STDMETHOD(LockServer)(BOOL) { return S_OK; }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return ::InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        long value = ::InterlockedDecrement(&m_refCount);

        if (!value)
        {
            delete m_obj;
        }

        return value;
    }

private:
    InterfaceType*  m_obj;
    long            m_refCount;
};