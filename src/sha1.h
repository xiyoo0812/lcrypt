/**
* @file re_sha.h  Interface to SHA (Secure Hash Standard) functions
*
* Copyright (C) 2010 Creytiv.com
*/

#ifndef SHA_H_
#define SHA_H_
#include <stdint.h>
#include "lcrypt.h"

#define SHA_BLOCKSIZE   (64)

/* public api for steve reid's public domain SHA-1 implementation */
/* this file is in the public domain */

/** SHA-1 Context */
typedef struct {
    uint32_t state[5];
    /**< Context state */
    uint32_t count[2];
    /**< Counter       */
    uint8_t buffer[64]; /**< SHA-1 buffer  */
} SHA1_CTX;

/** SHA-1 Context (OpenSSL compat) */
typedef SHA1_CTX SHA_CTX;

/** SHA-1 Digest size in bytes */
#define SHA1_DIGEST_SIZE 20
/** SHA-1 Digest size in bytes (OpenSSL compat) */
#define SHA_DIGEST_LENGTH SHA1_DIGEST_SIZE

LCRYPT_API void SHA1_Init(SHA1_CTX *context);

LCRYPT_API void SHA1_Update(SHA1_CTX *context, const void *p, size_t len);

LCRYPT_API void SHA1_Final(uint8_t digest[SHA1_DIGEST_SIZE], SHA1_CTX *context);

LCRYPT_API void hmac_sha1(const uint8_t *k,   /* secret key */
        size_t lk,  /* length of the key in bytes */
        const uint8_t *d,   /* data */
        size_t ld,  /* length of data in bytes */
        uint8_t *out, /* output buffer, at least "t" bytes */
        size_t *t);

#endif // SHA_H_
