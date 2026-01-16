#include "randombytes.h"
#include "crypto_nP.h"
#include "fe25519.h"

#define mladder CRYPTO_SHARED_NAMESPACE(mladder)
extern void mladder(fe25519 *,fe25519 *,const unsigned long long *);

void crypto_nP(unsigned char *q, const unsigned char *n, const unsigned char *p) {

	fe25519 r[2];
	
	int i;
	unsigned long long s[4],*t;	
	
	t = (unsigned long long *)n;
	for (i=0;i<4;++i) s[i] = *(t + i);	
	
	fe25519_unpack(r,p);
  	mladder(r,r,s);
  	fe25519_invert(r+1,r+1);
  	fe25519_mul(r,r,r+1);
  	fe25519_pack(q,r);
}
