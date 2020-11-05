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
 * e) to geenrate a binary for a RV32IMAB linux platform like Linux-on-Litex-Vexriscv:
 *    Generate ao object with B support:
 *    /opt/riscv64b/bin/riscv64-unknown-elf-gcc -I. -march=rv32imab -mabi=ilp32 -Os test_b.c -c
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
#ifdef __riscv
  //when missing in toolchain
#define FUN(NAME, OPC)							\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2) {	\
    uint32_t r;								\
    asm inline("or x17, %1 ,%1\n"					\
	       "or x18, %2, %2\n"					\
	       ".word " #OPC "\n"					\
	       "or %0, x19, x19\n"					\
	       : "=r" (r)						\
	       : "r" (rs1), "r" (rs2)					\
	       : "x17", "x18", "x19");					\
    return r;								\
  }
FUN(xperm_n,0x2928a9b3)
FUN(xperm_b,0x2928c9b3)
FUN(xperm_h,0x2928e9b3)
FUN(sh1add,0x2128a9b3)
FUN(sh2add,0x2128c9b3)
FUN(sh3add,0x2128e9b3)
#else
#define xperm_n _rv32_xperm_n
#define xperm_b _rv32_xperm_b
#define xperm_h _rv32_xperm_h
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
#endif

int main(int argc, char **argv) {
  unsigned int a = 0x01234567;
  unsigned int b = 0xdeadbeef;
  unsigned int c;
  unsigned int index;

  if (argc > 1)
    a = strtoul(argv[1], NULL, 16);
  if (argc > 2)
    b = strtoul(argv[2], NULL, 16);

#define T2(X) \
  c = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c)
#define T1(X) \
  c = X(a);printf(#X "(0x%08x) -> 0x%08x\n", a, c)

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

  // extra stuff
  T2(sh1add);
  T2(sh2add);
  T2(sh3add);

  T2(xperm_n);
  T2(xperm_b);
  T2(xperm_h);

  b = index;
  }

  return 0;
}
