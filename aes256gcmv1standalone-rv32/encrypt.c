#include <string.h>

#include "crypto_aead.h"
#include "crypto_verify_16.h"

#include "stdaes-common.h"

#define _bswap64(a) __builtin_bswap64(a)
#define _bswap(a) __builtin_bswap32(a)

#include "new_instructions_support_k.h"

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
static inline void aes256_1Tft_encrypt(uint32_t *output, const uint32_t *input, const uint32_t *aes_edrk)
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

/* same as above, but byte-revert the counter & increment it */
static inline void aes256_1Tft_encrypt_rinc(uint32_t *output, uint32_t *input, const uint32_t *aes_edrk)
{
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i = 0, j = 0;
  unsigned int l_aes_nr = 14;

  X0 = ((input[0]) ^ aes_edrk[j++]);
  X1 = ((input[1]) ^ aes_edrk[j++]);
  X2 = ((input[2]) ^ aes_edrk[j++]);
  X3 = (_bswap(input[3]) ^ aes_edrk[j++]);
  input[3]++;

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

/* emulates 64 bits clmul with 32 bit clmul/clmulh */
static inline int64_t _rv64_clmul(int64_t rs1, int64_t rs2)
{
  int64_t r = 0;
  uint32_t rs1l = rs1 & 0xFFFFFFFF;
  uint32_t rs1h = (rs1>>32) & 0xFFFFFFFF;
  uint32_t rs2l = rs2 & 0xFFFFFFFF;
  uint32_t rs2h = (rs2>>32) & 0xFFFFFFFF;
  uint32_t lll = _rv32_clmul(rs1l, rs2l);
  uint32_t llh = _rv32_clmulh(rs1l, rs2l);
  /* uint32_t hhl = _rv32_clmul(rs1h, rs2h); */
  /* uint32_t hhh = _rv32_clmulh(rs1h, rs2h); */
  uint32_t lhl = _rv32_clmul(rs1l, rs2h);
  /* uint32_t lhh = _rv32_clmulh(rs1l, rs2h); */
  uint32_t hll = _rv32_clmul(rs1h, rs2l);
  /* uint32_t hlh = _rv32_clmulh(rs1h, rs2l); */
  
  uint32_t L = lll;
  uint32_t H = llh ^ lhl ^ hll;
  r =  (int64_t)(((uint64_t)L)| ((uint64_t)H) << 32);
  return r;
}
static inline int64_t _rv64_clmulh(int64_t rs1, int64_t rs2)
{
  int64_t r = 0;
  uint32_t rs1l = rs1 & 0xFFFFFFFF;
  uint32_t rs1h = (rs1>>32) & 0xFFFFFFFF;
  uint32_t rs2l = rs2 & 0xFFFFFFFF;
  uint32_t rs2h = (rs2>>32) & 0xFFFFFFFF;
  /* uint32_t lll = _rv32_clmul(rs1l, rs2l); */
  /* uint32_t llh = _rv32_clmulh(rs1l, rs2l); */
  uint32_t hhl = _rv32_clmul(rs1h, rs2h);
  uint32_t hhh = _rv32_clmulh(rs1h, rs2h);
  /* uint32_t lhl = _rv32_clmul(rs1l, rs2h); */
  uint32_t lhh = _rv32_clmulh(rs1l, rs2h);
  /* uint32_t hll = _rv32_clmul(rs1h, rs2l); */
  uint32_t hlh = _rv32_clmulh(rs1h, rs2l);
  
  uint32_t L = hhl ^ lhh ^ hlh;
  uint32_t H = hhh;
  r =  (int64_t)(((uint64_t)L)| ((uint64_t)H) << 32);
  return r;
}

/* this is basically Supercop's crypto_aead/aes256gcmv1/dolbeau/aesenc-int,
   but without the unrolling.
*/

#include "m128_compat.h"

static inline void addmul_rv(unsigned char *c,
                          const unsigned char *a, int xlen,
                          const unsigned char *b) {
  //const __m128i rev = _mm_set_epi8(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
  const __m128i ff = _mm_set1_epi32(0xFFFFFFFF);
  __m128i A = _mm_loadu_si128((const __m128i*)a);
  //A = _mm_shuffle_epi8(A, rev);
  A = bytereverse128(A);
  if (xlen < 16) { // less than 16 useful bytes - insert zeroes where needed
    unsigned long long mask = -1ull ^ (1ull<<(((16-xlen)%8)*8))-1ull;
    __m128i vm;
    if (xlen>8) {
      vm = _mm_insert_epi64(ff, mask, 0);
    } else {
      vm = _mm_insert_epi64(_mm_setzero_si128(),mask,1);
    }
    A = _mm_and_si128(vm, A);
  }
  __m128i B = _mm_loadu_si128((const __m128i*)b);
  __m128i C = _mm_loadu_si128((const __m128i*)c);
  A = _mm_xor_si128(A,C);
  __m128i tmp3 = _mm_clmulepi64_si128(A, B, 0x00);
  __m128i tmp4 = _mm_clmulepi64_si128(A, B, 0x10);
  __m128i tmp5 = _mm_clmulepi64_si128(A, B, 0x01);
  __m128i tmp6 = _mm_clmulepi64_si128(A, B, 0x11);

  __m128i tmp10 = _mm_xor_si128(tmp4, tmp5);
  __m128i tmp13 = _mm_slli_si128(tmp10, 8);
  __m128i tmp11 = _mm_srli_si128(tmp10, 8);
  __m128i tmp15 = _mm_xor_si128(tmp3, tmp13);
  __m128i tmp17 = _mm_xor_si128(tmp6, tmp11);
  __m128i tmp7 = _mm_srli_epi32(tmp15, 31);
  __m128i tmp8 = _mm_srli_epi32(tmp17, 31);
  __m128i tmp16 = _mm_slli_epi32(tmp15, 1);
  __m128i tmp18 = _mm_slli_epi32(tmp17, 1);
  __m128i tmp9 = _mm_srli_si128(tmp7, 12);
  __m128i tmp22 = _mm_slli_si128(tmp8, 4);
  __m128i tmp25 = _mm_slli_si128(tmp7, 4);
  __m128i tmp29 =_mm_or_si128(tmp16, tmp25);
  __m128i tmp19 = _mm_or_si128(tmp18, tmp22);
  __m128i tmp20 = _mm_or_si128(tmp19, tmp9);
  __m128i tmp26 = _mm_slli_epi32(tmp29, 31);
  __m128i tmp23 = _mm_slli_epi32(tmp29, 30);
  __m128i tmp32 = _mm_slli_epi32(tmp29, 25);
  __m128i tmp27 = _mm_xor_si128(tmp26, tmp23);
  __m128i tmp28 = _mm_xor_si128(tmp27, tmp32);
  __m128i tmp24 = _mm_srli_si128(tmp28, 4);
  __m128i tmp33 = _mm_slli_si128(tmp28, 12);
  __m128i tmp30 = _mm_xor_si128(tmp29, tmp33);
  __m128i tmp2 = _mm_srli_epi32(tmp30, 1);
  __m128i tmp12 = _mm_srli_epi32(tmp30, 2);
  __m128i tmp14 = _mm_srli_epi32(tmp30, 7);
  __m128i tmp34 = _mm_xor_si128(tmp2, tmp12);
  __m128i tmp35 = _mm_xor_si128(tmp34, tmp14);
  __m128i tmp36 = _mm_xor_si128(tmp35, tmp24);
  __m128i tmp31 = _mm_xor_si128(tmp30, tmp36);
  __m128i tmp21 = _mm_xor_si128(tmp20, tmp31);
  _mm_storeu_si128((__m128i*)c, tmp21);
}

#define addmul(a,b,c,d) addmul_rv(a,b,c,d)
static inline void incle(unsigned char *n) {
  (*(unsigned int*)&n[12]) = (1+(((*(unsigned int*)&n[12]))));
}

/* full AES-GCM encryption function */
int crypto_aead_encrypt(
  unsigned char *c,unsigned long long *clen,
  const unsigned char *m,unsigned long long mlen,
  const unsigned char *ad,unsigned long long adlen_,
  const unsigned char *nsec,
  const unsigned char *npub,
  const unsigned char *k
)
{
  __m128i rkeys[16];
  unsigned long long i, j;
  unsigned long long adlen = adlen_;
  unsigned char n2[16];
  unsigned char H[16];
  unsigned char T[16];
  unsigned char accum[16];
  unsigned char fb[16];
  aes256_Tsetkey_encrypt(k, rkeys);
  for (i = 0;i < 12;i++) n2[i] = npub[i];
  for (i = 12; i < 16;i++) n2[i] = 0;
  memset(accum, 0, 16);

  *clen = mlen + 16;

  aes256_1Tft_encrypt(H, accum /* only because it's zero */, rkeys);
  n2[15]++;
  aes256_1Tft_encrypt(T, n2, rkeys);
  
  (*(unsigned long long*)&fb[0]) = _bswap64((unsigned long long)(8*adlen));
  (*(unsigned long long*)&fb[8]) = _bswap64((unsigned long long)(8*mlen));
  
  /* we store H byte-reverted once and for all */
  (*(__m128i*)H) = bytereverse128(*(__m128i*)H);

  /* GCM remainder loop */
  for (i = 0 ; i < adlen ; i+= 16) {
    unsigned long long blocklen = 16;
    if (i+blocklen>adlen)
      blocklen=adlen-i;
    addmul(accum,ad+i,blocklen,H);
  }
  
#define LOOP(iter)						\
  const int lb = iter * 16;					\
  for (i = 0 ; i < mlen ; i+= lb) {				\
    unsigned char outni[lb];				\
    aes256_1Tft_encrypt_rinc(outni, (unsigned int*)n2, rkeys);	\
    unsigned long long mj = lb;					\
    if ((i+mj)>=mlen)						\
      mj = mlen-i;						\
    for (j = 0 ; j < mj ; j++)					\
      c[i+j] = m[i+j] ^ outni[j];				\
    for (j = 0 ; j < mj ; j+=16) {				\
      unsigned long long bl = 16;				\
      if (j+bl>=mj) {						\
        bl = mj-j;						\
      }								\
      addmul(accum,c+i+j,bl,H);					\
    }								\
  }
  
  n2[15]=0;
  incle(n2);
  incle(n2);
  LOOP(1)

  addmul(accum,fb,16,H);

  for (i = 0;i < 16;++i) c[i+mlen] = T[i] ^ accum[15-i];

  return 0;
}


/* full AES-GCM decryption function
   basically the same as encrypt, but the checksuming
   is done _before_ the decryption. And checksum is
   checked at the end.
 */
int crypto_aead_decrypt(
  unsigned char *m,unsigned long long *mlen,
  unsigned char *nsec,
  const unsigned char *c,unsigned long long clen,
  const unsigned char *ad,unsigned long long adlen_,
  const unsigned char *npub,
  const unsigned char *k
)
{
  __m128i rkeys[16];
  unsigned long long i, j;
  unsigned long long adlen = adlen_;
  unsigned char n2[16];
  unsigned char H[16];
  unsigned char T[16];
  unsigned char accum[16];
  unsigned char fb[16];
  aes256_Tsetkey_encrypt(k, rkeys);
  for (i = 0;i < 12;i++) n2[i] = npub[i];
  for (i = 12; i < 16;i++) n2[i] = 0;
  memset(accum, 0, 16);

  *mlen = clen - 16;

  aes256_1Tft_encrypt(H, accum /* only because it's zero */, rkeys);
  n2[15]++;
  aes256_1Tft_encrypt(T, n2, rkeys);
  
  (*(unsigned long long*)&fb[0]) = _bswap64((unsigned long long)(8*adlen));
  (*(unsigned long long*)&fb[8]) = _bswap64((unsigned long long)(8*(*mlen)));

  /* we store H byte-reverted once and for all */
  (*(__m128i*)H) = bytereverse128(*(__m128i*)H);
  
  for (i = 0 ; i < adlen ; i+= 16) {
    unsigned long long blocklen = 16;
    if (i+blocklen>adlen)
      blocklen=adlen-i;
    addmul(accum,ad+i,blocklen,H);
  }
#define LOOPD(iter)                                       \
  const int lb = iter * 16;                               \
  for (i = 0 ; i < *mlen ; i+= lb) {                      \
    unsigned char outni[lb];                      \
    unsigned long long mj = lb;                           \
    if ((i+mj)>=*mlen)                                    \
      mj = *mlen-i;                                       \
    for (j = 0 ; j < mj ; j+=16) {                        \
      unsigned long long bl = 16;                         \
      if (j+bl>=mj) {                                     \
        bl = mj-j;                                        \
      }                                                   \
      addmul(accum,c+i+j,bl,H);                           \
    }                                                     \
    aes256_1Tft_encrypt_rinc(outni, (unsigned int*)n2, rkeys);	\
    for (j = 0 ; j < mj ; j++)                            \
      m[i+j] = c[i+j] ^ outni[j];                         \
  }
  
  n2[15]=0;
  incle(n2);
  incle(n2);
  LOOPD(1)

  addmul(accum,fb,16,H);

  unsigned char F = 0;

  for (i = 0;i < 16;++i) F |= (c[i+(*mlen)] != (T[i] ^ accum[15-i]));
  if (F)
    return -111;

  return 0; 
}
