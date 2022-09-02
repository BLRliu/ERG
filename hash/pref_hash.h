// *****************************************************************************
// 版权所有（C）2022-2023，风一样的网络
// 保留所有权利
// *****************************************************************************
// 作者 : 风一样的少年
// 版本 : 1.0
// 功能说明:
//           main
// *****************************************************************************
#ifndef HEAD_PREF_HASH_H
#define HEAD_PREF_HASH_H

struct pref_hash_context
{
	unsigned char seed[64];
	char machine_id[64];
};

unsigned char* GetSignaturesPublicKey(void* hHandle, char* name);
char* GetExtensionKey(unsigned char* SignaturesPublicKey);
char* GetExtensionID(unsigned char* SignaturesPublicKey);

int pref_hash_init(void* hHandle, struct pref_hash_context *context);
int pref_hash_calc(struct pref_hash_context *context, const char *path, const char *value, char *hash);

int pref_hash_init_v53(void* hHandle, struct pref_hash_context *context);
int pref_hash_calc_v53(struct pref_hash_context *context, const char *path, const char *value, char *hash);

int pref_hash_init_2345(struct pref_hash_context *context);
int pref_hash_calc_2345(struct pref_hash_context *context, const char *path, const char *value, char *hash);

#endif///HEAD_PREF_HASH_H