/* Simple keypair tool that calls the reference keypair function.
 *
 * Expects the ref10 symbols to be available:
 *   void crypto_sign_keypair(unsigned char *pk,unsigned char *sk);
 *
 * Prints private key (64 bytes) then public key (32 bytes) as hex to stdout.
 *
 * Place this file in /ref10build/ and run `make` (Makefile provided).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include the API header(s) used by the ref10 code */
#include "crypto_sign.h"

/* Forward declaration in case header differs: provide weak fallback.
   If the real function exists in the ref10 .c files, the linker will use it. */
#ifndef HAVE_CRYPTOSIGN_KEYPAIR_DECL
void crypto_sign_keypair(unsigned char *pk, unsigned char *sk);
#endif

static void printhex(const unsigned char *buf, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", buf[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;

    unsigned char pk[32];
    unsigned char sk[64];

    /* Some ref10 variants expect randombytes() to be present and used inside the keypair;
       ensure that randombytes.c is compiled into the tree (randombytes/devurandom.c) */

    /* Generate keypair */
    memset(pk, 0, sizeof pk);
    memset(sk, 0, sizeof sk);

    /* crypto_sign_keypair fills pk and sk. */
    crypto_sign_keypair(pk, sk);

    /* Print private (sk) and public (pk) as hex */
    printf("sk=");
    printhex(sk, sizeof sk);
    printf("pk=");
    printhex(pk, sizeof pk);

    return 0;
}