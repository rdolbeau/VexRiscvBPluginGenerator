/* 
 * A thin compatibility layer to SSE's __m128i data format
 *  and associated instructions to support GHASH & the full algo.
*/

#ifndef __M128_COMPAT_H__
#define __M128_COMPAT_H__

#include "new_instructions_support_b.h"

#include <stdio.h>

/* ouch */
typedef struct {
  uint64_t l;
  uint64_t h;
} __m128i;

//#define _mm_loadu_si128(a) (*(const __m128i*)a)
static inline __m128i  _mm_loadu_si128(const __m128i *ptr) {
  __m128i r;
  r.l = ((const uint64_t*)ptr)[0];
  r.h = ((const uint64_t*)ptr)[1];
  return r;
}

//#define _mm_storeu_si128(x,a) (*(__m128i*)x)=a
static inline void _mm_storeu_si128(__m128i *ptr, const __m128i data) {
  ((uint64_t*)ptr)[0] = data.l;
  ((uint64_t*)ptr)[1] = data.h;
}
static inline void _mm_store_si128(__m128i *ptr, const __m128i data) {
  ((uint64_t*)ptr)[0] = data.l;
  ((uint64_t*)ptr)[1] = data.h;
}
static inline void _mm_storel_epi64 (__m128i *ptr, const __m128i data) {
  ((uint64_t*)ptr)[0] = data.l;
}

static inline __m128i _mm_clmulepi64_si128(const __m128i a, const __m128i b, const int x) {
  __m128i r;
  switch (x) {
  case 0x00:
    r.l = _rv64_clmul(a.l, b.l);
    r.h = _rv64_clmulh(a.l, b.l);
    break;
  case 0x01:
    r.l = _rv64_clmul(a.l, b.h);
    r.h = _rv64_clmulh(a.l, b.h);
    break;
  case 0x10:
    r.l = _rv64_clmul(a.h, b.l);
    r.h = _rv64_clmulh(a.h, b.l);
    break;
  case 0x11:
    r.l = _rv64_clmul(a.h, b.h);
    r.h = _rv64_clmulh(a.h, b.h);
    break;
  }
  return r;
}

/*
static inline __m128i (const __m128i a, const __m128i b) {
  __m128i r;
  return r;
}
*/
static inline __m128i _mm_xor_si128(const __m128i a, const __m128i b) {
  __m128i r;
  r.l = a.l ^ b.l;
  r.h = a.h ^ b.h;
  return r;
}
static inline __m128i _mm_or_si128(const __m128i a, const __m128i b) {
  __m128i r;
  r.l = a.l | b.l;
  r.h = a.h | b.h;
  return r;
}
static inline __m128i _mm_and_si128(const __m128i a, const __m128i b) {
  __m128i r;
  r.l = a.l & b.l;
  r.h = a.h & b.h;
  return r;
}
static inline __m128i _mm_slli_si128(const __m128i a, const int b) {
  __m128i r;
  switch (b) {
  case 4:
    r.l = a.l << 32;
    r.h = a.h << 32 | a.l >> 32;
    break;
  case 8:
    r.l = 0;
    r.h = a.l;
    break;
  case 12:
    r.l = 0;
    r.h = a.l << 32;
    break;
  default:
	  fprintf(stderr, "%s: %d unimplemented\n", __PRETTY_FUNCTION__, b);
	  break;
  }
  return r;
}
static inline __m128i _mm_srli_si128(const __m128i a, const int b) {
  __m128i r;
  switch (b) {
  case 1:
	  r.l = a.l >> 8 | a.h << 56;
	  r.h = a.h >> 8;
	  break;
  case 4:
    r.l = a.l >> 32 | a.h << 32;
    r.h = a.h >> 32;
    break;
  case 8:
    r.l = a.h;
    r.h = 0;
    break;
  case 12:
    r.l = a.h >> 32;
    r.h = 0;
    break;
  default:
	  fprintf(stderr, "%s: %d unimplemented\n", __PRETTY_FUNCTION__, b);
	  break;
  }
  return r;
}
static inline __m128i _mm_srli_epi32(const __m128i a, const int b) {
  __m128i r;
  r.l = ((a.l & 0x00000000FFFFFFFFull) >> b) | (((a.l & 0xFFFFFFFF00000000ull) >> b) & 0xFFFFFFFF00000000ull);
  r.h = ((a.h & 0x00000000FFFFFFFFull) >> b) | (((a.h & 0xFFFFFFFF00000000ull) >> b) & 0xFFFFFFFF00000000ull);
  return r;
}
static inline __m128i _mm_slli_epi32(const __m128i a, const int b) {
  __m128i r;
  r.l = (((a.l & 0x00000000FFFFFFFFull) << b) & 0x00000000FFFFFFFFull) | ((a.l & 0xFFFFFFFF00000000ull) << b);
  r.h = (((a.h & 0x00000000FFFFFFFFull) << b) & 0x00000000FFFFFFFFull) | ((a.h & 0xFFFFFFFF00000000ull) << b);
  return r;
}
/* static inline __m128i _mm_srai_epi32(const __m128i a, const int b) { */
/*   __m128i r; */
/*   r.l = (((int32_t)(a.l & 0x00000000FFFFFFFFull)) >> b) | ((((int32_t)(a.l & 0xFFFFFFFF00000000ull)) >> b) & 0xFFFFFFFF00000000ull); */
/*   r.h = (((int32_t)(a.h & 0x00000000FFFFFFFFull)) >> b) | ((((int32_t)(a.h & 0xFFFFFFFF00000000ull)) >> b) & 0xFFFFFFFF00000000ull); */
/*   return r; */
/* } */
static inline __m128i _mm_insert_epi64(const __m128i a, const uint64_t x, const int b) {
  __m128i r;
  if (b == 0) {
    r.l = x;
    r.h = a.h;
  } else {
    r.l = a.l;
    r.h = x;
  }
  return r;
}
static inline __m128i _mm_setzero_si128(void) {
  __m128i r;
  r.l = 0;
  r.h = 0;
  return r;
}
static inline __m128i _mm_set1_epi32(const uint32_t x) {
  __m128i r;
  r.l = x | ((uint64_t)x) << 32;
  r.h = x | ((uint64_t)x) << 32;
  return r;
}
static inline __m128i _mm_set_epi32 (uint32_t e3, uint32_t e2, uint32_t e1, uint32_t e0) {
  __m128i r;
  r.l = (uint64_t)e0 | ((uint64_t)e1) << 32;
  r.h = (uint64_t)e2 | ((uint64_t)e3) << 32;
  return r;
}
/* non-intel stuff, used to replace some common use cases */
static inline uint64_t bytereverse64(const uint64_t a) {
  uint64_t r;
  r = (uint32_t)_rv32_grev((a>>32), 24) | (((uint64_t)_rv32_grev((a&0xFFFFFFFF), 24))<<32);
  return r;
}
static inline __m128i bytereverse128(const __m128i a) {
  __m128i r;
  r.l = bytereverse64(a.h);
  r.h = bytereverse64(a.l);
  return r;  
}

static inline uint64_t bitreverse64(const uint64_t a) {
  uint64_t r;
  r = (uint32_t)_rv32_grev((a&0xFFFFFFFF), 7) | (((uint64_t)_rv32_grev((a>>32), 7))<<32);
  return r;
}
static inline __m128i bitreverse128(const __m128i a) {
  __m128i r;
  r.l = bitreverse64(a.l);
  r.h = bitreverse64(a.h);
  return r;  
}

static inline uint64_t wordreverse64(const uint64_t a) {
  uint64_t r;
  r = (a>>32)|(a<<32);
  return r;
}
static inline __m128i wordreverse128(const __m128i  a) {
  __m128i r;
  r.l = wordreverse64(a.h);
  r.h = wordreverse64(a.l);
  return r;
}
static inline __m128i doublewordreverse128(const __m128i  a) {
  __m128i r;
  r.l = a.h;
  r.h = a.l;
  return r;
}
static inline __m128i wordrotate1l128(const __m128i  a) {
  __m128i r;
  /* i.e. epi32 _MM_SHUFFLE(2,1,0,3) */
  r.l = (a.h >> 32) | (a.l << 32);
  r.h = (a.l >> 32) | (a.h << 32);
  return r;
}
static inline __m128i halfwordandzero(const uint16_t a) {
	__m128i r;
	r.l = a;
	r.h = 0;
	return r;
}
static inline __m128i wordsign128(const __m128i  a) {
	__m128i r;
	r.l = (a.l & 0x0000000080000000ull ? 0x00000000FFFFFFFFull : 0) | (a.l & 0x8000000000000000ull ? 0xFFFFFFFF00000000ull : 0);
	r.h = (a.h & 0x0000000080000000ull ? 0x00000000FFFFFFFFull : 0) | (a.h & 0x8000000000000000ull ? 0xFFFFFFFF00000000ull : 0);
	return r;
}
#endif // __M128_COMPAT_H__
