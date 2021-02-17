/* 
// CAESAR OCB v1 somewhat optimised code
// Info: http://www.cs.ucdavis.edu/~rogaway/ocb
//
// Written by Romain Dolbeau (romain@dolbeau.org),
// based on the reference implementation by Ted Krovetz (ted@krovetz.net).
//
// Phillip Rogaway holds patents relevant to OCB. See the following for
// his free patent grant: http://www.cs.ucdavis.edu/~rogaway/ocb/grant.htm
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
*/

#include <string.h>

#include "api.h"
#include "crypto_aead.h"
#define KEYBYTES   CRYPTO_KEYBYTES
#define NONCEBYTES CRYPTO_NPUBBYTES
#define TAGBYTES   CRYPTO_ABYTES

#define ALIGN16  __attribute__((aligned(16)))
#define ALIGN32  __attribute__((aligned(32)))
#define ALIGN64  __attribute__((aligned(64)))
#define _bswap64(a) __builtin_bswap64(a)
#define _bswap(a) __builtin_bswap32(a)

#define printv16c(p,v)                                                  \
  {                                                                     \
    ALIGN16 unsigned char temp[16];                       \
    _mm_store_si128(temp, v);                                           \
    int z;                                                              \
    printf("%8s:%8s = ",p,#v);                                          \
    for (z = 15 ; z >= 0 ; z--) {                                       \
      printf("%02hhx", temp[z]);                                        \
      if ((z%4)==0) printf(" ");                                        \
    }                                                                   \
    printf("\n");                                                       \
  }

#include "m128_compat.h"

#include "new_instructions_support_k.h"

#define rotr(a,b) _rv32_ror(a,b)

static inline void aes256_Tsetkey_encrypt(const unsigned int key[], unsigned int *aes_edrk) {
  unsigned int i = 0;
  unsigned int rotl_aes_edrk;
  unsigned int tmp8, tmp9, tmp10, tmp11;
  unsigned int tmp12, tmp13, tmp14, tmp15;
  unsigned int temp_lds;
  unsigned int round = 0x00000001;

  tmp8  = (key[0]);
  aes_edrk[0] = tmp8;
  tmp9  = (key[1]);
  aes_edrk[1] = tmp9;
  tmp10 = (key[2]);
  aes_edrk[2] = tmp10;
  tmp11 = (key[3]);
  aes_edrk[3] = tmp11;
  tmp12 = (key[4]);
  aes_edrk[4] = tmp12;
  tmp13 = (key[5]);
  aes_edrk[5] = tmp13;
  tmp14 = (key[6]);
  aes_edrk[6] = tmp14;
  tmp15 = (key[7]);
  aes_edrk[7] = tmp15;

  for( i = 8; i < 56; /* i+=8 */ )
  {
	tmp8 = tmp8 ^ round;
	round = round << 1;
	rotl_aes_edrk = rotr(tmp15,8);
	tmp8 = aes32esi0(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi1(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi2(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi3(tmp8, rotl_aes_edrk);

    aes_edrk[i++]   = tmp8;
    tmp9  = tmp9  ^ tmp8;
    aes_edrk[i++]   = tmp9;
    tmp10 = tmp10 ^ tmp9;
    aes_edrk[i++]  = tmp10;
    tmp11 = tmp11 ^ tmp10;
    aes_edrk[i++]  = tmp11;

	tmp12 = aes32esi0(tmp12, tmp11);
	tmp12 = aes32esi1(tmp12, tmp11);
	tmp12 = aes32esi2(tmp12, tmp11);
	tmp12 = aes32esi3(tmp12, tmp11);
	
    aes_edrk[i++]  = tmp12;
    tmp13 = tmp13 ^ tmp12;
    aes_edrk[i++]  = tmp13;
    tmp14 = tmp14 ^ tmp13;
    aes_edrk[i++]  = tmp14;
    tmp15 = tmp15 ^ tmp14;
    aes_edrk[i++]  = tmp15;
  }

  tmp8 = tmp8 ^ round;
  round = round << 1;
  rotl_aes_edrk = rotr(tmp15,8);
  tmp8 = aes32esi0(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi1(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi2(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi3(tmp8, rotl_aes_edrk);
  
  aes_edrk[i++]   = tmp8;
  tmp9  = tmp9  ^ tmp8;
  aes_edrk[i++]   = tmp9;
  tmp10 = tmp10 ^ tmp9;
  aes_edrk[i++]  = tmp10;
  tmp11 = tmp11 ^ tmp10;
  aes_edrk[i++]  = tmp11;
}

static void aes256_key_enc2dec(unsigned int *erk, unsigned int *drk)
{
	int i, j;
	// first and last unchanged (but swapped)
	for (i = 0; i < 4; i++) {
		drk[i] = erk[i+56];
		drk[i+56] = erk[i];
	}
	// convert & revert order
	for (i = 1; i < 14; i++) {
		for (j = 0 ; j < 4 ; j++) {
			unsigned int ek, dk;
			ek = erk[i*4+j];
			
			dk = 0;
			dk = aes32esi0(dk, ek);
			dk = aes32esi1(dk, ek);
			dk = aes32esi2(dk, ek);
			dk = aes32esi3(dk, ek);
			
			ek = 0;
			ek = aes32dsmi0(ek, dk);
			ek = aes32dsmi1(ek, dk);
			ek = aes32dsmi2(ek, dk);
			ek = aes32dsmi3(ek, dk);
			
			drk[56-4*i+j] = ek;
		}
	}
}

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

/* using the K + B instructions */
static inline void aes256_1Tft_encrypt(const uint32_t *aes_edrk, const uint32_t *input, uint32_t *output)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = ((input[0]) ^ aes_edrk[j++]);
  X1 = ((input[1]) ^ aes_edrk[j++]);
  X2 = ((input[2]) ^ aes_edrk[j++]);
  X3 = ((input[3]) ^ aes_edrk[j++]);

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


#define AES_ROUND_DKT(TAB,I,X0,X1,X2,X3,Y0,Y1,Y2,Y3)	\
	{												\
		X0 = aes32dsmi0(TAB[I+0],Y0);				\
		X0 = aes32dsmi1(X0,Y3);						\
		X0 = aes32dsmi2(X0,Y2);						\
		X0 = aes32dsmi3(X0,Y1);						\
		X1 = aes32dsmi0(TAB[I+1],Y1);				\
		X1 = aes32dsmi1(X1,Y0);						\
		X1 = aes32dsmi2(X1,Y3);						\
		X1 = aes32dsmi3(X1,Y2);						\
		X2 = aes32dsmi0(TAB[I+2],Y2);				\
		X2 = aes32dsmi1(X2,Y1);						\
		X2 = aes32dsmi2(X2,Y0);						\
		X2 = aes32dsmi3(X2,Y3);						\
		X3 = aes32dsmi0(TAB[I+3],Y3);				\
		X3 = aes32dsmi1(X3,Y2);						\
		X3 = aes32dsmi2(X3,Y1);						\
		X3 = aes32dsmi3(X3,Y0);						\
	}

void aes256_1Tft_decrypt(const unsigned int *aes_drk, const unsigned int *input, unsigned int *output)
{
	const unsigned int aes_nr = 14; // aes256
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i;

  X0 = input[0]; X0 ^= aes_drk[0];
  X1 = input[1]; X1 ^= aes_drk[1];
  X2 = input[2]; X2 ^= aes_drk[2];
  X3 = input[3]; X3 ^= aes_drk[3];
  
  //    for (i=1;i<aes_nr;i++)
  i=1;
  do
      {
        AES_ROUND_DKT(aes_drk, (i<<2), Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 1 */
        X0=Y0;
        X1=Y1;
        X2=Y2;
        X3=Y3;
        i++;
      }
      while(i<aes_nr);
    i=(i<<2);

    /* last round */

	Y0 = aes32dsi0(aes_drk[i+0], X0);
	Y0 = aes32dsi1(Y0, X3);
	Y0 = aes32dsi2(Y0, X2);
	Y0 = aes32dsi3(Y0, X1);
	Y1 = aes32dsi0(aes_drk[i+1], X1);
	Y1 = aes32dsi1(Y1, X0);
	Y1 = aes32dsi2(Y1, X3);
	Y1 = aes32dsi3(Y1, X2);
	Y2 = aes32dsi0(aes_drk[i+2], X2);
	Y2 = aes32dsi1(Y2, X1);
	Y2 = aes32dsi2(Y2, X0);
	Y2 = aes32dsi3(Y2, X3);
	Y3 = aes32dsi0(aes_drk[i+3], X3);
	Y3 = aes32dsi1(Y3, X2);
	Y3 = aes32dsi2(Y3, X1);
	Y3 = aes32dsi3(Y3, X0);
	
    output[0] = Y0;
    output[1] = Y1;
    output[2] = Y2;
    output[3] = Y3;
}


/** single, by-the-book AES encryption with AES-NI */
static inline __m128i aes256_1Tft__encrypt1_si128(const __m128i nv, const __m128i rkeys[15]) {
	__m128i temp;
	aes256_1Tft_encrypt(rkeys, &nv, &temp);
	return temp;
}
static inline __m128i aes256_1Tft__decrypt1_si128(const __m128i nv, const __m128i rkeys[15]) {
	__m128i temp;
	aes256_1Tft_decrypt(rkeys, &nv, &temp);
	return temp;
}

typedef unsigned char block[16];

/* ------------------------------------------------------------------------- */

#if 0
static inline void xor_block(block d, block s1, block s2) {
    unsigned i;
    for (i=0; i<16; i++)
        d[i] = s1[i] ^ s2[i];
}
#else
/* 128 bits SSE doubling */
static inline void xor_block(unsigned char* d, const unsigned char* s1, const unsigned char* s2) {
  __m128i dv = _mm_xor_si128(_mm_loadu_si128((const __m128i*)s1), _mm_loadu_si128((const __m128i*)s2));
  _mm_storeu_si128((__m128i*)d,dv);
}
#endif

/* ------------------------------------------------------------------------- */

#if 0
static inline void double_block(block d, block s) {
    unsigned i;
    unsigned char tmp = s[0];
    for (i=0; i<15; i++)
        d[i] = (s[i] << 1) | (s[i+1] >> 7);
    d[15] = (s[15] << 1) ^ ((tmp >> 7) * 135);
}
#else
#if 0
/* 64 bits little-endian doubling, faster */
static inline void double_block(unsigned long long *d, const unsigned long long* s) {
  unsigned long long sl = _bswap64(s[1]), sh = _bswap64(s[0]);
  unsigned long long sl1 = sl << 1;
  unsigned long long sh1 = sh << 1;
  sh1 |= sl>>63;
  sl1 ^= (((long long)sh>>63) & 135);
  d[1]=_bswap64(sl1);
  d[0]=_bswap64(sh1);
}
#else
/* 128 bits SSE, much faster */
static inline __m128i double_block_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(135,1,1,1);
  /* __m128i sv31 = _mm_srai_epi32(sv, 31); */
  __m128i sv31 = wordsign128(sv);
  __m128i sv31m = _mm_and_si128(sv31, mask);
 /*  __m128i sv31ms = _mm_shuffle_epi32(sv31m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv31ms = wordrotate1l128(sv31m);
  __m128i sv1 = _mm_slli_epi32(sv, 1);
  __m128i dv = _mm_xor_si128(sv31ms,sv1);
  return dv;
}
static inline __m128i double_block_si128(const __m128i svr) {
  /* const __m128i rev = _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15); */
  /* __m128i sv = _mm_shuffle_epi8(svr, rev); */
  __m128i sv = bytereverse128(svr);
  __m128i dv = double_block_si128_norev(sv);
  /* return  _mm_shuffle_epi8(dv, rev); */
  return bytereverse128(dv);
}
static inline void double_block(unsigned char *d, const unsigned char* s) {
	__m128i sv = _mm_loadu_si128((const __m128i*)s);
	__m128i dv = double_block_si128(sv);
	_mm_storeu_si128((__m128i*)d,dv);
}
/* 128 bits SSE times 4 */
static const unsigned short lk4[64] = {
0x0000, 0x0086, 0x010c, 0x018a, 0x0218, 0x029e, 0x0314, 0x0392,
0x0430, 0x04b6, 0x053c, 0x05ba, 0x0628, 0x06ae, 0x0724, 0x07a2,
0x0860, 0x08e6, 0x096c, 0x09ea, 0x0a78, 0x0afe, 0x0b74, 0x0bf2,
0x0c50, 0x0cd6, 0x0d5c, 0x0dda, 0x0e48, 0x0ece, 0x0f44, 0x0fc2,
0x10c0, 0x1046, 0x11cc, 0x114a, 0x12d8, 0x125e, 0x13d4, 0x1352,
0x14f0, 0x1476, 0x15fc, 0x157a, 0x16e8, 0x166e, 0x17e4, 0x1762,
0x18a0, 0x1826, 0x19ac, 0x192a, 0x1ab8, 0x1a3e, 0x1bb4, 0x1b32,
0x1c90, 0x1c16, 0x1d9c, 0x1d1a, 0x1e88, 0x1e0e, 0x1f84, 0x1f02
};
static inline __m128i double_block_2_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(3,3,3,3);
  const int idx = _mm_extract_epi8(sv,15);
  /* __m128i sv30x = _mm_insert_epi16(_mm_setzero_si128(),lk4[(idx&0xC0)>>6],0); */
  __m128i sv30x = halfwordandzero(lk4[(idx&0xC0)>>6]);

  __m128i sv30 = _mm_srli_epi32(sv, 30);
  __m128i sv30m = _mm_and_si128(sv30, mask);
  /* __m128i sv30ms = _mm_shuffle_epi32(sv30m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv30ms = wordrotate1l128(sv30m);
  __m128i sv2 = _mm_slli_epi32(sv, 2);
  __m128i dv = _mm_xor_si128(sv30ms,sv2);
  __m128i final =  _mm_xor_si128(dv, sv30x);
  return final;
}
static inline __m128i double_block_3_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(7,7,7,7);
  const int idx = _mm_extract_epi8(sv,15);
  /* __m128i sv29x = _mm_insert_epi16(_mm_setzero_si128(),lk4[(idx&0xE0)>>5],0); */
  __m128i sv29x = halfwordandzero(lk4[(idx&0xE0)>>5]);

  __m128i sv29 = _mm_srli_epi32(sv, 29);
  __m128i sv29m = _mm_and_si128(sv29, mask);
  /* __m128i sv29ms = _mm_shuffle_epi32(sv29m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv29ms = wordrotate1l128(sv29m);
  __m128i sv3 = _mm_slli_epi32(sv, 3);
  __m128i dv = _mm_xor_si128(sv29ms,sv3);
  __m128i final =  _mm_xor_si128(dv, sv29x);
  return final;
}
static inline __m128i double_block_4_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(15,15,15,15);
  const int idx = _mm_extract_epi8(sv,15);
  /* __m128i sv28x = _mm_insert_epi16(_mm_setzero_si128(),lk4[(idx&0xF0)>>4],0); */
  __m128i sv28x = halfwordandzero(lk4[(idx&0xF0)>>4]);

  __m128i sv28 = _mm_srli_epi32(sv, 28);
  __m128i sv28m = _mm_and_si128(sv28, mask);
  /* __m128i sv28ms = _mm_shuffle_epi32(sv28m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv28ms = wordrotate1l128(sv28m);
  __m128i sv4 = _mm_slli_epi32(sv, 4);
  __m128i dv = _mm_xor_si128(sv28ms,sv4);
  __m128i final =  _mm_xor_si128(dv, sv28x);
  return final;
}
static inline __m128i double_block_5_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(31,31,31,31);
  const int idx = _mm_extract_epi8(sv,15);
  /* __m128i sv27x = _mm_insert_epi16(_mm_setzero_si128(),lk4[(idx&0xF8)>>3],0); */
  __m128i sv27x = halfwordandzero(lk4[(idx&0xF8)>>3]);

  __m128i sv27 = _mm_srli_epi32(sv, 27);
  __m128i sv27m = _mm_and_si128(sv27, mask);
  /* __m128i sv27ms = _mm_shuffle_epi32(sv27m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv27ms = wordrotate1l128(sv27m);
  __m128i sv5 = _mm_slli_epi32(sv, 5);
  __m128i dv = _mm_xor_si128(sv27ms,sv5);
  __m128i final =  _mm_xor_si128(dv, sv27x);
  return final;
}
static inline __m128i double_block_6_si128_norev(const __m128i sv) {
  const __m128i mask = _mm_set_epi32(63,63,63,63);
  const int idx = _mm_extract_epi8(sv,15);
  /* __m128i sv26x = _mm_insert_epi16(_mm_setzero_si128(),lk4[(idx&0xFC)>>2],0); */
  __m128i sv26x = halfwordandzero(lk4[(idx&0xFC)>>2]);

  __m128i sv26 = _mm_srli_epi32(sv, 26);
  __m128i sv26m = _mm_and_si128(sv26, mask);
  /* __m128i sv26ms = _mm_shuffle_epi32(sv26m, _MM_SHUFFLE(2,1,0,3)); */
  __m128i sv26ms = wordrotate1l128(sv26m);
  __m128i sv6 = _mm_slli_epi32(sv, 6);
  __m128i dv = _mm_xor_si128(sv26ms,sv6);
  __m128i final =  _mm_xor_si128(dv, sv26x);
  return final;
}
#endif
#endif

/* ------------------------------------------------------------------------- */
static inline __m128i calc_L_i_si128(const __m128i ldollarvr, const unsigned j) {
  /* const __m128i rev = _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15); */
  /* __m128i ldollarv = _mm_shuffle_epi8(ldollarvr, rev); */
  __m128i ldollarv = bytereverse128(ldollarvr);
  unsigned i;
  __m128i lv;
  unsigned ntz = __builtin_ctz(j);/* printf("ntz = %u\n", ntz); */
  switch(ntz) {
	case 0:
      lv = double_block_si128_norev(ldollarv);
	break;
	case 1:
      lv = double_block_2_si128_norev(ldollarv);
	break;
	case 2:
      lv = double_block_3_si128_norev(ldollarv);
	break;
	case 3:
      lv = double_block_4_si128_norev(ldollarv);
	break;
	case 4:
      lv = double_block_5_si128_norev(ldollarv);
	break;
 	default:
      lv = double_block_6_si128_norev(ldollarv);
      for (i = 5; i < ntz ; i++)
        lv = double_block_si128_norev(lv);
	break;
      }
  /* return _mm_shuffle_epi8(lv, rev); */
  return bytereverse128(lv);
}
static inline void calc_L_i(block l, const block ldollar, const unsigned i) {
  __m128i ldollarv = _mm_loadu_si128((const __m128i*)ldollar);
  __m128i lv = calc_L_i_si128(ldollarv, i);
  _mm_storeu_si128((__m128i*)l,lv);
}
static inline void precompute_lv(__m128i prelv[32], const __m128i ldollarvr, const unsigned max) {
  /* const __m128i rev = _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15); */
  /* __m128i ldollarv = _mm_shuffle_epi8(ldollarvr, rev); */
  __m128i ldollarv = bytereverse128(ldollarvr);
  unsigned i;
  __m128i lv = double_block_si128_norev(ldollarv);
  for (i = 0 ; i < max-1 ; i++) {
	/* prelv[i] = _mm_shuffle_epi8(lv, rev); */
	prelv[i] = bytereverse128(lv);
	lv = double_block_si128_norev(lv);
  }
  /* prelv[i] = _mm_shuffle_epi8(lv, rev); */
  return bytereverse128(lv);
}

/* ------------------------------------------------------------------------- */

static void hash(block result, const unsigned char *k,
                 unsigned char *a, unsigned abytes,
		 const __m128i lstar,
		 const __m128i prelv[32], const __m128i aes_key[15]) {
    __m128i  offset, sum, tmp;
    unsigned i;
    
    /* Process any whole blocks */
    /* Sum_0 = zeros(128) */
    sum = _mm_setzero_si128();
    /* Offset_0 = zeros(128) */
    offset = _mm_setzero_si128();
    i=1;
    for (; i<=abytes/16; i++, a = a + 16) {
        /* Offset_i = Offset_{i-1} xor L_{ntz(i)} */
	tmp = prelv[__builtin_ctz(i)];
        offset = _mm_xor_si128(offset, tmp);
        /* Sum_i = Sum_{i-1} xor ENCIPHER(K, A_i xor Offset_i) */
        tmp = _mm_xor_si128(offset, _mm_loadu_si128((const __m128i*)a));
        tmp = aes256_1Tft__encrypt1_si128(tmp, aes_key);
        sum = _mm_xor_si128(sum, tmp);
    }

    /* Process any final partial block; compute final hash value */

    abytes = abytes % 16;  /* Bytes in final block */
    if (abytes > 0) {
        /* Offset_* = Offset_m xor L_* */
        offset = _mm_xor_si128(offset, lstar);
        /* tmp = (A_* || 1 || zeros(127-bitlen(A_*))) xor Offset_* */
        unsigned char pad[16];
        memset(pad, 0, 16);
        memcpy(pad, a, abytes);
        pad[abytes] = 0x80;
        tmp = _mm_loadu_si128((const __m128i*)pad);
        tmp = _mm_xor_si128(offset, tmp);
        /* Sum = Sum_m xor ENCIPHER(K, tmp) */
        tmp = aes256_1Tft__encrypt1_si128(tmp, aes_key);
        sum = _mm_xor_si128(tmp, sum);
    }
    
    _mm_storeu_si128((__m128i*)result,sum);
}

/* ------------------------------------------------------------------------- */

static int ocb_crypt(unsigned char *out, unsigned char *k, unsigned char *n,
                     unsigned char *a, unsigned abytes,
                     unsigned char *in, unsigned inbytes, int encrypting) {
    __m128i prelv[32];
    __m128i aes_decrypt_key[15];
    __m128i aes_encrypt_key[15];
    block ad_hash;
    __m128i lstar, ldollar, sum, offset, ktop, pad, nonce, tag, tmp, outv;
    block nonce_b, offset_b;
    unsigned char stretch[24];
    unsigned bottom, byteshift, bitshift, i, max;
    
    /* Setup AES and strip ciphertext of its tag */
    if ( ! encrypting ) {
         if (inbytes < TAGBYTES) return -1;
         inbytes -= TAGBYTES;
    }
    aes256_Tsetkey_encrypt(k, aes_encrypt_key);
    if ( ! encrypting ) {
	aes256_key_enc2dec(aes_encrypt_key, aes_decrypt_key);
    }
     
    /* Key-dependent variables */

    /* L_* = ENCIPHER(K, zeros(128)) */
    tmp = _mm_setzero_si128();
    lstar = aes256_1Tft__encrypt1_si128(tmp, aes_encrypt_key);
    /* L_$ = double(L_*) */
    ldollar = double_block_si128(lstar); 
    max = abytes >= inbytes ? abytes/4 : inbytes/4;
    max = (max < 2 ? 2 : max);
    /* only precompute what's really needed;
       look at the number of leading zero (to find the leftmost bit set to one)
       all trailing zero will be at the right of it so we have an upper bound
    */
    precompute_lv(prelv,ldollar,31-__builtin_clz(max));

    /* Nonce-dependent and per-encryption variables */

    /* Nonce = zeros(127-bitlen(N)) || 1 || N */
    memset(nonce_b, 0, 16);
    memcpy(&nonce_b[16-NONCEBYTES],n,NONCEBYTES);
    nonce_b[0] = (unsigned char)(((TAGBYTES * 8) % 128) << 1);
    nonce_b[16-NONCEBYTES-1] |= 0x01;
    /* bottom = str2num(Nonce[123..128]) */
    bottom = nonce_b[15] & 0x3F;
    /* Ktop = ENCIPHER(K, Nonce[1..122] || zeros(6)) */
    nonce_b[15] &= 0xC0;
    nonce = _mm_loadu_si128((const __m128i*)nonce_b);
    ktop = aes256_1Tft__encrypt1_si128(nonce, aes_encrypt_key);
    /* Stretch = Ktop || (Ktop[1..64] xor Ktop[9..72]) */
    _mm_storeu_si128((__m128i*)stretch, ktop);
    _mm_storel_epi64((__m128i*)(stretch+16), _mm_xor_si128(_mm_srli_si128(ktop,1), ktop));
    /* Offset_0 = Stretch[1+bottom..128+bottom] */
    byteshift = bottom/8;
    bitshift  = bottom%8;
    if (bitshift != 0)
        for (i=0; i<16; i++)
            offset_b[i] = (stretch[i+byteshift] << bitshift) |
                        (stretch[i+byteshift+1] >> (8-bitshift));
    else
        for (i=0; i<16; i++)
            offset_b[i] = stretch[i+byteshift];
    offset = _mm_loadu_si128((const __m128i*)offset_b);
    /* Checksum_0 = zeros(128) */
    sum = _mm_xor_si128(sum,sum);

    /* Hash associated data */
    hash(ad_hash, k, a, abytes, lstar, prelv, aes_encrypt_key);

    /* Process any whole blocks */
    i=1;
    if (encrypting) {

      for (; i<=inbytes/16; i++, in=in+16, out=out+16) {
        /* Offset_i = Offset_{i-1} xor L_{ntz(i)} */
        tmp = prelv[__builtin_ctz(i)];
 
        offset = _mm_xor_si128(offset, tmp);
        tmp = _mm_xor_si128(offset, _mm_loadu_si128((const __m128i*)in));
        
        /* Checksum_i = Checksum_{i-1} xor P_i */
        sum = _mm_xor_si128(_mm_loadu_si128((const __m128i*)in), sum);
        /* C_i = Offset_i xor ENCIPHER(K, P_i xor Offset_i) */
        tmp = aes256_1Tft__encrypt1_si128(tmp, aes_encrypt_key);
        outv = _mm_xor_si128(offset, tmp);
        _mm_storeu_si128((__m128i*)out, outv);
      }
    } else {

      for (; i<=inbytes/16; i++, in=in+16, out=out+16) {
        /* Offset_i = Offset_{i-1} xor L_{ntz(i)} */
        tmp= prelv[__builtin_ctz(i)];
        offset = _mm_xor_si128(offset, tmp);        
        tmp = _mm_xor_si128(offset, _mm_loadu_si128((const __m128i*)in));

        /* P_i = Offset_i xor DECIPHER(K, C_i xor Offset_i) */
        tmp = aes256_1Tft__decrypt1_si128(tmp, aes_decrypt_key);
        outv = _mm_xor_si128(offset, tmp);
        _mm_storeu_si128((__m128i*)out, outv);
        /* Checksum_i = Checksum_{i-1} xor P_i */
        sum = _mm_xor_si128(outv, sum);
      }
    }

    /* Process any final partial block and compute raw tag */

    inbytes = inbytes % 16;  /* Bytes in final block */
    if (inbytes > 0) {
        /* Offset_* = Offset_m xor L_* */
        offset = _mm_xor_si128(offset, lstar);
        /* Pad = ENCIPHER(K, Offset_*) */
        pad = aes256_1Tft__encrypt1_si128(offset, aes_encrypt_key);
        
        if (encrypting) {
            /* Checksum_* = Checksum_m xor (P_* || 1 || zeros(127-bitlen(P_*))) */
            unsigned char tmp_b[16];
            unsigned char pad_b[16];
            memset(tmp_b, 0, 16);
            memcpy(tmp_b, in, inbytes);
            tmp_b[inbytes] = 0x80;
            tmp = _mm_loadu_si128((const __m128i*)tmp_b);
            sum = _mm_xor_si128(tmp, sum);
            /* C_* = P_* xor Pad[1..bitlen(P_*)] */
            pad = _mm_xor_si128(tmp, pad);
            _mm_storeu_si128((__m128i*)pad_b, pad);
            memcpy(out, pad_b, inbytes);
            out = out + inbytes;
        } else {
            /* P_* = C_* xor Pad[1..bitlen(C_*)] */
            unsigned char tmp_b[16];
            unsigned char pad_b[16];
            _mm_storeu_si128((__m128i*)pad_b, pad);
            memcpy(tmp_b, pad_b, 16);
            memcpy(tmp_b, in, inbytes);
            xor_block(tmp_b,pad_b,tmp_b);
            tmp_b[inbytes] = 0x80;
            memcpy(out, tmp_b, inbytes);
            tmp = _mm_loadu_si128((const __m128i*)tmp_b);
            /* Checksum_* = Checksum_m xor (P_* || 1 || zeros(127-bitlen(P_*))) */
            sum = _mm_xor_si128(tmp, sum);
            in = in + inbytes;
        }
    }
    
    /* Tag = ENCIPHER(K, Checksum xor Offset xor L_$) xor HASH(K,A) */
    tmp = _mm_xor_si128(sum, offset);
    tmp = _mm_xor_si128(tmp, ldollar);
    tag = aes256_1Tft__encrypt1_si128(tmp, aes_encrypt_key);
    tag = _mm_xor_si128(_mm_loadu_si128((const __m128i*)ad_hash), tag);
    
    if (encrypting) {
        unsigned char tag_b[16];
        _mm_storeu_si128((__m128i*)tag_b, tag);
        memcpy(out, tag_b, TAGBYTES);
        return 0;
    } else {
        unsigned char tag_b[16];
        _mm_storeu_si128((__m128i*)tag_b, tag);
        return (memcmp(in,tag_b,TAGBYTES) ? -1 : 0);     /* Check for validity */
    }
}

/* ------------------------------------------------------------------------- */

#define OCB_ENCRYPT 1
#define OCB_DECRYPT 0

void ocb_encrypt(unsigned char *c, unsigned char *k, unsigned char *n,
                 unsigned char *a, unsigned abytes,
                 unsigned char *p, unsigned pbytes) {
    ocb_crypt(c, k, n, a, abytes, p, pbytes, OCB_ENCRYPT);
}

/* ------------------------------------------------------------------------- */

int ocb_decrypt(unsigned char *p, unsigned char *k, unsigned char *n,
                unsigned char *a, unsigned abytes,
                unsigned char *c, unsigned cbytes) {
    return ocb_crypt(p, k, n, a, abytes, c, cbytes, OCB_DECRYPT);
}

/* ------------------------------------------------------------------------- */

int crypto_aead_encrypt(
unsigned char *c,unsigned long long *clen,
const unsigned char *m,unsigned long long mlen,
const unsigned char *ad,unsigned long long adlen,
const unsigned char *nsec,
const unsigned char *npub,
const unsigned char *k
)
{
    *clen = mlen + TAGBYTES;
    ocb_crypt(c, (unsigned char *)k, (unsigned char *)npub, (unsigned char *)ad,
            adlen, (unsigned char *)m, mlen, OCB_ENCRYPT);
    return 0;
}

int crypto_aead_decrypt(
unsigned char *m,unsigned long long *mlen,
unsigned char *nsec,
const unsigned char *c,unsigned long long clen,
const unsigned char *ad,unsigned long long adlen,
const unsigned char *npub,
const unsigned char *k
)
{
    *mlen = clen - TAGBYTES;
    return ocb_crypt(m, (unsigned char *)k, (unsigned char *)npub,
            (unsigned char *)ad, adlen, (unsigned char *)c, clen, OCB_DECRYPT);
}

