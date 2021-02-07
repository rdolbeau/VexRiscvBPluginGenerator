/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

/*
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//#include <rvintrin.h>

typedef uint32_t uint_xlen_t;
#define XLEN 32
#ifdef __riscv
  //when missing in toolchain
#define FUN1(NAME, ASNAME)						\
  static inline uint32_t NAME(uint32_t rs1) {				\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1\n"					\
	 : "=r" (r)							\
	 : "r" (rs1));							\
    return r;								\
  }
#define FUN2(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2) {	\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2\n"				\
	       : "=r" (r)						\
	       : "r" (rs1), "r" (rs2));					\
    return r;								\
  }
#define FUN3(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2, uint_xlen_t rs3) {	\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2, reg_%3\n"			\
	       : "=r" (r)						\
	 : "r" (rs1), "r" (rs2), "r" (rs3));				\
    return r;								\
  }

#define ASM1MACRO(N, O) asm(".macro "#N" rd, rs1\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15))\n"	\
			   ".endm\n");
#define ASM2MACRO(N, O) asm(".macro "#N" rd, rs1, rs2\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\rs2 << 20))\n"	\
			   ".endm\n");
#define ASM3MACRO(N, O) asm(".macro "#N" rd, rs1, rs2, rs3\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\rs2 << 20) | (\\rs3 << 27) )\n"	\
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
ASM2MACRO(ADD8,0x48000077)
FUN2(__rv__add8,ADD8)
ASM2MACRO(RADD8,0x08000077)
FUN2(__rv__radd8,RADD8)
ASM2MACRO(RSUB8,0x0a000077)
FUN2(__rv__rsub8,RSUB8)
ASM2MACRO(CMPEQ8,0x4e000077)
FUN2(__rv__cmpeq8,CMPEQ8)
ASM1MACRO(CLZ8,0xae100077)
FUN1(__rv__clz8,CLZ8)
ASM1MACRO(CLO8,0xae300077)
FUN1(__rv__clo8,CLO8)
ASM1MACRO(CLRS8,0xae000077)
FUN1(__rv__clrs8,CLRS8)
#else // !__riscv
typedef uint8_t uint4x8_t[4]; 
typedef int8_t int4x8_t[4];
uint32_t __rv__add8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  c[2] = a[2] + b[2];
  c[3] = a[3] + b[3];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__radd8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (((int)a[0] + (int)b[0]) & 0x000001FE)>>1;
  c[1] = (((int)a[1] + (int)b[1]) & 0x000001FE)>>1;
  c[2] = (((int)a[2] + (int)b[2]) & 0x000001FE)>>1;
  c[3] = (((int)a[3] + (int)b[3]) & 0x000001FE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__rsub8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (((int)a[0] - (int)b[0]) & 0x000001FE)>>1;
  c[1] = (((int)a[1] - (int)b[1]) & 0x000001FE)>>1;
  c[2] = (((int)a[2] - (int)b[2]) & 0x000001FE)>>1;
  c[3] = (((int)a[3] - (int)b[3]) & 0x000001FE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__cmpeq8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] == b[0]) ? 0xFF : 0x00;
  c[1] = (a[1] == b[1]) ? 0xFF : 0x00;
  c[2] = (a[2] == b[2]) ? 0xFF : 0x00;
  c[3] = (a[3] == b[3]) ? 0xFF : 0x00;
  memcpy(&r, c, 4);
  return r;
}

uint32_t __rv__clz8(const uint32_t rs1) {
  uint4x8_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] == 0 ? 8 : __builtin_clz((uint32_t)a[0]) - 24;
  c[1] = a[1] == 0 ? 8 : __builtin_clz((uint32_t)a[1]) - 24;
  c[2] = a[2] == 0 ? 8 : __builtin_clz((uint32_t)a[2]) - 24;
  c[3] = a[3] == 0 ? 8 : __builtin_clz((uint32_t)a[3]) - 24;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__clo8(const uint32_t rs1) {
  uint4x8_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] == 0xff ? 8 : __builtin_clz((uint32_t)(uint8_t)(~a[0])) - 24;
  c[1] = a[1] == 0xff ? 8 : __builtin_clz((uint32_t)(uint8_t)(~a[1])) - 24;
  c[2] = a[2] == 0xff ? 8 : __builtin_clz((uint32_t)(uint8_t)(~a[2])) - 24;
  c[3] = a[3] == 0xff ? 8 : __builtin_clz((uint32_t)(uint8_t)(~a[3])) - 24;
  memcpy(&r, c, 4);
  return r;
}
/* off-by-one, should use  __builtin_clrsb ... */
uint32_t __rv__clrs8(const uint32_t rs1) {
  uint4x8_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  /* c[0] = a[0] == 0 ? 8 : a[0] == 0xFF ? 8 : __builtin_clz(a[0]&0x80 ? (uint32_t)(uint8_t)(~a[0]) : (uint32_t)a[0]) - 24; */
  /* c[1] = a[1] == 0 ? 8 : a[1] == 0xFF ? 8 : __builtin_clz(a[1]&0x80 ? (uint32_t)(uint8_t)(~a[1]) : (uint32_t)a[1]) - 24; */
  /* c[2] = a[2] == 0 ? 8 : a[2] == 0xFF ? 8 : __builtin_clz(a[2]&0x80 ? (uint32_t)(uint8_t)(~a[2]) : (uint32_t)a[2]) - 24; */
  /* c[3] = a[3] == 0 ? 8 : a[3] == 0xFF ? 8 : __builtin_clz(a[3]&0x80 ? (uint32_t)(uint8_t)(~a[3]) : (uint32_t)a[3]) - 24; */
  c[0] = __builtin_clrsb((int32_t)a[0]) - 24;
  c[1] = __builtin_clrsb((int32_t)a[1]) - 24;
  c[2] = __builtin_clrsb((int32_t)a[2]) - 24;
  c[3] = __builtin_clrsb((int32_t)a[3]) - 24;
  memcpy(&r, c, 4);
  return r;
}
#endif // __riscv
  
  unsigned int a = 0x01234567;

int main(int argc, char **argv) {
  unsigned int b = 0xdeadbeef;
  unsigned int c;
  unsigned int d = 0xC0FFEE00;
  unsigned int index;
  unsigned int index2;

  if (argc > 1)
    a = strtoul(argv[1], NULL, 16);
  if (argc > 2)
    b = strtoul(argv[2], NULL, 16);
  if (argc > 3)
    d = strtoul(argv[2], NULL, 16);

#define T2(X) \
  c = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c)
#define T1(X) \
  c = X(a);printf(#X "(0x%08x) -> 0x%08x\n", a, c)
#define T3(X) \
  c = X(a,d,b);printf(#X "(0x%08x, 0x%08x, 0x%08x) -> 0x%08x\n", a, d, b, c)

  for (index = 0 ; index < 32 ; index++) {
  
  T2(__rv__add8);
  T2(__rv__radd8);
  T2(__rv__rsub8);
  T2(__rv__cmpeq8);

  
  T1(__rv__clz8);
  T1(__rv__clo8);
  T1(__rv__clrs8);
  
  b = 0x0100F004 | index;
  }

  return 0;
}
