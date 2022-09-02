#if !defined(AFX_SK_H__7C685788_786D_45E4_8740_40E826DE95CC__HEAD__)
#define AFX_SK_H__7C685788_786D_45E4_8740_40E826DE95CC__HEAD__

#if defined(SHARED_API)
#define __shared_api_ extern "C" __declspec(dllexport)
#else
#define __shared_api_ extern "C" __declspec(dllimport)
#endif

__shared_api_ void __stdcall api_object_init(const void*, unsigned long);
__shared_api_ void __stdcall api_object_uninit();

/*!@ 新生联创®（上海）*/
/*!@ Thu Sep 9 10:02:49 UTC+0800 2021*/
/*!@ ___www.skstu.com___*/
#endif /*AFX_SK_H__7C685788_786D_45E4_8740_40E826DE95CC__HEAD__*/