// *****************************************************************************
// ��Ȩ���У�C��2022-2023����һ��������
// ��������Ȩ��
// *****************************************************************************
// ���� : ��һ��������
// �汾 : 1.0
// ����˵��:
//           main
// *****************************************************************************
#ifndef RC5_H
#define RC5_H

int __cdecl rc5_initkey(unsigned int *ctx, unsigned int a2, unsigned __int8 *key, signed int a4);
unsigned int __cdecl rc5_encrypt(unsigned __int8 *src, unsigned __int8 *dst, unsigned int len, unsigned int *key, unsigned __int8 *iv, int is_encrypt);

unsigned int __cdecl rc5_encrypt_01(unsigned __int8 *src, unsigned __int8 *dst, unsigned int len, unsigned int *key, unsigned __int8 *iv, int is_encrypt);

#endif
