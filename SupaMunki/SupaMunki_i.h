

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Nov 14 17:05:23 2017
 */
/* Compiler settings for SupaMunki.idl:
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

#ifndef __SupaMunki_i_h__
#define __SupaMunki_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISupaMunkiElement_FWD_DEFINED__
#define __ISupaMunkiElement_FWD_DEFINED__
typedef interface ISupaMunkiElement ISupaMunkiElement;
#endif 	/* __ISupaMunkiElement_FWD_DEFINED__ */


#ifndef ___ISupaMunkiElementEvents_FWD_DEFINED__
#define ___ISupaMunkiElementEvents_FWD_DEFINED__
typedef interface _ISupaMunkiElementEvents _ISupaMunkiElementEvents;
#endif 	/* ___ISupaMunkiElementEvents_FWD_DEFINED__ */


#ifndef __SupaMunkiElement_FWD_DEFINED__
#define __SupaMunkiElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class SupaMunkiElement SupaMunkiElement;
#else
typedef struct SupaMunkiElement SupaMunkiElement;
#endif /* __cplusplus */

#endif 	/* __SupaMunkiElement_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISupaMunkiElement_INTERFACE_DEFINED__
#define __ISupaMunkiElement_INTERFACE_DEFINED__

/* interface ISupaMunkiElement */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISupaMunkiElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12b381dc-9dc3-4050-b688-3fbdaa25d720")
    ISupaMunkiElement : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetElement( 
            /* [in] */ VARIANT arrSpecification,
            /* [in] */ ULONG ulTimeoutMs,
            /* [retval][out] */ ISupaMunkiElement **oResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetIntValue( 
            /* [in] */ int nValue,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStringValue( 
            /* [in] */ BSTR szValue,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFocus( 
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitProperty( 
            /* [in] */ BSTR szPropertyName,
            /* [in] */ VARIANT oValue,
            /* [in] */ int nTimeoutMs,
            /* [retval][out] */ VARIANT_BOOL *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Expand( 
            /* [in] */ VARIANT_BOOL bExpand) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Click( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ ISupaMunkiElement **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Parent( 
            /* [in] */ ISupaMunkiElement *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISupaMunkiElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISupaMunkiElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISupaMunkiElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISupaMunkiElement * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISupaMunkiElement * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISupaMunkiElement * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISupaMunkiElement * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISupaMunkiElement * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetElement )( 
            ISupaMunkiElement * This,
            /* [in] */ VARIANT arrSpecification,
            /* [in] */ ULONG ulTimeoutMs,
            /* [retval][out] */ ISupaMunkiElement **oResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetIntValue )( 
            ISupaMunkiElement * This,
            /* [in] */ int nValue,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetStringValue )( 
            ISupaMunkiElement * This,
            /* [in] */ BSTR szValue,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetFocus )( 
            ISupaMunkiElement * This,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitProperty )( 
            ISupaMunkiElement * This,
            /* [in] */ BSTR szPropertyName,
            /* [in] */ VARIANT oValue,
            /* [in] */ int nTimeoutMs,
            /* [retval][out] */ VARIANT_BOOL *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Expand )( 
            ISupaMunkiElement * This,
            /* [in] */ VARIANT_BOOL bExpand);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Click )( 
            ISupaMunkiElement * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Parent )( 
            ISupaMunkiElement * This,
            /* [retval][out] */ ISupaMunkiElement **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Parent )( 
            ISupaMunkiElement * This,
            /* [in] */ ISupaMunkiElement *newVal);
        
        END_INTERFACE
    } ISupaMunkiElementVtbl;

    interface ISupaMunkiElement
    {
        CONST_VTBL struct ISupaMunkiElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISupaMunkiElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISupaMunkiElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISupaMunkiElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISupaMunkiElement_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISupaMunkiElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISupaMunkiElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISupaMunkiElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISupaMunkiElement_GetElement(This,arrSpecification,ulTimeoutMs,oResult)	\
    ( (This)->lpVtbl -> GetElement(This,arrSpecification,ulTimeoutMs,oResult) ) 

#define ISupaMunkiElement_SetIntValue(This,nValue,bResult)	\
    ( (This)->lpVtbl -> SetIntValue(This,nValue,bResult) ) 

#define ISupaMunkiElement_SetStringValue(This,szValue,bResult)	\
    ( (This)->lpVtbl -> SetStringValue(This,szValue,bResult) ) 

#define ISupaMunkiElement_SetFocus(This,bResult)	\
    ( (This)->lpVtbl -> SetFocus(This,bResult) ) 

#define ISupaMunkiElement_WaitProperty(This,szPropertyName,oValue,nTimeoutMs,bResult)	\
    ( (This)->lpVtbl -> WaitProperty(This,szPropertyName,oValue,nTimeoutMs,bResult) ) 

#define ISupaMunkiElement_Expand(This,bExpand)	\
    ( (This)->lpVtbl -> Expand(This,bExpand) ) 

#define ISupaMunkiElement_Click(This)	\
    ( (This)->lpVtbl -> Click(This) ) 

#define ISupaMunkiElement_get_Parent(This,pVal)	\
    ( (This)->lpVtbl -> get_Parent(This,pVal) ) 

#define ISupaMunkiElement_put_Parent(This,newVal)	\
    ( (This)->lpVtbl -> put_Parent(This,newVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISupaMunkiElement_INTERFACE_DEFINED__ */



#ifndef __SupaMunkiLib_LIBRARY_DEFINED__
#define __SupaMunkiLib_LIBRARY_DEFINED__

/* library SupaMunkiLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SupaMunkiLib;

#ifndef ___ISupaMunkiElementEvents_DISPINTERFACE_DEFINED__
#define ___ISupaMunkiElementEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ISupaMunkiElementEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__ISupaMunkiElementEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7d6aeff4-3223-46c8-a5b5-e43590d41255")
    _ISupaMunkiElementEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ISupaMunkiElementEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISupaMunkiElementEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISupaMunkiElementEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISupaMunkiElementEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ISupaMunkiElementEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ISupaMunkiElementEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ISupaMunkiElementEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ISupaMunkiElementEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ISupaMunkiElementEventsVtbl;

    interface _ISupaMunkiElementEvents
    {
        CONST_VTBL struct _ISupaMunkiElementEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISupaMunkiElementEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISupaMunkiElementEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISupaMunkiElementEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISupaMunkiElementEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _ISupaMunkiElementEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _ISupaMunkiElementEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _ISupaMunkiElementEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ISupaMunkiElementEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SupaMunkiElement;

#ifdef __cplusplus

class DECLSPEC_UUID("2a8272b8-324c-468e-a638-4a82e61159d0")
SupaMunkiElement;
#endif
#endif /* __SupaMunkiLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


