/*
  rv32.c
  AES-CTR
  Romain Dolbeau
  Public Domain
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto_stream.h"
#include "stdaes-common.h"

#include <stdint.h>

#define _bswap64(a) __builtin_bswap64(a)
#define _bswap(a) __builtin_bswap32(a)

static inline void aes256_4ft_encrypt(uint32_t *output, const uint32_t *input, const uint32_t *aes_edrk)
{
  uint32_t X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  uint32_t i = 0, j = 0;
  uint32_t l_aes_nr = 14;

  X0 = (_bswap(input[1]) ^ aes_edrk[j++]);
  X1 = (_bswap(input[0]) ^ aes_edrk[j++]);
  X2 = (_bswap(input[3]) ^ aes_edrk[j++]);
  X3 = (_bswap(input[2]) ^ aes_edrk[j++]);

  for (i = 4 ; i < (l_aes_nr<<2) ; ) {
    
    AES_ROUND4(aes_edrk, i, Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

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

static inline void aes256_1ft_encrypt(uint32_t *output, const uint32_t *input, const uint32_t *aes_edrk)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = (_bswap(input[1]) ^ aes_edrk[j++]);
  X1 = (_bswap(input[0]) ^ aes_edrk[j++]);
  X2 = (_bswap(input[3]) ^ aes_edrk[j++]);
  X3 = (_bswap(input[2]) ^ aes_edrk[j++]);

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


int crypto_stream(
uint8_t *out,
uint64_t outlen,
const uint8_t *n,
const uint8_t *k
)
{
  uint32_t rkeys[64];
  uint64_t n2[2];
  uint64_t i, j;
  aes256_setkey_encrypt(k, rkeys);
  /* n2 is in byte-reversed (i.e., native little endian)
     order to make increment/testing easier */
  n2[1] = _bswap64((*(uint64_t*)&n[8]));
  n2[0] = _bswap64((*(uint64_t*)&n[0]));
  
#define LOOP(iter)                                       \
  int lb = iter * 16;                                    \
  for (i = 0 ; i < outlen ; i+= lb) {                    \
    uint8_t outni[lb];					 \
    aes256_4ft_encrypt(outni, n2, rkeys);		 \
    n2[1]++;						 \
    if (n2[1] == 0)					 \
      n2[0]++;						 \
    uint64_t mj = lb;					 \
    if ((i+mj)>=outlen)                                  \
      mj = outlen-i;                                     \
    for (j = 0 ; j < mj ; j++)                           \
      out[i+j] = outni[j];                               \
  }
  
  LOOP(1);

  return 0;
}

int crypto_stream_xor(
uint8_t *out,
const uint8_t *in,
uint64_t inlen,
const uint8_t *n,
const uint8_t *k
)
{
  uint32_t rkeys[64];
  uint64_t n2[2];
  uint64_t i, j;
  aes256_setkey_encrypt(k, rkeys);
  /* n2 is in byte-reversed (i.e., native little endian)
     order to make increment/testing easier */
  n2[1] = _bswap64((*(uint64_t*)&n[8]));
  n2[0] = _bswap64((*(uint64_t*)&n[0]));
  
#define LOOPXOR(iter)					     \
  int32_t lb = iter * 16;                                    \
  for (i = 0 ; i < inlen ; i+= lb) {			     \
    uint8_t outni[lb];					     \
    aes256_4ft_encrypt(outni, n2, rkeys);		     \
    n2[1]++;						     \
    if (n2[1] == 0)					     \
      n2[0]++;						     \
    uint64_t mj = lb;					     \
    if ((i+mj)>=inlen)					     \
      mj = inlen-i;					     \
    for (j = 0 ; j < mj ; j++)				     \
      out[i+j] = in[i+j] ^ outni[j];			     \
  }
  
  LOOPXOR(1);

  return 0;
}
