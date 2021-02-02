/*
 * Copyright (c) 2020 Romain Dolbeau <romain.dolbeau@european-processor-initiative.eu>
 * MIT License
 * See the LICENSE file at the top level of this software distribution for details.
 */

/*
 * test file for some B instructions.
 * a) Get the B-supporting toolchain from <https://github.com/riscv/riscv-bitmanip>, as explained in directory <tools/> of that repository
 * b) Fix the assembler for the bug in <https://github.com/riscv/riscv-bitmanip/issues/93> (swap the value of MATCH_MAX and MATCH_MINU unless the fix was integrated since)
 * c) Get the official toolchain for RISC-V (e.g. see 'Installing a RISC-V toolchain' in https://github.com/litex-hub/linux-on-litex-vexriscv)
 * c) Copy the <cproofs/rvintrin.h> header from bitmanip in here
 * d) to simulate on your host:
 *    gcc -I. -DRVINTRIN_EMULATE test_b.c && ./a.out | tee check.txt
 * e) to generate a binary for a RV32IMAB linux platform like Linux-on-Litex-Vexriscv:
 *    Generate an assembly with B support (there's macro in the output assembly so need to go through a .S file):
 *    /opt/riscv64b/bin/riscv64-unknown-elf-gcc -I. -march=rv32imab -mabi=ilp32 -Os test_b.c -S -o test_b.S
 *    Generate an object with B support:
 *    /opt/riscv64b/bin/riscv64-unknown-elf-gcc -I. -march=rv32imab -mabi=ilp32 -Os test_b.S -c -o test_b.o
 *    Link with the official toolchain:
 *    /opt/riscv64-unknown-elf-gcc-8.3.0-2019.08.0-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc -march=rv32ima -mabi=ilp32 test_b.o -o check
 * Running the 'check' binary on the VexRiscv core should give the same results as running in simulation on the host.
 * You can pass parameters to the binary to change input values.
 * If you don't implement some instructions, remove them from the test.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* typedef uint32_t uint_xlen_t; */
/* #define XLEN 32 */
#include <rvintrin.h>


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
ASM2MACRO(XPERM_N,0x28002033)
ASM2MACRO(XPERM_B,0x28004033)
ASM2MACRO(XPERM_H,0x28006033)
ASM2MACRO(SH1ADD,0x20002033)
ASM2MACRO(SH2ADD,0x20004033)
ASM2MACRO(SH3ADD,0x20006033)

/* FUN(xperm_n,0x2928a9b3) */
/* FUN(xperm_b,0x2928c9b3) */
/* FUN(xperm_h,0x2928e9b3) */
/* FUN(sh1add,0x2128a9b3) */
/* FUN(sh2add,0x2128c9b3) */
/* FUN(sh3add,0x2128e9b3) */
FUN2(xperm_n,XPERM_N)
FUN2(xperm_b,XPERM_B)
FUN2(xperm_h,XPERM_H)
FUN2(sh1add,SH1ADD)
FUN2(sh2add,SH2ADD)
FUN2(sh3add,SH3ADD)

#define _rv64_clmul2(a,b) _rv64_clmul(a,b)
#else
  uint_xlen_t xperm(uint_xlen_t rs1, uint_xlen_t rs2, int sz_log2)
{
    uint_xlen_t r = 0;
    uint_xlen_t sz = 1LL << sz_log2;
    uint_xlen_t mask = (1LL << sz) - 1;
    for (int i = 0; i < XLEN; i += sz) {
        uint_xlen_t pos = ((rs2 >> i) & mask) << sz_log2;
        if (pos < XLEN)
            r |= ((rs1 >> pos) & mask) << i;
    }
    return r;
}
uint_xlen_t xperm_n (uint_xlen_t rs1, uint_xlen_t rs2) {  return xperm(rs1, rs2, 2); }
uint_xlen_t xperm_b (uint_xlen_t rs1, uint_xlen_t rs2) {  return xperm(rs1, rs2, 3); }
uint_xlen_t xperm_h (uint_xlen_t rs1, uint_xlen_t rs2) {  return xperm(rs1, rs2, 4); }
uint_xlen_t xperm_w (uint_xlen_t rs1, uint_xlen_t rs2) {  return xperm(rs1, rs2, 5); }

  
uint_xlen_t sh1add(uint_xlen_t rs1, uint_xlen_t rs2)
{
    return (rs1 << 1) + rs2;
}
uint_xlen_t sh2add(uint_xlen_t rs1, uint_xlen_t rs2)
{
    return (rs1 << 2) + rs2;
}
uint_xlen_t sh3add(uint_xlen_t rs1, uint_xlen_t rs2)
{
    return (rs1 << 3) + rs2;
}
#endif // riscv


/* emulates 64 bits clmul with 32 bit clmul/clmulh */
static inline int64_t _rv64_clmul2(int64_t rs1, int64_t rs2)
{
  int64_t r = 0;
  uint32_t rs1l = rs1 & 0xFFFFFFFF;
  uint32_t rs1h = (rs1>>32) & 0xFFFFFFFF;
  uint32_t rs2l = rs2 & 0xFFFFFFFF;
  uint32_t rs2h = (rs2>>32) & 0xFFFFFFFF;
  uint32_t lll = _rv32_clmul(rs1l, rs2l);
  uint32_t llh = _rv32_clmulh(rs1l, rs2l);
  //uint32_t hhl = _rv32_clmul(rs1h, rs2h);
  // hhh
  uint32_t lhl = _rv32_clmul(rs1l, rs2h);
  /* uint32_t lhh = _rv32_clmulh(rs1l, rs2h); */
  uint32_t hll = _rv32_clmul(rs1h, rs2l);
  /* uint32_t hlh = _rv32_clmulh(rs1h, rs2l); */
  
  uint32_t L = lll;
  uint32_t H = llh ^ lhl ^ hll;
  r =  (int64_t)(((uint64_t)L)| ((uint64_t)H) << 32);
  return r;
}


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
  
  T2(_rv32_ror);
  T2(_rv32_rol);
  
  T2(_rv32_grev);
  T2(_rv32_gorc);
  
  T2(_rv32_pack);
  T2(_rv32_packu);
  T2(_rv32_packh);
  
  T2(_rv32_shfl);
  T2(_rv32_unshfl);
  
  T2(_rv_andn);
  T2(_rv_xnor);
  T2(_rv_orn);

  // T2(_rv32_sh1add);
  // T2(_rv32_sh2add);
  // T2(_rv32_sh3add);

  T2(_rv32_sbset);
  T2(_rv32_sbclr);
  T2(_rv32_sbinv);
  T2(_rv32_sbext);
  
  T2(_rv32_min);
  T2(_rv32_minu);
  T2(_rv32_max);
  T2(_rv32_maxu);
  
  T2(_rv32_slo);
  T2(_rv32_sro);

  //T2(_rv32_xperm_b);

  T1(_rv32_sext_b);
  T1(_rv32_sext_h);

  T1(_rv32_clz);
  T1(_rv32_ctz);
  T1(_rv32_pcnt);

  T2(_rv32_clmul);
  T2(_rv32_clmulr);
  T2(_rv32_clmulh);

  {
    int64_t x = 0xc4f5a63e4ac4567bULL ^ (uint64_t)a << 32 ^ (uint64_t)c << 17 ^ (uint64_t)b;
    int64_t y = 0x9ff123456aabbcc9ULL ^ (uint64_t)c << 32 ^ (uint64_t)b << 23 ^ (uint64_t)a;
    int64_t z = _rv64_clmul(x, y);
    int64_t z2 = _rv64_clmul2(x, y);
    printf("0x%016llx 0x%016llx (0x%016llx)\n", z, z2, z^z2);
  }

  // extra stuff
  T2(sh1add);
  T2(sh2add);
  T2(sh3add);

  T2(xperm_n);
  T2(xperm_b);
  T2(xperm_h);

  T3(_rv_cmix);
  T3(_rv_cmov);

  T3(_rv32_fsl);
  T3(_rv32_fsr);

  T2(_rv32_bfp);

  b = index;
  }
  for (index2 = 0 ; index2 < 16 ; index2++) {
    for (index = 0 ; index < 32 ; index++){
      {
	unsigned int a2, b2, c2;
	b2 = (index2<<24) | (index<<16) | 0;
	a2 = 0xFFFFFFFF;
	c2 = _rv32_bfp(a2,b2);printf("_rv32_bfp (0x%08x, 0x%08x) -> 0x%08x\n", a2, b2, c2);
      }
    }
  }
  for (index2 = 0 ; index2 < 16 ; index2++) {
    for (index = 0 ; index < 32 ; index++){
      {
	unsigned int a2, b2, c2;
	b2 = (index2<<24) | (index<<16) | (a&0xFFFF);
	a2 = 0;
	c2 = _rv32_bfp(a2,b2);printf("_rv32_bfp (0x%08x, 0x%08x) -> 0x%08x\n", a2, b2, c2);
      }
    }
  }

  return 0;
}
