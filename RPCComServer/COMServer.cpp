
#include "stdafx.h"

#include "COMServer.h"

STDMETHODIMP COMServer::QueryInterface(REFIID riid, LPVOID* ppToInterface)
{
    *ppToInterface = NULL;

    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, __uuidof(IServerInterface)))
    {
        *ppToInterface = (IServerInterface*)this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP COMServer::Square(long *pVal)
{
    long value = *pVal;
    *pVal = value * value;
    return S_OK;
}

STDMETHODIMP COMServer::Cube(long *pVal)
{
    long value = *pVal;
    *pVal = value * value * value;
    return S_OK;
}