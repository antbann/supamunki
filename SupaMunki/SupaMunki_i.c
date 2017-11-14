

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ISupaMunkiElement,0x12b381dc,0x9dc3,0x4050,0xb6,0x88,0x3f,0xbd,0xaa,0x25,0xd7,0x20);


MIDL_DEFINE_GUID(IID, LIBID_SupaMunkiLib,0x7c9aaaa5,0xed08,0x49cb,0xbf,0xd2,0x73,0x8c,0x33,0x73,0x12,0x92);


MIDL_DEFINE_GUID(IID, DIID__ISupaMunkiElementEvents,0x7d6aeff4,0x3223,0x46c8,0xa5,0xb5,0xe4,0x35,0x90,0xd4,0x12,0x55);


MIDL_DEFINE_GUID(CLSID, CLSID_SupaMunkiElement,0x2a8272b8,0x324c,0x468e,0xa6,0x38,0x4a,0x82,0xe6,0x11,0x59,0xd0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



