// *****************************************************************************
// ��Ȩ���У�C��2022-2023����һ��������
// ��������Ȩ��
// *****************************************************************************
// ���� : ��һ��������
// �汾 : 1.0
// ����˵��:
//           main
// *****************************************************************************

#ifndef _SHA1_H_
#define _SHA1_H_

/* 
 *  This structure will hold context information for the hashing
 *  operation
 */
typedef struct sha1_context
{
    unsigned Message_Digest[5]; /* Message Digest (output)          */

    unsigned Length_Low;        /* Message length in bits           */
    unsigned Length_High;       /* Message length in bits           */

    unsigned char Message_Block[64]; /* 512-bit message blocks      */
    int Message_Block_Index;    /* Index into message block array   */

    int Computed;               /* Is the digest computed?          */
    int Corrupted;              /* Is the message digest corruped?  */
} sha1_context;

/*
 *  Function Prototypes
 */
void sha1_init(sha1_context *);
int sha1_final(sha1_context *, unsigned char *);
void sha1_update(sha1_context *,
                const unsigned char *,
                unsigned);

#endif
