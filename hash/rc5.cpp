// *****************************************************************************
// 版权所有（C）2022-2023，风一样的网络
// 保留所有权利
// *****************************************************************************
// 作者 : 风一样的少年
// 版本 : 1.0
// 功能说明:
//           main
// *****************************************************************************

#include "defs.h"

#ifdef _BYTE
#undef _BYTE
#define _BYTE unsigned char
#endif

#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE1(x)   BYTEn(x,  1)

#ifdef LOBYTE
#undef LOBYTE
#define LOBYTE(x)   BYTEn(x,  0)
#endif

//#pragma warning(disable: 4312 4311 4302)


//#define __ROL4__(x, y) __rotl__(x, y)       // Rotate left
//#define __ROR4__(x, y) __rotr__(x, y)       // Rotate right
//
//__declspec(naked) unsigned int __cdecl __rotl__(unsigned int x, unsigned int y)
//{
//	__asm push ecx
//	__asm mov eax, [esp + 8]
//	__asm mov ecx, [esp + 0Ch]
//redo:
//	__asm test ecx, ecx
//	__asm jz done
//	__asm rol eax, 1
//	__asm dec ecx
//	__asm jmp redo
//done:
//	__asm pop ecx
//	__asm ret
//}
//
//__declspec(naked) unsigned int __cdecl __rotr__(unsigned int x, unsigned int y)
//{
//	__asm push ecx
//	__asm mov eax, [esp + 8]
//	__asm mov ecx, [esp + 0Ch]
//redo:
//	__asm test ecx, ecx
//	__asm jz done
//	__asm ror eax, 1
//	__asm dec ecx
//	__asm jmp redo
//done:
//	__asm pop ecx
//	__asm ret
//}

int __cdecl rc5_initkey(unsigned int* ctx, unsigned int a2, unsigned __int8* key, signed int a4)
{
 signed int v4; // edi@1
 unsigned int v5; // ecx@6
 int v6; // ebx@6
 unsigned __int8* v7; // edx@6
 int v8; // esi@6
 unsigned int v9; // edi@7
 int v10; // eax@8
 int v11; // ecx@8
 int v12; // eax@8
 int v13; // esi@11
 int v14; // eax@11
 int v15; // ecx@11
 unsigned __int8* v16; // edx@11
 signed int v17; // eax@21
 int v18; // edi@21
 signed int v19; // ecx@21
 int v20; // esi@21
 int v21; // eax@23
 int v22; // ecx@25
 int result; // eax@25
 unsigned int v24; // eax@26
 int v25; // eax@26
 int v26; // ecx@26
 int v27; // ebx@26
 int v28; // [sp+Ch] [bp-114h]@26
 int v29; // [sp+10h] [bp-110h]@25
 unsigned int v30; // [sp+14h] [bp-10Ch]@6
 int v31; // [sp+14h] [bp-10Ch]@23
 int v32; // [sp+18h] [bp-108h]@6
 int v33; // [sp+18h] [bp-108h]@23
 int v34[64]; // [sp+1Ch] [bp-104h]@8

 v4 = a4;
 if (a4 != 16 && a4 != 12)
 {
  if (a4 != 8)
   v4 = 16;
  a4 = v4;
 }
 v5 = a2;
 v6 = 0;
 v7 = key;
 v8 = 0;
 *ctx = v4;
 v32 = 0;
 v30 = 0;
 if (((a2 - 8) & 0x80000000) == 0)
 {
  v9 = a2 >> 3;
  v30 = 8 * (a2 >> 3);
  do
  {
   v10 = v7[5];
   v34[v8] = (v7[3] << 24) | (v7[2] << 16) | (v7[1] << 8) | *v7;
   v11 = (v7[6] << 16) | (v10 << 8) | v7[4];
   v12 = v7[7] << 24;
   v7 += 8;
   v34[v8 + 1] = v12 | v11;
   v8 += 2;
   --v9;
  } while (v9);
  v4 = a4;
  v5 = a2;
  v32 = v8;
 }
 if (v5 != v30)
 {
  v13 = 0;
  v14 = v5 & 7;
  v15 = 0;
  v16 = &v7[v14];
  switch (v14)
  {
  case 8:
   v15 = *--v16 << 24;
   goto LABEL_13;
  case 7:
  LABEL_13:
   v15 |= *--v16 << 16;
   goto LABEL_14;
  case 6:
  LABEL_14:
   v15 |= *--v16 << 8;
   goto LABEL_15;
  case 5:
  LABEL_15:
   v15 |= *--v16;
   goto LABEL_16;
  case 4:
  LABEL_16:
   v13 = *--v16 << 24;
   goto LABEL_17;
  case 3:
  LABEL_17:
   v13 |= *--v16 << 16;
   goto LABEL_18;
  case 2:
  LABEL_18:
   v13 |= *--v16 << 8;
   goto LABEL_19;
  case 1:
  LABEL_19:
   v13 |= *(v16 - 1);
   break;
  default:
   break;
  }
  v34[v32 + 1] = v15;
  v5 = a2;
  v34[v32] = v13;
 }
 v17 = v5 + 3;
 v18 = 2 * v4 + 2;
 v19 = 1;
 v20 = v17 / 4;
 for (ctx[1] = 0xB7E15163; v19 < v18; ++v19)
  ctx[v19 + 1] = ctx[v19] - 1640531527;
 v31 = 0;
 v21 = v17 / 4;
 v33 = 0;
 if (v18 > v20)
  v21 = v18;
 v22 = 3 * v21;
 result = 0;
 v29 = v22;
 if (v22 > 0)
 {
  do
  {
   v24 = __ROL4__(ctx[v31 + 1] + v33 + result, 3);
   ctx[v31 + 1] = v24;
   v28 = v24;
   v25 = __ROL4__(v24 + v33 + v34[v6], (v24 + v33) & 0x1F);
   v26 = v6 + 1;
   v34[v6] = v25;
   v27 = 0;
   v33 = v25;
   if (v31 + 1 < v18)
    v27 = v31 + 1;
   result = v28;
   v31 = v27;
   v6 = 0;
   if (v26 < v20)
    v6 = v26;
   --v29;
  } while (v29);
 }
 return result;
}

unsigned int* __cdecl rc5_transform(unsigned int* block, unsigned int* key)
{
 unsigned int v2; // esi@1
 int v3; // edx@1
 unsigned int v4; // edx@1
 int v5; // esi@1
 unsigned int v6; // esi@1
 int v7; // eax@1
 unsigned int v8; // eax@1
 int v9; // esi@1
 unsigned int v10; // esi@1
 int v11; // edx@1
 unsigned int v12; // edx@1
 int v13; // esi@1
 unsigned int v14; // esi@1
 int v15; // eax@1
 unsigned int v16; // eax@1
 int v17; // esi@1
 unsigned int v18; // esi@1
 int v19; // edx@1
 unsigned int v20; // edx@1
 int v21; // esi@1
 unsigned int v22; // esi@1
 int v23; // eax@1
 unsigned int v24; // eax@1
 int v25; // esi@1
 unsigned int v26; // esi@1
 int v27; // edx@1
 unsigned int v28; // edx@1
 int v29; // esi@1
 unsigned int v30; // esi@1
 int v31; // edi@1
 unsigned int v32; // edi@1
 int v33; // esi@1
 unsigned int v34; // esi@1
 int v35; // eax@2
 unsigned int v36; // eax@2
 int v37; // esi@2
 unsigned int v38; // esi@2
 int v39; // edx@2
 unsigned int v40; // edx@2
 int v41; // esi@2
 unsigned int v42; // esi@2
 int v43; // eax@2
 unsigned int v44; // eax@2
 int v45; // esi@2
 unsigned int v46; // esi@2
 int v47; // edi@2
 int v48; // esi@2
 int v49; // eax@4
 unsigned int v50; // eax@4
 int v51; // esi@4
 unsigned int v52; // esi@4
 int v53; // edx@4
 unsigned int v54; // edx@4
 int v55; // esi@4
 unsigned int v56; // esi@4
 int v57; // eax@4
 unsigned int v58; // eax@4
 int v59; // esi@4
 unsigned int v60; // esi@4
 int v61; // edx@4
 unsigned int v62; // edx@4
 int v63; // esi@4
 unsigned int v64; // esi@4
 int v65; // eax@4
 unsigned int v66; // eax@4
 int v67; // esi@4
 unsigned int v68; // esi@4
 int v69; // edx@4
 unsigned int v70; // edx@4
 int v71; // esi@4
 unsigned int v72; // esi@4
 int v73; // eax@4
 unsigned int v74; // eax@4
 int v75; // esi@4
 unsigned int v76; // esi@4
 int v77; // edi@4
 int v78; // esi@4
 unsigned int* result; // eax@5

 v2 = block[1] + key[2];
 v3 = __ROL4__(v2 ^ (*block + key[1]), (*((_BYTE*)block + 4) + *((_BYTE*)key + 8)) & 0x1F);
 v4 = key[3] + v3;
 v5 = __ROL4__(v4 ^ v2, v4 & 0x1F);
 v6 = key[4] + v5;
 v7 = __ROL4__(v4 ^ v6, v6 & 0x1F);
 v8 = key[5] + v7;
 v9 = __ROL4__(v8 ^ v6, v8 & 0x1F);
 v10 = key[6] + v9;
 v11 = __ROL4__(v8 ^ v10, v10 & 0x1F);
 v12 = key[7] + v11;
 v13 = __ROL4__(v12 ^ v10, v12 & 0x1F);
 v14 = key[8] + v13;
 v15 = __ROL4__(v12 ^ v14, v14 & 0x1F);
 v16 = key[9] + v15;
 v17 = __ROL4__(v16 ^ v14, v16 & 0x1F);
 v18 = key[10] + v17;
 v19 = __ROL4__(v16 ^ v18, v18 & 0x1F);
 v20 = key[11] + v19;
 v21 = __ROL4__(v20 ^ v18, v20 & 0x1F);
 v22 = key[12] + v21;
 v23 = __ROL4__(v20 ^ v22, v22 & 0x1F);
 v24 = key[13] + v23;
 v25 = __ROL4__(v24 ^ v22, v24 & 0x1F);
 v26 = key[14] + v25;
 v27 = __ROL4__(v24 ^ v26, v26 & 0x1F);
 v28 = key[15] + v27;
 v29 = __ROL4__(v28 ^ v26, v28 & 0x1F);
 v30 = key[16] + v29;
 v31 = __ROL4__(v28 ^ v30, v30 & 0x1F);
 v32 = key[17] + v31;
 v33 = __ROL4__(v32 ^ v30, v32 & 0x1F);
 v34 = key[18] + v33;
 if (*key == 12)
 {
  v35 = __ROL4__(v32 ^ v34, v34 & 0x1F);
  v36 = key[19] + v35;
  v37 = __ROL4__(v36 ^ v34, v36 & 0x1F);
  v38 = key[20] + v37;
  v39 = __ROL4__(v36 ^ v38, v38 & 0x1F);
  v40 = key[21] + v39;
  v41 = __ROL4__(v40 ^ v38, v40 & 0x1F);
  v42 = key[22] + v41;
  v43 = __ROL4__(v40 ^ v42, v42 & 0x1F);
  v44 = key[23] + v43;
  v45 = __ROL4__(v44 ^ v42, v44 & 0x1F);
  v46 = key[24] + v45;
  v47 = __ROL4__(v44 ^ v46, v46 & 0x1F);
  v32 = key[25] + v47;
  v48 = __ROL4__(v32 ^ v46, v32 & 0x1F);
  v34 = key[26] + v48;
 }
 else if (*key == 16)
 {
  v49 = __ROL4__(v32 ^ v34, v34 & 0x1F);
  v50 = key[19] + v49;
  v51 = __ROL4__(v50 ^ v34, v50 & 0x1F);
  v52 = key[20] + v51;
  v53 = __ROL4__(v50 ^ v52, v52 & 0x1F);
  v54 = key[21] + v53;
  v55 = __ROL4__(v54 ^ v52, v54 & 0x1F);
  v56 = key[22] + v55;
  v57 = __ROL4__(v54 ^ v56, v56 & 0x1F);
  v58 = key[23] + v57;
  v59 = __ROL4__(v58 ^ v56, v58 & 0x1F);
  v60 = key[24] + v59;
  v61 = __ROL4__(v58 ^ v60, v60 & 0x1F);
  v62 = key[25] + v61;
  v63 = __ROL4__(v62 ^ v60, v62 & 0x1F);
  v64 = key[26] + v63;
  v65 = __ROL4__(v62 ^ v64, v64 & 0x1F);
  v66 = key[27] + v65;
  v67 = __ROL4__(v66 ^ v64, v66 & 0x1F);
  v68 = key[28] + v67;
  v69 = __ROL4__(v66 ^ v68, v68 & 0x1F);
  v70 = key[29] + v69;
  v71 = __ROL4__(v70 ^ v68, v70 & 0x1F);
  v72 = key[30] + v71;
  v73 = __ROL4__(v70 ^ v72, v72 & 0x1F);
  v74 = key[31] + v73;
  v75 = __ROL4__(v74 ^ v72, v74 & 0x1F);
  v76 = key[32] + v75;
  v77 = __ROL4__(v74 ^ v76, v76 & 0x1F);
  v32 = key[33] + v77;
  v78 = __ROL4__(v32 ^ v76, v32 & 0x1F);
  v34 = key[34] + v78;
 }
 result = block;
 *block = v32;
 block[1] = v34;
 return result;
}

unsigned int __cdecl rc5_transform2(unsigned int* block, unsigned int* key)
{
 unsigned int v2; // eax@1
 int v3; // edx@1
 int v4; // edx@2
 int v5; // edx@2
 int v6; // eax@2
 int v7; // eax@2
 int v8; // edx@2
 int v9; // edx@2
 int v10; // eax@2
 int v11; // eax@2
 int v12; // edx@2
 int v13; // edx@2
 int v14; // eax@2
 int v15; // eax@2
 int v16; // edx@2
 int v17; // eax@2
 int v18; // edx@4
 int v19; // edx@4
 int v20; // eax@4
 int v21; // eax@4
 int v22; // edx@4
 int v23; // edx@4
 int v24; // eax@4
 int v25; // eax@4
 int v26; // edx@4
 int v27; // edx@4
 int v28; // eax@4
 int v29; // eax@4
 int v30; // edx@4
 int v31; // eax@4
 int v32; // edx@5
 int v33; // edx@5
 int v34; // eax@5
 int v35; // eax@5
 int v36; // edx@5
 int v37; // edx@5
 int v38; // eax@5
 int v39; // eax@5
 int v40; // edx@5
 int v41; // edx@5
 int v42; // eax@5
 int v43; // eax@5
 int v44; // edx@5
 int v45; // edx@5
 int v46; // eax@5
 int v47; // eax@5
 int v48; // edx@5
 int v49; // edx@5
 int v50; // eax@5
 int v51; // eax@5
 int v52; // edx@5
 int v53; // edx@5
 int v54; // eax@5
 int v55; // eax@5
 int v56; // edx@5
 int v57; // edx@5
 int v58; // eax@5
 int v59; // eax@5
 int v60; // edx@5
 int v61; // edx@5
 int v62; // eax@5
 unsigned int result; // eax@5

 v2 = *block;
 v3 = block[1];
 if (*key == 16)
 {
  v4 = __ROR4__(v3 - key[34], v2 & 0x1F);
  v5 = v2 ^ v4;
  v6 = __ROR4__(v2 - key[33], v5 & 0x1F);
  v7 = v5 ^ v6;
  v8 = __ROR4__(v5 - key[32], v7 & 0x1F);
  v9 = v7 ^ v8;
  v10 = __ROR4__(v7 - key[31], v9 & 0x1F);
  v11 = v9 ^ v10;
  v12 = __ROR4__(v9 - key[30], v11 & 0x1F);
  v13 = v11 ^ v12;
  v14 = __ROR4__(v11 - key[29], v13 & 0x1F);
  v15 = v13 ^ v14;
  v16 = __ROR4__(v13 - key[28], v15 & 0x1F);
  v3 = v15 ^ v16;
  v17 = __ROR4__(v15 - key[27], v3 & 0x1F);
  v2 = v3 ^ v17;
 LABEL_4:
  v18 = __ROR4__(v3 - key[26], v2 & 0x1F);
  v19 = v2 ^ v18;
  v20 = __ROR4__(v2 - key[25], v19 & 0x1F);
  v21 = v19 ^ v20;
  v22 = __ROR4__(v19 - key[24], v21 & 0x1F);
  v23 = v21 ^ v22;
  v24 = __ROR4__(v21 - key[23], v23 & 0x1F);
  v25 = v23 ^ v24;
  v26 = __ROR4__(v23 - key[22], v25 & 0x1F);
  v27 = v25 ^ v26;
  v28 = __ROR4__(v25 - key[21], v27 & 0x1F);
  v29 = v27 ^ v28;
  v30 = __ROR4__(v27 - key[20], v29 & 0x1F);
  v3 = v29 ^ v30;
  v31 = __ROR4__(v29 - key[19], v3 & 0x1F);
  v2 = v3 ^ v31;
  goto LABEL_5;
 }
 if (*key == 12)
  goto LABEL_4;
LABEL_5:
 v32 = __ROR4__(v3 - key[18], v2 & 0x1F);
 v33 = v2 ^ v32;
 v34 = __ROR4__(v2 - key[17], v33 & 0x1F);
 v35 = v33 ^ v34;
 v36 = __ROR4__(v33 - key[16], v35 & 0x1F);
 v37 = v35 ^ v36;
 v38 = __ROR4__(v35 - key[15], v37 & 0x1F);
 v39 = v37 ^ v38;
 v40 = __ROR4__(v37 - key[14], v39 & 0x1F);
 v41 = v39 ^ v40;
 v42 = __ROR4__(v39 - key[13], v41 & 0x1F);
 v43 = v41 ^ v42;
 v44 = __ROR4__(v41 - key[12], v43 & 0x1F);
 v45 = v43 ^ v44;
 v46 = __ROR4__(v43 - key[11], v45 & 0x1F);
 v47 = v45 ^ v46;
 v48 = __ROR4__(v45 - key[10], v47 & 0x1F);
 v49 = v47 ^ v48;
 v50 = __ROR4__(v47 - key[9], v49 & 0x1F);
 v51 = v49 ^ v50;
 v52 = __ROR4__(v49 - key[8], v51 & 0x1F);
 v53 = v51 ^ v52;
 v54 = __ROR4__(v51 - key[7], v53 & 0x1F);
 v55 = v53 ^ v54;
 v56 = __ROR4__(v53 - key[6], v55 & 0x1F);
 v57 = v55 ^ v56;
 v58 = __ROR4__(v55 - key[5], v57 & 0x1F);
 v59 = v57 ^ v58;
 v60 = __ROR4__(v57 - key[4], v59 & 0x1F);
 v61 = v59 ^ v60;
 v62 = __ROR4__(v59 - key[3], v61 & 0x1F);
 result = (v61 ^ v62) - key[1];
 *block = result;
 block[1] = v61 - key[2];
 return result;
}

unsigned int __cdecl rc5_encrypt(unsigned __int8* src, unsigned __int8* dst, unsigned int len, unsigned int* key, unsigned __int8* iv, int is_encrypt)
{
 unsigned __int8* v6; // esi@2
 unsigned __int8* v7; // edi@2
 unsigned int v8; // ebx@2
 int v9; // eax@2
 unsigned int v10; // edx@2
 unsigned int v11; // ecx@2
 unsigned __int8* v12; // esi@3
 int v13; // ecx@4
 int v14; // ecx@4
 int v15; // eax@4
 unsigned int v16; // eax@4
 char v17; // zf@4
 unsigned __int8* v18; // eax@5
 unsigned __int8* v19; // ecx@8
 unsigned int v20; // eax@8
 unsigned int v21; // ecx@17
 unsigned int v22; // eax@19
 unsigned int result; // eax@20
 unsigned __int8* v24; // ebx@21
 unsigned int v25; // ecx@21
 int v26; // edx@21
 unsigned int v27; // edi@21
 unsigned __int8* v28; // ebx@22
 unsigned int v29; // edi@23
 int v30; // esi@23
 int v31; // esi@23
 unsigned __int8* v32; // eax@23
 unsigned int v33; // edx@23
 unsigned int v34; // ecx@23
 unsigned __int8* v35; // eax@23
 unsigned __int8* v36; // ecx@23
 unsigned __int8* v37; // edx@24
 int v38; // eax@27
 int v39; // ecx@27
 int v40; // eax@27
 unsigned int v41; // edx@27
 unsigned __int8* v42; // ecx@27
 unsigned int v43; // esi@28
 unsigned int v44; // edx@38
 unsigned int block[2]; // [sp+Ch] [bp-1Ch]@4
 int v46; // [sp+14h] [bp-14h]@22
 unsigned __int8* v47; // [sp+18h] [bp-10h]@21
 unsigned int v48; // [sp+1Ch] [bp-Ch]@2
 unsigned int v49; // [sp+20h] [bp-8h]@2
 unsigned __int8* v50; // [sp+24h] [bp-4h]@8
 unsigned int lena; // [sp+38h] [bp+10h]@3
 unsigned __int8* lend; // [sp+38h] [bp+10h]@5
 unsigned int lenb; // [sp+38h] [bp+10h]@8
 unsigned __int8* lenc; // [sp+38h] [bp+10h]@22
 unsigned __int8* lene; // [sp+38h] [bp+10h]@23
 int is_encrypta; // [sp+44h] [bp+1Ch]@21
 unsigned int is_encryptb; // [sp+44h] [bp+1Ch]@27

 if (is_encrypt)
 {
  v6 = iv;
  v7 = dst;
  v8 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v9 = iv[7] << 24;
  v10 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
  v11 = len - 8;
  v48 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
  v49 = len - 8;
  if (((len - 8) & 0x80000000) != 0)
  {
   v18 = src;
  }
  else
  {
   v12 = src;
   lena = len >> 3;
   v49 = -8 * lena + v11;
   do
   {
    v13 = (v12[5] << 8) | v12[4];
    block[0] = v8 ^ ((v12[3] << 24) | (v12[2] << 16) | (v12[1] << 8) | *v12);
    v14 = (v12[6] << 16) | v13;
    v15 = v12[7] << 24;
    v12 += 8;
    block[1] = v48 ^ (v15 | v14);
    rc5_transform(block, key);
    v8 = block[0];
    v10 = block[1];
    v16 = block[0] >> 8;
    *v7 = block[0];
    v7[1] = v16;
    v7[2] = v8 >> 16;
    v7[3] = BYTE3(v8);
    v7[4] = v10;
    v7[5] = BYTE1(v10);
    v7[6] = v10 >> 16;
    v7[7] = BYTE3(v10);
    v7 += 8;
    v17 = lena-- == 1;
    v48 = v10;
   } while (!v17);
   v11 = v49;
   lend = v12;
   v6 = iv;
   v18 = lend;
  }
  if (v11 != -8)
  {
   v19 = &v18[v11 + 8];
   v20 = 0;
   v49 += 7;
   lenb = 0;
   v50 = 0;
   if (v49 > 7)
   {
    v21 = 0;
   }
   else
   {
    switch (v49)
    {
    case 0u:
     goto LABEL_17;
    case 1u:
     goto LABEL_16;
    case 2u:
     goto LABEL_15;
    case 3u:
     goto LABEL_14;
    case 4u:
     goto LABEL_13;
    case 5u:
     goto LABEL_12;
    case 6u:
     break;
    case 7u:
     lenb = *--v19 << 24;
     break;
    }
    lenb |= *--v19 << 16;
   LABEL_12:
    lenb |= *--v19 << 8;
   LABEL_13:
    lenb |= *--v19;
   LABEL_14:
    v50 = (unsigned __int8*)(*--v19 << 24);
   LABEL_15:
    v50 = (unsigned __int8*)((*--v19 << 16) | (unsigned int)v50);
   LABEL_16:
    v50 = (unsigned __int8*)((*--v19 << 8) | (unsigned int)v50);
   LABEL_17:
    v21 = *(v19 - 1) | (unsigned int)v50;
    v20 = lenb;
   }
   block[1] = v48 ^ v20;
   block[0] = v8 ^ v21;
   rc5_transform(block, key);
   v8 = block[0];
   v10 = block[1];
   v22 = block[0] >> 8;
   *v7 = block[0];
   v7[1] = v22;
   v6 = iv;
   v7[2] = v8 >> 16;
   v7[3] = BYTE3(v8);
   v7[4] = v10;
   v7[5] = BYTE1(v10);
   v7[6] = v10 >> 16;
   v7[7] = BYTE3(v10);
  }
  *v6 = v8;
  v6[1] = BYTE1(v8);
  v6[2] = v8 >> 16;
  v6[3] = BYTE3(v8);
  v6[4] = v10;
  v6[5] = BYTE1(v10);
  result = v10 >> 16;
  v6[6] = v10 >> 16;
  v6[7] = BYTE3(v10);
 }
 else
 {
  v24 = iv;
  v47 = iv;
  v25 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v26 = (iv[5] << 8) | iv[4];
  v48 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v27 = len - 8;
  is_encrypta = (iv[7] << 24) | (iv[6] << 16) | v26;
  if (((len - 8) & 0x80000000) != 0)
  {
   v37 = src;
   v31 = is_encrypta;
   lenc = dst;
  }
  else
  {
   v28 = src;
   v49 = len >> 3;
   v46 = -8 * (len >> 3) + v27;
   lenc = dst;
   do
   {
    v30 = (v28[5] << 8) | v28[4];
    block[0] = (v28[3] << 24) | (v28[2] << 16) | (v28[1] << 8) | *v28;
    v29 = block[0];
    v31 = (v28[7] << 24) | (v28[6] << 16) | v30;
    v50 = v28 + 8;
    block[1] = v31;
    rc5_transform2(block, key);
    v32 = lenc;
    v33 = is_encrypta ^ block[1];
    v34 = v48 ^ block[0];
    *lenc = v48 ^ LOBYTE(block[0]);
    lene = lenc + 2;
    is_encrypta = v31;
    v32[1] = BYTE1(v34);
    *lene = v34 >> 16;
    v28 = v50;
    v35 = lene + 1;
    *v35 = BYTE3(v34);
    v36 = lene + 1;
    v35[1] = v33;
    v35[2] = BYTE1(v33);
    v36[3] = v33 >> 16;
    v36[4] = BYTE3(v33);
    v17 = v49-- == 1;
    lenc = lene + 6;
    v25 = v29;
    v48 = v29;
   } while (!v17);
   v24 = v47;
   v37 = v50;
   v27 = v46;
  }
  if (v27 == -8)
  {
   v44 = is_encrypta;
  }
  else
  {
   v38 = v37[5];
   v46 = (v37[3] << 24) | (v37[2] << 16) | (v37[1] << 8) | *v37;
   block[0] = v46;
   v39 = (v38 << 8) | v37[4];
   v40 = v37[6];
   v49 = v39;
   v49 = ((v40 | (v37[7] << 8)) << 16) | v39;
   block[1] = v49;
   rc5_transform2(block, key);
   v41 = v48 ^ block[0];
   is_encryptb = v31 ^ block[1];
   v42 = &lenc[v27 + 8];
   switch (v27)
   {
   case 0u:
    v43 = v31 ^ block[1];
    *--v42 = BYTE3(is_encryptb);
    goto LABEL_30;
   case 0xFFFFFFFF:
    v43 = v31 ^ block[1];
   LABEL_30:
    *--v42 = v43 >> 16;
    goto LABEL_32;
   case 0xFFFFFFFE:
    BYTE1(v43) = BYTE1(is_encryptb);
   LABEL_32:
    *--v42 = BYTE1(v43);
    goto LABEL_33;
   case 0xFFFFFFFD:
   LABEL_33:
    *--v42 = is_encryptb;
    goto LABEL_34;
   case 0xFFFFFFFC:
   LABEL_34:
    *--v42 = BYTE3(v41);
    goto LABEL_35;
   case 0xFFFFFFFB:
   LABEL_35:
    *--v42 = v41 >> 16;
    goto LABEL_36;
   case 0xFFFFFFFA:
   LABEL_36:
    *--v42 = BYTE1(v41);
    goto LABEL_37;
   case 0xFFFFFFF9:
   LABEL_37:
    *(v42 - 1) = v41;
    break;
   default:
    break;
   }
   v25 = v46;
   v44 = v49;
  }
  *v24 = v25;
  v24[1] = BYTE1(v25);
  v24[2] = v25 >> 16;
  v24[3] = BYTE3(v25);
  v24[4] = v44;
  v24[5] = BYTE1(v44);
  result = v44 >> 16;
  v24[6] = v44 >> 16;
  v24[7] = BYTE3(v44);
 }
 return result;
}


unsigned int __cdecl rc5_encrypt_01(unsigned __int8* src, unsigned __int8* dst, unsigned int len, unsigned int* key, unsigned __int8* iv, int is_encrypt)
{
 unsigned __int8* v6; // esi@2
 unsigned __int8* v7; // edi@2
 unsigned int v8; // ebx@2
 int v9; // eax@2
 unsigned int v10; // edx@2
 unsigned int v11; // ecx@2
 unsigned __int8* v12; // esi@3
 int v13; // ecx@4
 int v14; // ecx@4
 int v15; // eax@4
 unsigned int v16; // eax@4
 char v17; // zf@4
 unsigned __int8* v18; // eax@5
 unsigned __int8* v19; // ecx@8
 unsigned int v20; // eax@8
 unsigned int v21; // ecx@17
 unsigned int v22; // eax@19
 unsigned int result; // eax@20
 unsigned __int8* v24; // ebx@21
 unsigned int v25; // ecx@21
 int v26; // edx@21
 unsigned int v27; // edi@21
 unsigned __int8* v28; // ebx@22
 unsigned int v29; // edi@23
 int v30; // esi@23
 int v31; // esi@23
 unsigned __int8* v32; // eax@23
 unsigned int v33; // edx@23
 unsigned int v34; // ecx@23
 unsigned __int8* v35; // eax@23
 unsigned __int8* v36; // ecx@23
 unsigned __int8* v37; // edx@24
 int v38; // eax@27
 int v39; // ecx@27
 int v40; // eax@27
 unsigned int v41; // edx@27
 unsigned __int8* v42; // ecx@27
 unsigned int v43; // esi@28
 unsigned int v44; // edx@38
 unsigned int block[2]; // [sp+Ch] [bp-1Ch]@4
 int v46; // [sp+14h] [bp-14h]@22
 unsigned __int8* v47; // [sp+18h] [bp-10h]@21
 unsigned int v48; // [sp+1Ch] [bp-Ch]@2
 unsigned int v49; // [sp+20h] [bp-8h]@2
 unsigned __int8* v50; // [sp+24h] [bp-4h]@8
 unsigned int lena; // [sp+38h] [bp+10h]@3
 unsigned __int8* lend; // [sp+38h] [bp+10h]@5
 unsigned int lenb; // [sp+38h] [bp+10h]@8
 unsigned __int8* lenc; // [sp+38h] [bp+10h]@22
 unsigned __int8* lene; // [sp+38h] [bp+10h]@23
 int is_encrypta; // [sp+44h] [bp+1Ch]@21
 unsigned int is_encryptb; // [sp+44h] [bp+1Ch]@27

 if (is_encrypt)
 {
  v6 = iv;
  v7 = dst;
  v8 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v9 = iv[7] << 24;
  v10 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
  v11 = len - 8;
  v48 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
  v49 = len - 8;
  if (((len - 8) & 0x80000000) != 0)
  {
   v18 = src;
  }
  else
  {
   v12 = src;
   lena = len >> 3;
   v49 = -8 * lena + v11;
   do
   {

    //强制加上的
    v8 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
    v9 = iv[7] << 24;
    v10 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
    v48 = v9 | (iv[6] << 16) | (iv[5] << 8) | iv[4];
    //强制加上的

    v13 = (v12[5] << 8) | v12[4];
    block[0] = v8 ^ ((v12[3] << 24) | (v12[2] << 16) | (v12[1] << 8) | *v12);
    v14 = (v12[6] << 16) | v13;
    v15 = v12[7] << 24;
    v12 += 8;
    block[1] = v48 ^ (v15 | v14);
    rc5_transform(block, key);
    v8 = block[0];
    v10 = block[1];
    v16 = block[0] >> 8;
    *v7 = block[0];
    v7[1] = v16;
    v7[2] = v8 >> 16;
    v7[3] = BYTE3(v8);
    v7[4] = v10;
    v7[5] = BYTE1(v10);
    v7[6] = v10 >> 16;
    v7[7] = BYTE3(v10);
    v7 += 8;
    v17 = lena-- == 1;
    v48 = v10;
   } while (!v17);
   v11 = v49;
   lend = v12;
   v6 = iv;
   v18 = lend;
  }
  if (v11 != -8)
  {
   v19 = &v18[v11 + 8];
   v20 = 0;
   v49 += 7;
   lenb = 0;
   v50 = 0;
   if (v49 > 7)
   {
    v21 = 0;
   }
   else
   {
    switch (v49)
    {
    case 0u:
     goto LABEL_17;
    case 1u:
     goto LABEL_16;
    case 2u:
     goto LABEL_15;
    case 3u:
     goto LABEL_14;
    case 4u:
     goto LABEL_13;
    case 5u:
     goto LABEL_12;
    case 6u:
     break;
    case 7u:
     lenb = *--v19 << 24;
     break;
    }
    lenb |= *--v19 << 16;
   LABEL_12:
    lenb |= *--v19 << 8;
   LABEL_13:
    lenb |= *--v19;
   LABEL_14:
    v50 = (unsigned __int8*)(*--v19 << 24);
   LABEL_15:
    v50 = (unsigned __int8*)((*--v19 << 16) | (unsigned int)v50);
   LABEL_16:
    v50 = (unsigned __int8*)((*--v19 << 8) | (unsigned int)v50);
   LABEL_17:
    v21 = *(v19 - 1) | (unsigned int)v50;
    v20 = lenb;
   }
   block[1] = v48 ^ v20;
   block[0] = v8 ^ v21;
   rc5_transform(block, key);
   v8 = block[0];
   v10 = block[1];
   v22 = block[0] >> 8;
   *v7 = block[0];
   v7[1] = v22;
   v6 = iv;
   v7[2] = v8 >> 16;
   v7[3] = BYTE3(v8);
   v7[4] = v10;
   v7[5] = BYTE1(v10);
   v7[6] = v10 >> 16;
   v7[7] = BYTE3(v10);
  }
  *v6 = v8;
  v6[1] = BYTE1(v8);
  v6[2] = v8 >> 16;
  v6[3] = BYTE3(v8);
  v6[4] = v10;
  v6[5] = BYTE1(v10);
  result = v10 >> 16;
  v6[6] = v10 >> 16;
  v6[7] = BYTE3(v10);
 }
 else
 {
  v24 = iv;
  v47 = iv;
  v25 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v26 = (iv[5] << 8) | iv[4];
  v48 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
  v27 = len - 8;
  is_encrypta = (iv[7] << 24) | (iv[6] << 16) | v26;
  if (((len - 8) & 0x80000000) != 0)
  {
   v37 = src;
   v31 = is_encrypta;
   lenc = dst;
  }
  else
  {
   v28 = src;
   v49 = len >> 3;
   v46 = -8 * (len >> 3) + v27;
   lenc = dst;
   do
   {
    //强制加上的
    v25 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
    v26 = (iv[5] << 8) | iv[4];
    v48 = (iv[3] << 24) | (iv[2] << 16) | (iv[1] << 8) | *iv;
    is_encrypta = (iv[7] << 24) | (iv[6] << 16) | v26;
    //强制加上的

    v30 = (v28[5] << 8) | v28[4];
    block[0] = (v28[3] << 24) | (v28[2] << 16) | (v28[1] << 8) | *v28;
    v29 = block[0];
    v31 = (v28[7] << 24) | (v28[6] << 16) | v30;
    v50 = v28 + 8;
    block[1] = v31;
    rc5_transform2(block, key);
    v32 = lenc;
    v33 = is_encrypta ^ block[1];
    v34 = v48 ^ block[0];
    *lenc = v48 ^ LOBYTE(block[0]);
    lene = lenc + 2;
    is_encrypta = v31;
    v32[1] = BYTE1(v34);
    *lene = v34 >> 16;
    v28 = v50;
    v35 = lene + 1;
    *v35 = BYTE3(v34);
    v36 = lene + 1;
    v35[1] = v33;
    v35[2] = BYTE1(v33);
    v36[3] = v33 >> 16;
    v36[4] = BYTE3(v33);
    v17 = v49-- == 1;
    lenc = lene + 6;
    v25 = v29;
    v48 = v29;
   } while (!v17);
   v24 = v47;
   v37 = v50;
   v27 = v46;
  }
  if (v27 == -8)
  {
   v44 = is_encrypta;
  }
  else
  {
   v38 = v37[5];
   v46 = (v37[3] << 24) | (v37[2] << 16) | (v37[1] << 8) | *v37;
   block[0] = v46;
   v39 = (v38 << 8) | v37[4];
   v40 = v37[6];
   v49 = v39;
   v49 = ((v40 | (v37[7] << 8)) << 16) | v39;
   block[1] = v49;
   rc5_transform2(block, key);
   v41 = v48 ^ block[0];
   is_encryptb = v31 ^ block[1];
   v42 = &lenc[v27 + 8];
   switch (v27)
   {
   case 0u:
    v43 = v31 ^ block[1];
    *--v42 = BYTE3(is_encryptb);
    goto LABEL_30;
   case 0xFFFFFFFF:
    v43 = v31 ^ block[1];
   LABEL_30:
    *--v42 = v43 >> 16;
    goto LABEL_32;
   case 0xFFFFFFFE:
    BYTE1(v43) = BYTE1(is_encryptb);
   LABEL_32:
    *--v42 = BYTE1(v43);
    goto LABEL_33;
   case 0xFFFFFFFD:
   LABEL_33:
    *--v42 = is_encryptb;
    goto LABEL_34;
   case 0xFFFFFFFC:
   LABEL_34:
    *--v42 = BYTE3(v41);
    goto LABEL_35;
   case 0xFFFFFFFB:
   LABEL_35:
    *--v42 = v41 >> 16;
    goto LABEL_36;
   case 0xFFFFFFFA:
   LABEL_36:
    *--v42 = BYTE1(v41);
    goto LABEL_37;
   case 0xFFFFFFF9:
   LABEL_37:
    *(v42 - 1) = v41;
    break;
   default:
    break;
   }
   v25 = v46;
   v44 = v49;
  }
  *v24 = v25;
  v24[1] = BYTE1(v25);
  v24[2] = v25 >> 16;
  v24[3] = BYTE3(v25);
  v24[4] = v44;
  v24[5] = BYTE1(v44);
  result = v44 >> 16;
  v24[6] = v44 >> 16;
  v24[7] = BYTE3(v44);
 }
 return result;
}
