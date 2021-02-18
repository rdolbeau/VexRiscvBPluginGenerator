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

#ifdef __riscv

#include "new_instructions_support_b.h"

#define _rv64_clmul2(a,b) _rv64_clmul(a,b)
#else
#include <rvintrin.h> // emulation

typedef uint32_t uint_xlen_t;
#define XLEN 32
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

//#define CHECK_SIGILL

#if defined(CHECK_SIGILL)
#include <setjmp.h>
extern jmp_buf jb;
void installillhandler(void);
#endif // CHECK_SIGILL

int main(int argc, char **argv) {
  unsigned int b = 0xdeadbeef;
  unsigned int c;
  unsigned int d = 0xC0FFEE00;
  unsigned int index;
  unsigned int index2;
  
#if defined(CHECK_SIGILL)
  installillhandler();
#endif // CHECK_SIGILL

  if (argc > 1)
    a = strtoul(argv[1], NULL, 16);
  if (argc > 2)
    b = strtoul(argv[2], NULL, 16);
  if (argc > 3)
    d = strtoul(argv[3], NULL, 16);

  #if !defined(CHECK_SIGILL)
#define T2(X)							\
  c = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c)
#define T1(X) \
  c = X(a);printf(#X "(0x%08x) -> 0x%08x\n", a, c)
#define T3(X) \
  c = X(a,b,d);printf(#X "(0x%08x, 0x%08x, 0x%08x) -> 0x%08x\n", a, b, d, c)
#define T2W(X)							\
  cq = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%016llx\n", a, b, cq)
#else
#define T2(X) do {							\
    if (setjmp(jb)) {							\
      printf(#X "(0x%08x, 0x%08x) -> *SIGILL*\n", a, b);		\
    } else {								\
      c = X(a,b);							\
      printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c);		\
    }									\
  } while (0)
#define T1(X) do {							\
    if (setjmp(jb)) {							\
      printf(#X "(0x%08x) -> *SIGILL*\n", a);				\
    } else {								\
      c = X(a);								\
      printf(#X "(0x%08x) -> 0x%08x\n", a, c);				\
    }									\
  } while (0)
#define T3(X) do {							\
    if (setjmp(jb)) {							\
      printf(#X "(0x%08x, 0x%08x, 0x%08x) -> *SIGILL*\n", a, b, d);	\
    } else {								\
      c = X(a,b,d);							\
      printf(#X "(0x%08x, 0x%08x, 0x%08x) -> 0x%08x\n", a, b, d, c);	\
    }									\
  } while (0)
#define T2W(X) do {							\
    if (setjmp(jb)) {							\
      printf(#X "(0x%08x, 0x%08x) -> *SIGILL*\n", a, b);		\
    } else {								\
      cq = X(a,b);							\
      printf(#X "(0x%08x, 0x%08x) -> 0x%016llx\n", a, b, cq);		\
    }									\
  } while (0)
#endif // CHECK_SIGILL

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

  //T2(_rv32_sh1add);
  //T2(_rv32_sh2add);
  //T2(_rv32_sh3add);

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
