#ifndef __NEW_INSTRUCTION_SUPPORT_H__
#define __NEW_INSTRUCTION_SUPPORT_H__

#include <stdint.h>

typedef uint32_t uint_xlen_t;
#define XLEN 32

  //when missing in toolchain...

// macro to build the function to access the assembly instructions
// unary
#define FUN1(NAME, ASNAME)						\
  static inline uint32_t NAME(uint32_t rs1) {				\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1\n"					\
	 : "=r" (r)							\
	 : "r" (rs1));							\
    return r;								\
  }
// binary
#define FUN2(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2) {	\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2\n"				\
	       : "=r" (r)						\
	       : "r" (rs1), "r" (rs2));					\
    return r;								\
  }
// binary (destructive, e.g. aes32esmi from K)
#define FUN2F(NAME, ASNAME)						\
  static inline uint32_t NAME(uint32_t rs1, uint32_t rs2) {		\
    uint32_t r = rs1;							\
    asm (#ASNAME " reg_%0, reg_%1\n"					\
	 : "+&r" (r)							\
	 : "r" (rs2));							\
    return r;								\
  }
// ternary (constructive, e.g. cmov from B)
#define FUN3(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2, uint_xlen_t rs3) {	\
    uint32_t r;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2, reg_%3\n"			\
	       : "=r" (r)						\
	 : "r" (rs1), "r" (rs2), "r" (rs3));				\
    return r;								\
  }
// ternary (destructive, e.g. pbsad from P)
#define FUN3R(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2, uint_xlen_t rs3) {	\
    uint32_t r = rs3;							\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2\n"				\
	 : "+&r" (r)							\
	 : "r" (rs1), "r" (rs2));					\
    return r;								\
  }
// ternary (destructive using an immediate, e.g. insb from P)
#define FUN3RI(NAME, ASNAME, IMM)					\
  static inline uint_xlen_t NAME##IMM(uint_xlen_t rs1, uint_xlen_t rs3) { \
    uint32_t r = rs3;							\
    asm (#ASNAME " reg_%0, reg_%1, " #IMM "\n"				\
	       : "+&r" (r)						\
	 : "r" (rs1));							\
    return r;								\
  }
// binary wide (64-bits output in R2n/R2n+1, e.g. smul8 from P)
#define FUN2W(NAME, ASNAME)						\
  static inline uint64_t NAME(uint_xlen_t rs1, uint_xlen_t rs2) {	\
    register uint32_t r0 asm ("t5"), r1 asm ("t6");			\
    asm (#ASNAME " reg_%0, reg_%2, reg_%3\n"				\
	 : "=r" (r0), "=r" (r1)						\
	 : "r" (rs1), "r" (rs2));					\
    return ((uint64_t)r0 | (((uint64_t)r1)<<32));			\
  }

// ternary wide (64-bits output in R2n/R2n+1)
#define FUN3Wx(NAME, ASNAME, r0, r1)										\
  static inline uint64_t NAME(uint_xlen_t rs1, uint_xlen_t rs2, uint_xlen_t rs3) {	\
	  register uint32_t r0 asm (""#r0), r1 asm (""#r1);					\
	  r0 = rs3;															\
	  asm (#ASNAME " reg_%0, reg_%2, reg_%3\n"							\
		   : "+r" (r0), "=r" (r1)										\
		   : "r" (rs1), "r" (rs2));										\
	  return ((uint64_t)r0 | (((uint64_t)r1)<<32));						\
  }
#define FUN3Wt5(NAME, ASNAME) FUN3Wx(NAME, ASNAME, t5, t6)
#define FUN3Wt3(NAME, ASNAME) FUN3Wx(NAME, ASNAME, t3, t4)
#define FUN3Ws10(NAME, ASNAME) FUN3Wx(NAME, ASNAME, s10, s11)
#define FUN3Ws8(NAME, ASNAME) FUN3Wx(NAME, ASNAME, s8, s9)

// macro to build assembly macros to generate the proper
// opcodes as .word macro
// the translation from name to number is done my the
// defines below, so this need to go .c -> .S -> .o
// so that there preprocessor is applied to the
// intermediate .S file
#define ASM1MACRO(N, O) asm(".macro "#N" rd, rs1\n"			\
			    ".word ("#O" | (\\rd << 7) | (\\rs1 << 15))\n" \
			    ".endm\n");
#define ASM2MACRO(N, O) asm(".macro "#N" rd, rs1, rs2\n"		\
			    ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\rs2 << 20))\n" \
			    ".endm\n");
#define ASM2FMACRO(N, O) asm(".macro "#N" rt, rs2\n"			\
			     ".word ("#O" | (\\rt << 15) | (\\rs2 << 20))\n" \
			     ".endm\n");
#define ASM3MACRO(N, O) asm(".macro "#N" rd, rs1, rs2, rs3\n"		\
			    ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\rs2 << 20) | (\\rs3 << 27) )\n" \
			    ".endm\n");
#define ASM3RMACRO(N, O) ASM2MACRO(N, O)
#define ASM3RIMACRO(N, O) asm(".macro "#N" rd, rs1, imm\n"		\
			      ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\imm << 20))\n" \
			      ".endm\n");
// register name -> number mapping
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

#endif // __NEW_INSTRUCTION_SUPPORT_H__
