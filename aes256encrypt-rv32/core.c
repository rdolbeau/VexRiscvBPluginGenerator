/*
  core.c version $Date: 2014/12/12 09:04:41 $
  aes256encrypt
  Romain Dolbeau
  Public Domain
*/

#include "crypto_core.h"
#include "stdaes-common.h"


#define _bswap64(a) __builtin_bswap64(a)
#define _bswap(a) __builtin_bswap32(a)

#include "new_instructions_support_k.h"

#define AES_ROUND1T(TAB,I,X0,X1,X2,X3,Y0,Y1,Y2,Y3)		 \
  {								 \
    X0 = aes32esmi0(TAB[I++],Y0);				 \
    X0 = aes32esmi1(X0,Y1);					 \
    X0 = aes32esmi2(X0,Y2);					 \
    X0 = aes32esmi3(X0,Y3);					 \
    X1 = aes32esmi0(TAB[I++],Y1);				 \
    X1 = aes32esmi1(X1,Y2);					 \
    X1 = aes32esmi2(X1,Y3);					 \
    X1 = aes32esmi3(X1,Y0);					 \
    X2 = aes32esmi0(TAB[I++],Y2);				 \
    X2 = aes32esmi1(X2,Y3);					 \
    X2 = aes32esmi2(X2,Y0);					 \
    X2 = aes32esmi3(X2,Y1);					 \
    X3 = aes32esmi0(TAB[I++],Y3);				 \
    X3 = aes32esmi1(X3,Y0);					 \
    X3 = aes32esmi2(X3,Y1);					 \
    X3 = aes32esmi3(X3,Y2);					 \
  }
/* using the custom instructions */
static inline void aes256_1Tft_encrypt(const unsigned int *aes_edrk, const unsigned int *input, unsigned int *output)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = ((input[i++]) ^ aes_edrk[j++]);
  X1 = ((input[i++]) ^ aes_edrk[j++]);
  X2 = ((input[i++]) ^ aes_edrk[j++]);
  X3 = ((input[i++]) ^ aes_edrk[j++]);

  for (i = 4 ; i < (l_aes_nr<<2) ; ) {
    
    AES_ROUND1T(aes_edrk, i, Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

    X0=Y0;
    X1=Y1;
    X2=Y2;
    X3=Y3;
  }
  /* last round */

  Y0 = aes32esi0(aes_edrk[i], X0);
  Y0 = aes32esi1(Y0, X1);
  Y0 = aes32esi2(Y0, X2);
  Y0 = aes32esi3(Y0, X3);
  i++;
  Y1 = aes32esi0(aes_edrk[i], X1);
  Y1 = aes32esi1(Y1, X2);
  Y1 = aes32esi2(Y1, X3);
  Y1 = aes32esi3(Y1, X0);
  i++;
  Y2 = aes32esi0(aes_edrk[i], X2);
  Y2 = aes32esi1(Y2, X3);
  Y2 = aes32esi2(Y2, X0);
  Y2 = aes32esi3(Y2, X1);
  i++;
  Y3 = aes32esi0(aes_edrk[i], X3);
  Y3 = aes32esi1(Y3, X0);
  Y3 = aes32esi2(Y3, X1);
  Y3 = aes32esi3(Y3, X2);

  output[0] = (Y0);
  output[1] = (Y1);
  output[2] = (Y2);
  output[3] = (Y3);
}

static inline void aes256_1ft_encrypt(const unsigned int *aes_edrk, const unsigned int *input, unsigned int *output)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = (input[i++] ^ aes_edrk[j++]);
  X1 = (input[i++] ^ aes_edrk[j++]);
  X2 = (input[i++] ^ aes_edrk[j++]);
  X3 = (input[i++] ^ aes_edrk[j++]);

  for (i = 4 ; i < (l_aes_nr<<2) ; ) {
    
    AES_ROUND1(aes_edrk, i, Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

    X0=Y0;
    X1=Y1;
    X2=Y2;
    X3=Y3;
  }
  /* last round */
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  Y0 = aes_edrk[i] ^
    ( FSb[( X0 >> 24 ) &0xFF ] << 24 ) ^
    ( FSb[( X1 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X2 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X3       ) &0xFF ]       );
  
  Y1 = aes_edrk[1+i] ^
    ( FSb[( X1 >> 24 ) &0xFF ] << 24 ) ^
    ( FSb[( X2 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X3 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X0       ) &0xFF ]       );
  
  Y2 = aes_edrk[2+i] ^
    ( FSb[( X2 >> 24 ) &0xFF ] << 24 ) ^
    ( FSb[( X3 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X0 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X1       ) &0xFF ]       );
  
  Y3 = aes_edrk[3+i] ^
    ( FSb[( X3 >> 24 ) &0xFF ] << 24 ) ^
    ( FSb[( X0 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X1 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X2       ) &0xFF ]       );
#else
  Y0 = (aes_edrk[i]) ^
    ( FSb[( X0       ) &0xFF ]       ) ^
    ( FSb[( X1 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X2 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X3 >> 24 ) &0xFF ] << 24 );
  
  Y1 = (aes_edrk[1+i]) ^
    ( FSb[( X1       ) &0xFF ]       ) ^
    ( FSb[( X2 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X3 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X0 >> 24 ) &0xFF ] << 24 );
  
  Y2 = (aes_edrk[2+i]) ^
    ( FSb[( X2       ) &0xFF ]       ) ^
    ( FSb[( X3 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X0 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X1 >> 24 ) &0xFF ] << 24 );
  
  Y3 = (aes_edrk[3+i]) ^
    ( FSb[( X3       ) &0xFF ]       ) ^
    ( FSb[( X0 >>  8 ) &0xFF ] <<  8 ) ^
    ( FSb[( X1 >> 16 ) &0xFF ] << 16 ) ^
    ( FSb[( X2 >> 24 ) &0xFF ] << 24 );
#endif

  output[0] = (Y0);
  output[1] = (Y1);
  output[2] = (Y2);
  output[3] = (Y3);
}

int crypto_core(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
) {
  unsigned int rkeys[60];
  aes256_setkey_encrypt((const unsigned int*)k,rkeys);
  aes256_1Tft_encrypt(rkeys, (const unsigned int*)in, (unsigned int*)out);
  return 0;
}
