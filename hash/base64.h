// *****************************************************************************
// 版权所有（C）2022-2023，风一样的网络
// 保留所有权利
// *****************************************************************************
// 作者 : 风一样的少年
// 版本 : 1.0
// 功能说明:
//           main
// *****************************************************************************
#ifndef BASE64_H
#define BASE64_H

/**
 * Decode a base64-encoded string.
 *
 * @param out      buffer for decoded data
 * @param in       null-terminated input string
 * @param out_size size in bytes of the out buffer, must be at
 *                 least 3/4 of the length of in
 * @return         number of bytes written, or a negative value in case of
 *                 invalid input
 */
int base64_decode(unsigned char *out, const char *in, int out_size);
/**
 * Encode data to base64 and null-terminate.
 *
 * @param out      buffer for encoded data
 * @param out_size size in bytes of the out buffer (including the
 *                 null terminator), must be at least BASE64_SIZE(in_size)
 * @param in       input buffer containing the data to encode
 * @param in_size  size in bytes of the in buffer
 * @return         out or NULL in case of error
 */
char *base64_encode(char *out, int out_size, const unsigned char *in, int in_size);
char *base64_url_encode(char *out, int out_size, const unsigned char *in, int in_size);
/**
 * Calculate the output size needed to base64-encode x bytes to a
 * null-terminated string.
 */
#define BASE64_SIZE(x)  (((x)+2) / 3 * 4 + 1)

#endif
