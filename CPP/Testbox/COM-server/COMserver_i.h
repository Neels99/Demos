

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu May 23 12:39:24 2013
 */
/* Compiler settings for COMserver.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
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
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COMserver_i_h__
#define __COMserver_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IComTestServer_FWD_DEFINED__
#define __IComTestServer_FWD_DEFINED__
typedef interface IComTestServer IComTestServer;
#endif 	/* __IComTestServer_FWD_DEFINED__ */


#ifndef __Ifigure_FWD_DEFINED__
#define __Ifigure_FWD_DEFINED__
typedef interface Ifigure Ifigure;
#endif 	/* __Ifigure_FWD_DEFINED__ */


#ifndef __ComTestServer_FWD_DEFINED__
#define __ComTestServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComTestServer ComTestServer;
#else
typedef struct ComTestServer ComTestServer;
#endif /* __cplusplus */

#endif 	/* __ComTestServer_FWD_DEFINED__ */


#ifndef __figure_FWD_DEFINED__
#define __figure_FWD_DEFINED__

#ifdef __cplusplus
typedef class figure figure;
#else
typedef struct figure figure;
#endif /* __cplusplus */

#endif 	/* __figure_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComTestServer_INTERFACE_DEFINED__
#define __IComTestServer_INTERFACE_DEFINED__

/* interface IComTestServer */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IComTestServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("03C792C9-36E3-44F0-BBAC-0CFE6D6AC620")
    IComTestServer : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE square( 
            /* [in] */ LONG sizeA,
            /* [in] */ LONG sizeB,
            /* [retval][out] */ LONG *result) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComTestServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComTestServer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComTestServer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComTestServer * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComTestServer * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComTestServer * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComTestServer * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComTestServer * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *square )( 
            IComTestServer * This,
            /* [in] */ LONG sizeA,
            /* [in] */ LONG sizeB,
            /* [retval][out] */ LONG *result);
        
        END_INTERFACE
    } IComTestServerVtbl;

    interface IComTestServer
    {
        CONST_VTBL struct IComTestServerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComTestServer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComTestServer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComTestServer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComTestServer_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IComTestServer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IComTestServer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IComTestServer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IComTestServer_square(This,sizeA,sizeB,result)	\
    ( (This)->lpVtbl -> square(This,sizeA,sizeB,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComTestServer_INTERFACE_DEFINED__ */


#ifndef __Ifigure_INTERFACE_DEFINED__
#define __Ifigure_INTERFACE_DEFINED__

/* interface Ifigure */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_Ifigure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F15368E7-E74C-497B-B22F-F89F6BCD8C77")
    Ifigure : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE draw( 
            /* [in] */ SHORT X,
            /* [in] */ SHORT Y) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IfigureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ifigure * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ifigure * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ifigure * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ifigure * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ifigure * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ifigure * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ifigure * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *draw )( 
            Ifigure * This,
            /* [in] */ SHORT X,
            /* [in] */ SHORT Y);
        
        END_INTERFACE
    } IfigureVtbl;

    interface Ifigure
    {
        CONST_VTBL struct IfigureVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ifigure_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ifigure_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ifigure_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ifigure_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ifigure_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ifigure_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ifigure_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define Ifigure_draw(This,X,Y)	\
    ( (This)->lpVtbl -> draw(This,X,Y) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Ifigure_INTERFACE_DEFINED__ */



#ifndef __COMserverLib_LIBRARY_DEFINED__
#define __COMserverLib_LIBRARY_DEFINED__

/* library COMserverLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_COMserverLib;

EXTERN_C const CLSID CLSID_ComTestServer;

#ifdef __cplusplus

class DECLSPEC_UUID("CB0FFD73-90E5-447D-916D-3EB970E72304")
ComTestServer;
#endif

EXTERN_C const CLSID CLSID_figure;

#ifdef __cplusplus

class DECLSPEC_UUID("32DF4041-B656-422E-BB37-9327C65976F2")
figure;
#endif
#endif /* __COMserverLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


