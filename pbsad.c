#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint32_t MpegEncContext; /* don't care */
typedef ssize_t ptrdiff_t;

#ifdef __riscv

#include "new_instructions_support_p.h"

static inline long long cpucycles_riscv(void) {
  long long result;
#if defined(__riscv_xlen)
#if __riscv_xlen == 64
  asm volatile("rdcycle %0" : "=r" (result));
#elif __riscv_xlen == 32
  unsigned int l, h, h2;
  asm volatile(	"start:\n"
		"rdcycleh %0\n"
		"rdcycle %1\n"  
		"rdcycleh %2\n"
		"bne %0, %2, start\n"
		: "=r" (h), "=r" (l), "=r" (h2));

  result = (((unsigned long long)h)<<32) | ((unsigned long long)l);
#else
#error "unknown __riscv_xlen"
#endif
#else // __riscv_xlen
#error "__riscv_xlen required for RISC-V support"
#endif // __riscv_xlen
  return result;
}
static inline int pix_abs8_r5vp(MpegEncContext *v, uint8_t *pix1, uint8_t *pix2,
                             ptrdiff_t stride, int h)
{
    int s = 0, i;

    for (i = 0; i < h; i++) {
        uint32_t p1 = ((uint32_t*)pix1)[0];
	uint32_t p2 = ((uint32_t*)pix2)[0];
	s = __rv__pbsada(p1, p2, s);
	p1 = ((uint32_t*)pix1)[1];
	p2 = ((uint32_t*)pix2)[1];
	s = __rv__pbsada(p1, p2, s);
        pix1 += stride;
        pix2 += stride;
    }
    return s;
}
#endif // __riscv



/* lifted from FFmpeg */
static inline int pix_abs8_c(MpegEncContext *v, uint8_t *pix1, uint8_t *pix2,
                             ptrdiff_t stride, int h)
{
    int s = 0, i;

    for (i = 0; i < h; i++) {
        s    += abs(pix1[0] - pix2[0]);
        s    += abs(pix1[1] - pix2[1]);
        s    += abs(pix1[2] - pix2[2]);
        s    += abs(pix1[3] - pix2[3]);
        s    += abs(pix1[4] - pix2[4]);
        s    += abs(pix1[5] - pix2[5]);
        s    += abs(pix1[6] - pix2[6]);
        s    += abs(pix1[7] - pix2[7]);
        pix1 += stride;
        pix2 += stride;
    }
    return s;
}

int main(int argc, char **argv) {
  unsigned int seed = 0;
  uint8_t *pix1, *pix2;
  uint32_t i, j;
  
  if (argc > 1)
    seed = atol(argv[1]);

  srandom(seed);

  pix1 = malloc(8 * 4 * 8 * 4 * sizeof(uint8_t));
  pix2 = malloc(8 * 4 * 8 * 4 * sizeof(uint8_t));
  for (i = 0 ; i < 8 * 8 * 4 * 4 ; i ++) {
    pix1[i] = random() & 0xFF;
    pix2[i] = random() & 0xFF;
  }

  for (i = 0 ; i < 4 ; i++) {
    for (j = 0 ; j < 4 ; j++) {
      size_t offset = i*8+j*(8*4*8);
      long long t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;
#ifdef __riscv
      t0 = cpucycles_riscv();
#endif
      int res =  pix_abs8_c(&i, pix1 + offset, pix2 + offset, 8 * 4, 8);
#ifdef __riscv
      t1 = cpucycles_riscv();
      int res2 =  pix_abs8_r5vp(&i, pix1 + offset, pix2 + offset, 8 * 4, 8);
      t2 = cpucycles_riscv();
      int res3 =  pix_abs8_c(&i, pix1 + offset, pix2 + offset, 8 * 4, 8);
      t3 = cpucycles_riscv();
      int res4 =  pix_abs8_r5vp(&i, pix1 + offset, pix2 + offset, 8 * 4, 8);
      t4 = cpucycles_riscv();
#else
      int res2 = 0, res3 = 0, res4 = 0;
#endif
      printf("%u, %u: %d, %d / %d, %d (%llu, %llu / %llu, %llu)\n", i, j, res, res2, res3, res4, t1-t0, t2-t1, t3-t2, t4-t3);
    }
  }

  return 0;
}
