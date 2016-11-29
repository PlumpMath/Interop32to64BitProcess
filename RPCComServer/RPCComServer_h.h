

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0620 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for RPCComServer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0620 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RPCComServer_h_h__
#define __RPCComServer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IServerInterface_FWD_DEFINED__
#define __IServerInterface_FWD_DEFINED__
typedef interface IServerInterface IServerInterface;

#endif 	/* __IServerInterface_FWD_DEFINED__ */


#ifndef __COMServer_FWD_DEFINED__
#define __COMServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class COMServer COMServer;
#else
typedef struct COMServer COMServer;
#endif /* __cplusplus */

#endif 	/* __COMServer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IServerInterface_INTERFACE_DEFINED__
#define __IServerInterface_INTERFACE_DEFINED__

/* interface IServerInterface */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IServerInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("dc186800-657f-11d4-B0B5-0050BABFC903")
    IServerInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Square( 
            /* [in] */ long *pVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cube( 
            /* [in] */ long *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServerInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServerInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServerInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServerInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *Square )( 
            IServerInterface * This,
            /* [in] */ long *pVal);
        
        HRESULT ( STDMETHODCALLTYPE *Cube )( 
            IServerInterface * This,
            /* [in] */ long *pVal);
        
        END_INTERFACE
    } IServerInterfaceVtbl;

    interface IServerInterface
    {
        CONST_VTBL struct IServerInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServerInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServerInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServerInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServerInterface_Square(This,pVal)	\
    ( (This)->lpVtbl -> Square(This,pVal) ) 

#define IServerInterface_Cube(This,pVal)	\
    ( (This)->lpVtbl -> Cube(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServerInterface_INTERFACE_DEFINED__ */



#ifndef __RPCComServerLib_LIBRARY_DEFINED__
#define __RPCComServerLib_LIBRARY_DEFINED__

/* library RPCComServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_RPCComServerLib;

EXTERN_C const CLSID CLSID_COMServer;

#ifdef __cplusplus

class DECLSPEC_UUID("dc186800-657f-11d4-B0B5-0050BABFC905")
COMServer;
#endif
#endif /* __RPCComServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


