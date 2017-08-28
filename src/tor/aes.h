/#ifndef TOR_AES_H
#define TOR_AES_H

/**
 * \file aes.h
 * \brief Headers for aes.c
 */

struct aes_cnt_cipher;
typedef struct aes_cnt_cipher aes_cnt_cipher_t;

aes_cnt_cipher_t* aes_new_cipher(const char *key, const char *iv);
void aes_cipher_free(aes_cnt_cipher_t *cipher);
void aes_crypt(aes_cnt_cipher_t *cipher, const char *input, size_t len,
               char *output);
void aes_crypt_inplace(aes_cnt_cipher_t *cipher, char *data, size_t len);

int evaluate_evp_for_aes(int force_value);
int evaluate_ctr_for_aes(void);

#endif

