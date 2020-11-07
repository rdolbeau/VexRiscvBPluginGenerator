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

#define ASM1MACRO(N, O) asm(".macro "#N" rd, rs1\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15))\n"	\
			   ".endm\n");
#define ASM2MACRO(N, O) asm(".macro "#N" rd, rs1, rs2\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\rs2 << 20))\n"	\
			   ".endm\n");
asm("#define reg_zero 0\n");
asm("#define reg_ra 1\n");
asm("#define reg_sp 2\n");
asm("#define reg_gp 3\n");
asm("#define reg_tp 4\n");
asm("#define reg_t0 5\n");
asm("#define reg_t1 6\n");
asm("#define reg_t2 7\n");
asm("#define reg_s0 8\n");
asm("#define reg_s1 9\n");
asm("#define reg_a0 10\n");
asm("#define reg_a1 11\n");
asm("#define reg_a2 12\n");
asm("#define reg_a3 13\n");
asm("#define reg_a4 14\n");
asm("#define reg_a5 15\n");
asm("#define reg_a6 16\n");
asm("#define reg_a7 17\n");
asm("#define reg_s2 18\n");
asm("#define reg_s3 19\n");
asm("#define reg_s4 20\n");
asm("#define reg_s5 21\n");
asm("#define reg_s6 22\n");
asm("#define reg_s7 23\n");
asm("#define reg_s8 24\n");
asm("#define reg_s9 25\n");
asm("#define reg_s10 26\n");
asm("#define reg_s11 27\n");
asm("#define reg_t3 28\n");
asm("#define reg_t4 29\n");
asm("#define reg_t5 30\n");
asm("#define reg_t6 31\n");
  
ASM2MACRO(AESX0,0x0000000b)
ASM2MACRO(AESX1,0x0000100b)
ASM2MACRO(AESX2,0x0000200b)
ASM2MACRO(AESX3,0x0000300b)

#define FUN1(NAME, ASNAME)						\
  static inline uint32_t NAME(uint32_t rs1) {				\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1\n"					\
	 : "=r" (r)							\
	 : "r" (rs1));							\
    return r;								\
  }
#define FUN2(NAME, ASNAME)						\
  static inline uint32_t NAME(uint32_t rs1, uint32_t rs2) {		\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2\n"				\
	 : "=r" (r)							\
	 : "r" (rs1), "r" (rs2));					\
    return r;								\
  }

FUN2(aesx0,AESX0)
FUN2(aesx1,AESX1)
FUN2(aesx2,AESX2)
FUN2(aesx3,AESX3)

#define AES_ROUND1T(TAB,I,X0,X1,X2,X3,Y0,Y1,Y2,Y3)	 \
  {                                                      \
    X0 = aesx0(Y0,TAB[I++]);				 \
    X0 = aesx1(Y1,X0);					 \
    X0 = aesx2(Y2,X0);					 \
    X0 = aesx3(Y3,X0);					 \
    X1 = aesx0(Y1,TAB[I++]);				 \
    X1 = aesx1(Y2,X1);					 \
    X1 = aesx2(Y3,X1);					 \
    X1 = aesx3(Y0,X1);					 \
    X2 = aesx0(Y2,TAB[I++]);				 \
    X2 = aesx1(Y3,X2);					 \
    X2 = aesx2(Y0,X2);					 \
    X2 = aesx3(Y1,X2);					 \
    X3 = aesx0(Y3,TAB[I++]);				 \
    X3 = aesx1(Y0,X3);					 \
    X3 = aesx2(Y1,X3);					 \
    X3 = aesx3(Y2,X3);					 \
  }

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

/* using the custom instructions */
static inline void aes256_1Tft_encrypt(uint32_t *output, const uint32_t *input, const uint32_t *aes_edrk)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = (_bswap(input[1]) ^ aes_edrk[j++]);
  X1 = (_bswap(input[0]) ^ aes_edrk[j++]);
  X2 = (_bswap(input[3]) ^ aes_edrk[j++]);
  X3 = (_bswap(input[2]) ^ aes_edrk[j++]);

  for (i = 4 ; i < (l_aes_nr<<2) ; ) {
    
    AES_ROUND1T(aes_edrk, i, Y0, Y1, Y2, Y3, X0, X1, X2, X3 );

    X0=Y0;
    X1=Y1;
    X2=Y2;
    X3=Y3;
  }
  /* last round */
  /* the two middle bytes of FT0 are the FSb table.
     this re-use aesx* to get a byte in the proper spot
     so we can directly XOR with the keys */
  Y0 = (aesx2((X0 &       0xFF) << 16, aes_edrk[i]) &       0xFF) ^
       (aesx0((X1 &     0xFF00) >>  8, aes_edrk[i]) &     0xFF00) ^
       (aesx0((X2 &   0xFF0000) >> 16, aes_edrk[i]) &   0xFF0000) ^
       (aesx2((X3 & 0xFF000000) >>  8, aes_edrk[i]) & 0xFF000000);
  i++;
  Y1 = (aesx2((X1 &       0xFF) << 16, aes_edrk[i]) &       0xFF) ^
       (aesx0((X2 &     0xFF00) >>  8, aes_edrk[i]) &     0xFF00) ^
       (aesx0((X3 &   0xFF0000) >> 16, aes_edrk[i]) &   0xFF0000) ^
       (aesx2((X0 & 0xFF000000) >>  8, aes_edrk[i]) & 0xFF000000);
  i++;
  Y2 = (aesx2((X2 &       0xFF) << 16, aes_edrk[i]) &       0xFF) ^
       (aesx0((X3 &     0xFF00) >>  8, aes_edrk[i]) &     0xFF00) ^
       (aesx0((X0 &   0xFF0000) >> 16, aes_edrk[i]) &   0xFF0000) ^
       (aesx2((X1 & 0xFF000000) >>  8, aes_edrk[i]) & 0xFF000000);
  i++;
  Y3 = (aesx2((X3 &       0xFF) << 16, aes_edrk[i]) &       0xFF) ^
       (aesx0((X0 &     0xFF00) >>  8, aes_edrk[i]) &     0xFF00) ^
       (aesx0((X1 &   0xFF0000) >> 16, aes_edrk[i]) &   0xFF0000) ^
       (aesx2((X2 & 0xFF000000) >>  8, aes_edrk[i]) & 0xFF000000);

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
    aes256_1Tft_encrypt(outni, n2, rkeys);		 \
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
    aes256_1Tft_encrypt(outni, n2, rkeys);		     \
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
