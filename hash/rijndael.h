// *****************************************************************************
// ��Ȩ���У�C��2022-2023����һ��������
// ��������Ȩ��
// *****************************************************************************
// ���� : ��һ��������
// �汾 : 1.0
// ����˵��:
//           main
// *****************************************************************************

#ifndef RIJNDAEL_H
#define RIJNDAEL_H

// ** Thread-safe implementation

// ** Aes cipher
// ** 128bit block size
// ** 256bit key

#define RKLENGTH(keybits)  ((keybits)/8+28)

int rijndael_set_key_encrypt(unsigned int *rk, const unsigned char *key, const int keybits);
int rijndael_set_key_decrypt(unsigned int *rk, const unsigned char *key, const int keybits);
void rijndael_encrypt(const unsigned int *rk, const int nrounds, const unsigned char *plaintext, unsigned char *ciphertext);
void rijndael_decrypt(const unsigned int *rk, const int nrounds, const unsigned char *ciphertext, unsigned char *plaintext);

#endif
