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
#define FUN3R(NAME, ASNAME)						\
  static inline uint_xlen_t NAME(uint_xlen_t rs1, uint_xlen_t rs2, uint_xlen_t rs3) {	\
    uint32_t r = rs3;								\
    asm (#ASNAME " reg_%0, reg_%1, reg_%2\n"			\
	       : "+&r" (r)						\
	 : "r" (rs1), "r" (rs2));				\
    return r;								\
  }
#define FUN3RI(NAME, ASNAME, IMM)						\
  static inline uint_xlen_t NAME##IMM(uint_xlen_t rs1, uint_xlen_t rs3) {	\
    uint32_t r = rs3;								\
    asm (#ASNAME " reg_%0, reg_%1, " #IMM "\n"			\
	       : "+&r" (r)						\
	 : "r" (rs1));				\
    return r;								\
  }
#define FUN2W(NAME, ASNAME)						\
  static inline uint64_t NAME(uint_xlen_t rs1, uint_xlen_t rs2) {	\
    uint32_t r0, r1;							\
    asm (#ASNAME " reg_t5, reg_%2, reg_%3\n"				\
	 "mv %0, t5\n"							\
	 "mv %1, t6\n"							\
	 : "=r" (r0), "=r" (r1)						\
	 : "r" (rs1), "r" (rs2)						\
	 : "t5", "t6");							\
    return ((uint64_t)r0 | (((uint64_t)r1)<<32));			\
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
#define ASM3RMACRO(N, O) ASM2MACRO(N, O)
#define ASM3RIMACRO(N, O) asm(".macro "#N" rd, rs1, imm\n"		\
			   ".word ("#O" | (\\rd << 7) | (\\rs1 << 15) | (\\imm << 20))\n"	\
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
ASM1MACRO(SWAP8,0xad800077)
FUN1(__rv__swap8,swap8)
ASM2MACRO(SCMPLE8,0x1e000077)
FUN2(__rv__scmple8,SCMPLE8)
ASM2MACRO(SCMPLT8,0x0e000077)
FUN2(__rv__scmplt8,SCMPLt8)
ASM2MACRO(SLL8,0x5c000077)
FUN2(__rv__sll8,SLL8)
ASM2MACRO(SRL8,0x5a000077)
FUN2(__rv__srl8,SRL8)
ASM2MACRO(SRA8,0x58000077)
FUN2(__rv__sra8,SRA8)
ASM2MACRO(SMAX8,0x8a000077)
FUN2(__rv__smax8,SMAX8)
ASM2MACRO(SMIN8,0x88000077)
FUN2(__rv__smin8,SMIN8)
ASM2MACRO(SUB8,0x4a000077)
FUN2(__rv__sub8,SUB8)
ASM2MACRO(UCMPLE8,0x3e000077)
FUN2(__rv__ucmple8,UCMPLE8)
ASM2MACRO(UCMPLT8,0x2e000077)
FUN2(__rv__ucmplt8,UCMPLt8)
ASM2MACRO(UMAX8,0x9a000077)
FUN2(__rv__umax8,UMAX8)
ASM2MACRO(UMIN8,0x98000077)
FUN2(__rv__umin8,UMIN8)
ASM2MACRO(URADD8,0x28000077)
FUN2(__rv__uradd8,URADD8)
ASM2MACRO(URSUB8,0x2a000077)
FUN2(__rv__ursub8,URSUB8)
  
ASM2MACRO(ADD16,0x40000077)
FUN2(__rv__add16,ADD16)
ASM2MACRO(RADD16,0x00000077)
FUN2(__rv__radd16,RADD16)
ASM2MACRO(RSUB16,0x02000077)
FUN2(__rv__rsub16,RSUB16)
ASM2MACRO(CMPEQ16,0x4c000077)
FUN2(__rv__cmpeq16,CMPEQ16)
ASM1MACRO(CLZ16,0xae900077)
FUN1(__rv__clz16,CLZ16)
ASM1MACRO(CLO16,0xaeb00077)
FUN1(__rv__clo16,CLO16)
ASM1MACRO(CLRS16,0xae800077)
FUN1(__rv__clrs16,CLRS16)
ASM1MACRO(SWAP16,0xad900077)
FUN1(__rv__swap16,swap16)
ASM2MACRO(SCMPLE16,0x1c000077)
FUN2(__rv__scmple16,SCMPLE16)
ASM2MACRO(SCMPLT16,0x0c000077)
FUN2(__rv__scmplt16,SCMPLT16)
ASM2MACRO(SLL16,0x54000077)
FUN2(__rv__sll16,SLL16)
ASM2MACRO(SRL16,0x52000077)
FUN2(__rv__srl16,SRL16)
ASM2MACRO(SRA16,0x50000077)
FUN2(__rv__sra16,SRA16)
ASM2MACRO(SMAX16,0x82000077)
FUN2(__rv__smax16,SMAX16)
ASM2MACRO(SMIN16,0x80000077)
FUN2(__rv__smin16,SMIN16)
ASM2MACRO(SUB16,0x42000077)
FUN2(__rv__sub16,SUB16)
ASM2MACRO(UCMPLE16,0x3c000077)
FUN2(__rv__ucmple16,UCMPLE16)
ASM2MACRO(UCMPLT16,0x2c000077)
FUN2(__rv__ucmplt16,UCMPLT16)
ASM2MACRO(UMAX16,0x92000077)
FUN2(__rv__umax16,UMAX16)
ASM2MACRO(UMIN16,0x90000077)
FUN2(__rv__umin16,UMIN16)

ASM2MACRO(PKBB16,0x0e001077)
FUN2(__rv__pkbb16,PKBB16)
ASM2MACRO(PKBT16,0x1e001077)
FUN2(__rv__pkbt16,PKBT16)
ASM2MACRO(PKTB16,0x2e001077)
FUN2(__rv__pktb16,PKTB16)
ASM2MACRO(PKTT16,0x3e001077)
FUN2(__rv__pktt16,PKTT16)
ASM2MACRO(URADD16,0x20000077)
FUN2(__rv__uradd16,URADD16)
ASM2MACRO(URSUB16,0x22000077)
FUN2(__rv__ursub16,URSUB16)


ASM2MACRO(RADDW,0x20001077)
FUN2(__rv__raddw,RADDW)
ASM2MACRO(RSUBW,0x22001077)
FUN2(__rv__rsubw,RSUBW)
ASM2MACRO(URADDW,0x30001077)
FUN2(__rv__uraddw,URADDW)
ASM2MACRO(URSUBW,0x32001077)
FUN2(__rv__ursubw,URSUBW)
ASM2MACRO(AVE,0xe0000077)
FUN2(__rv__ave,AVE)

ASM2MACRO(PBSAD, 0xfc000077)
FUN2(__rv__pbsad, PBSAD)
ASM3RMACRO(PBSADA, 0xfe000077)
FUN3R(__rv__pbsada, PBSADA)

ASM2MACRO(BITREV,0xe6000077)
FUN2(__rv__bitrev,BITREV)

ASM3RIMACRO(INSB, 0xac000077)
FUN3RI(__rv__insb, INSB, 0)
FUN3RI(__rv__insb, INSB, 1)
FUN3RI(__rv__insb, INSB, 2)
FUN3RI(__rv__insb, INSB, 3)
  
ASM2MACRO(SMUL8,0xa8000077)
FUN2W(__rv__smul8,SMUL8)
ASM2MACRO(UMUL8,0xb8000077)
FUN2W(__rv__umul8,UMUL8)
ASM2MACRO(SMUL16,0xa0000077)
FUN2W(__rv__smul16,SMUL16)
ASM2MACRO(UMUL16,0xb0000077)
FUN2W(__rv__umul16,UMUL16)
  
ASM2MACRO(SMULx8,0xaa000077)
FUN2W(__rv__smulx8,SMULx8)
ASM2MACRO(UMULx8,0xba000077)
FUN2W(__rv__umulx8,UMULx8)
ASM2MACRO(SMULx16,0xa2000077)
FUN2W(__rv__smulx16,SMULx16)
ASM2MACRO(UMULx16,0xb2000077)
FUN2W(__rv__umulx16,UMULx16)

#else // !__riscv
typedef uint8_t uint4x8_t[4];
typedef int8_t int4x8_t[4];

typedef uint16_t uint2x16_t[2];
typedef int16_t int2x16_t[2];

typedef uint16_t uint4x16_t[4]; // for 2W
typedef int16_t int4x16_t[4]; // for 2W
typedef uint32_t uint2x32_t[2]; // for 2W
typedef int32_t int2x32_t[2];  // for 2W

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
  c[0] = (((int32_t)a[0] + (int32_t)b[0]) & 0x000001FE)>>1;
  c[1] = (((int32_t)a[1] + (int32_t)b[1]) & 0x000001FE)>>1;
  c[2] = (((int32_t)a[2] + (int32_t)b[2]) & 0x000001FE)>>1;
  c[3] = (((int32_t)a[3] + (int32_t)b[3]) & 0x000001FE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__rsub8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (((int32_t)a[0] - (int32_t)b[0]) & 0x000001FE)>>1;
  c[1] = (((int32_t)a[1] - (int32_t)b[1]) & 0x000001FE)>>1;
  c[2] = (((int32_t)a[2] - (int32_t)b[2]) & 0x000001FE)>>1;
  c[3] = (((int32_t)a[3] - (int32_t)b[3]) & 0x000001FE)>>1;
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
uint32_t __rv__clrs8(const uint32_t rs1) {
  uint4x8_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = __builtin_clrsb((int32_t)a[0]) - 24;
  c[1] = __builtin_clrsb((int32_t)a[1]) - 24;
  c[2] = __builtin_clrsb((int32_t)a[2]) - 24;
  c[3] = __builtin_clrsb((int32_t)a[3]) - 24;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__swap8(const uint32_t rs1) {
  uint4x8_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[1];
  c[1] = a[0];
  c[2] = a[3];
  c[3] = a[2];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__scmple8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? 0xFF : 0x00;
  c[1] = (a[1] <= b[1]) ? 0xFF : 0x00;
  c[2] = (a[2] <= b[2]) ? 0xFF : 0x00;
  c[3] = (a[3] <= b[3]) ? 0xFF : 0x00;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__scmplt8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] < b[0]) ? 0xFF : 0x00;
  c[1] = (a[1] < b[1]) ? 0xFF : 0x00;
  c[2] = (a[2] < b[2]) ? 0xFF : 0x00;
  c[3] = (a[3] < b[3]) ? 0xFF : 0x00;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__sll8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, c;
  uint32_t o = rs2 & 0x7;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] << o;
  c[1] = a[1] << o;
  c[2] = a[2] << o;
  c[3] = a[3] << o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__srl8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, c;
  uint32_t o = rs2 & 0x7;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] >> o;
  c[1] = a[1] >> o;
  c[2] = a[2] >> o;
  c[3] = a[3] >> o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__sra8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, c;
  uint32_t o = rs2 & 0x7;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] >> o;
  c[1] = a[1] >> o;
  c[2] = a[2] >> o;
  c[3] = a[3] >> o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__smax8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] >= b[0]) ? a[0] : b[0];
  c[1] = (a[1] >= b[1]) ? a[1] : b[1];
  c[2] = (a[2] >= b[2]) ? a[2] : b[2];
  c[3] = (a[3] >= b[3]) ? a[3] : b[3];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__smin8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? a[0] : b[0];
  c[1] = (a[1] <= b[1]) ? a[1] : b[1];
  c[2] = (a[2] <= b[2]) ? a[2] : b[2];
  c[3] = (a[3] <= b[3]) ? a[3] : b[3];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ucmple8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? 0xFF : 0x00;
  c[1] = (a[1] <= b[1]) ? 0xFF : 0x00;
  c[2] = (a[2] <= b[2]) ? 0xFF : 0x00;
  c[3] = (a[3] <= b[3]) ? 0xFF : 0x00;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ucmplt8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] < b[0]) ? 0xFF : 0x00;
  c[1] = (a[1] < b[1]) ? 0xFF : 0x00;
  c[2] = (a[2] < b[2]) ? 0xFF : 0x00;
  c[3] = (a[3] < b[3]) ? 0xFF : 0x00;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__umax8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] >= b[0]) ? a[0] : b[0];
  c[1] = (a[1] >= b[1]) ? a[1] : b[1];
  c[2] = (a[2] >= b[2]) ? a[2] : b[2];
  c[3] = (a[3] >= b[3]) ? a[3] : b[3];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__umin8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? a[0] : b[0];
  c[1] = (a[1] <= b[1]) ? a[1] : b[1];
  c[2] = (a[2] <= b[2]) ? a[2] : b[2];
  c[3] = (a[3] <= b[3]) ? a[3] : b[3];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__uradd8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = ((a[0] + b[0]) & 0x000001FE)>>1;
  c[1] = ((a[1] + b[1]) & 0x000001FE)>>1;
  c[2] = ((a[2] + b[2]) & 0x000001FE)>>1;
  c[3] = ((a[3] + b[3]) & 0x000001FE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ursub8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = ((a[0] - b[0]) & 0x000001FE)>>1;
  c[1] = ((a[1] - b[1]) & 0x000001FE)>>1;
  c[2] = ((a[2] - b[2]) & 0x000001FE)>>1;
  c[3] = ((a[3] - b[3]) & 0x000001FE)>>1;
  memcpy(&r, c, 4);
  return r;
}



uint32_t __rv__add16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] + b[0];
  c[1] = a[1] + b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__radd16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (((int32_t)a[0] + (int32_t)b[0]) & 0x0001FFFE)>>1;
  c[1] = (((int32_t)a[1] + (int32_t)b[1]) & 0x0001FFFE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__rsub16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (((int32_t)a[0] - (int32_t)b[0]) & 0x0001FFFE)>>1;
  c[1] = (((int32_t)a[1] - (int32_t)b[1]) & 0x0001FFFE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__cmpeq16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] == b[0]) ? 0xFFFF : 0x0000;
  c[1] = (a[1] == b[1]) ? 0xFFFF : 0x0000;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__clz16(const uint32_t rs1) {
  uint2x16_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] == 0 ? 16 : __builtin_clz((uint32_t)a[0]) - 16;
  c[1] = a[1] == 0 ? 16 : __builtin_clz((uint32_t)a[1]) - 16;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__clo16(const uint32_t rs1) {
  uint2x16_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] == 0xff ? 16 : __builtin_clz((uint32_t)(uint8_t)(~a[0])) - 16;
  c[1] = a[1] == 0xff ? 16 : __builtin_clz((uint32_t)(uint8_t)(~a[1])) - 16;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__clrs16(const uint32_t rs1) {
  uint2x16_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = __builtin_clrsb((int32_t)a[0]) - 16;
  c[1] = __builtin_clrsb((int32_t)a[1]) - 16;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__swap16(const uint32_t rs1) {
  uint2x16_t a, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[1];
  c[1] = a[0];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__scmple16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? 0xFFFF : 0x0000;
  c[1] = (a[1] <= b[1]) ? 0xFFFF : 0x0000;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__scmplt16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] < b[0]) ? 0xFFFF : 0x0000;
  c[1] = (a[1] < b[1]) ? 0xFFFF : 0x0000;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__sll16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, c;
  uint32_t o = rs2 & 0xF;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] << o;
  c[1] = a[1] << o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__srl16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, c;
  uint32_t o = rs2 & 0xF;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] >> o;
  c[1] = a[1] >> o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__sra16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, c;
  uint32_t o = rs2 & 0xF;
  uint32_t r;
  memcpy(a, &rs1, 4);
  c[0] = a[0] >> o;
  c[1] = a[1] >> o;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__smax16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] >= b[0]) ? a[0] : b[0];
  c[1] = (a[1] >= b[1]) ? a[1] : b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__smin16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? a[0] : b[0];
  c[1] = (a[1] <= b[1]) ? a[1] : b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ucmple16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? 0xFFFF : 0x0000;
  c[1] = (a[1] <= b[1]) ? 0xFFFF : 0x0000;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ucmplt16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] < b[0]) ? 0xFFFF : 0x0000;
  c[1] = (a[1] < b[1]) ? 0xFFFF : 0x0000;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__umax16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] >= b[0]) ? a[0] : b[0];
  c[1] = (a[1] >= b[1]) ? a[1] : b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__umin16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = (a[0] <= b[0]) ? a[0] : b[0];
  c[1] = (a[1] <= b[1]) ? a[1] : b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__uradd16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = ((a[0] + b[0]) & 0x0001FFFE)>>1;
  c[1] = ((a[1] + b[1]) & 0x0001FFFE)>>1;
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__ursub16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = ((a[0] - b[0]) & 0x0001FFFE)>>1;
  c[1] = ((a[1] - b[1]) & 0x0001FFFE)>>1;
  memcpy(&r, c, 4);
  return r;
}


uint32_t __rv__pkbb16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[1] = a[0];
  c[0] = b[0];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__pkbt16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[1] = a[0];
  c[0] = b[1];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__pktb16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[1] = a[1];
  c[0] = b[0];
  memcpy(&r, c, 4);
  return r;
}
uint32_t __rv__pktt16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b, c;
  uint32_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[1] = a[1];
  c[0] = b[1];
  memcpy(&r, c, 4);
  return r;
}

int32_t __rv__raddw(const int32_t rs1, const int32_t rs2) {
  int64_t s = (int64_t)rs1 + (int64_t)rs2;
  return (int32_t)((s>>1)&0xFFFFFFFF);
}
int32_t __rv__rsubw(const int32_t rs1, const int32_t rs2) {
  int64_t s = (int64_t)rs1 - (int64_t)rs2;
  return (int32_t)((s>>1)&0xFFFFFFFF);
}
uint32_t __rv__uraddw(const uint32_t rs1, const uint32_t rs2) {
  uint64_t s = (uint64_t)rs1 + (uint64_t)rs2;
  return (int32_t)((s>>1)&0xFFFFFFFF);
}
uint32_t __rv__ursubw(const uint32_t rs1, const uint32_t rs2) {
  uint64_t s = (uint64_t)rs1 - (uint64_t)rs2;
  return (uint32_t)((s>>1)&0xFFFFFFFF);
}
int32_t __rv__ave(const int32_t rs1, const int32_t rs2) {
  int64_t s = 1 + ((int64_t)rs1<<1) + ((int64_t)rs2<<1);
  return (int32_t)((s>>1)&0xFFFFFFFF);
}
uint32_t __rv__bitrev(const uint32_t rs1, const uint32_t rs2) {
  const uint32_t n = rs2 & 0x1F;
  uint32_t x = rs1;

  x = (x & 0x55555555)<<1 | (x & 0xaaaaaaaa)>>1;
  x = (x & 0x33333333)<<2 | (x & 0xcccccccc)>>2;
  x = (x & 0x0F0F0F0F)<<4 | (x & 0xF0F0F0F0)>>4;
  x = (x & 0x00FF00FF)<<8 | (x & 0xFF00FF00)>>8;
  x = (x & 0x0000FFFF)<<16 | (x & 0xFFFF0000)>>16;
  return x >> (31-n);
}



uint32_t __rv__pbsada(const uint32_t rs1, const uint32_t rs2, const uint32_t rs3) {
  uint4x8_t a, b;
  uint32_t r = rs3;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  r += abs((int32_t)a[0] - (int32_t)b[0]);
  r += abs((int32_t)a[1] - (int32_t)b[1]);
  r += abs((int32_t)a[2] - (int32_t)b[2]);
  r += abs((int32_t)a[3] - (int32_t)b[3]);
  return r;
}
uint32_t __rv__pbsad(const uint32_t rs1, const uint32_t rs2) {
  return __rv__pbsada(rs1, rs2, 0);
}

uint32_t __rv__insb0(const uint32_t rs1, const uint32_t rs2) {
  uint32_t r;

  r = rs2 & 0xFFFFFF00;
  r |= ((rs1 & 0xFF) << 0);

  return r;
}
uint32_t __rv__insb1(const uint32_t rs1, const uint32_t rs2) {
  uint32_t r;

  r = rs2 & 0xFFFF00FF;
  r |= ((rs1 & 0xFF) << 8);

  return r;
}
uint32_t __rv__insb2(const uint32_t rs1, const uint32_t rs2) {
  uint32_t r;

  r = rs2 & 0xFF00FFFF;
  r |= ((rs1 & 0xFF) << 16);

  return r;
}
uint32_t __rv__insb3(const uint32_t rs1, const uint32_t rs2) {
  uint32_t r;

  r = rs2 & 0x00FFFFFF;
  r |= ((rs1 & 0xFF) << 24);

  return r;
}



uint64_t __rv__smul8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b;
  int4x16_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[0];
  c[1] = a[1] * b[1];
  c[2] = a[2] * b[2];
  c[3] = a[3] * b[3];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__umul8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b;
  uint4x16_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[0];
  c[1] = a[1] * b[1];
  c[2] = a[2] * b[2];
  c[3] = a[3] * b[3];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__smul16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b;
  int2x32_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[0];
  c[1] = a[1] * b[1];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__umul16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b;
  uint2x32_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[0];
  c[1] = a[1] * b[1];
  memcpy(&r, c, 8);
  return r;
}

uint64_t __rv__smulx8(const uint32_t rs1, const uint32_t rs2) {
  int4x8_t a, b;
  int4x16_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[1];
  c[1] = a[1] * b[0];
  c[2] = a[2] * b[3];
  c[3] = a[3] * b[2];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__umulx8(const uint32_t rs1, const uint32_t rs2) {
  uint4x8_t a, b;
  uint4x16_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[1];
  c[1] = a[1] * b[0];
  c[2] = a[2] * b[3];
  c[3] = a[3] * b[2];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__smulx16(const uint32_t rs1, const uint32_t rs2) {
  int2x16_t a, b;
  int2x32_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[1];
  c[1] = a[1] * b[0];
  memcpy(&r, c, 8);
  return r;
}
uint64_t __rv__umulx16(const uint32_t rs1, const uint32_t rs2) {
  uint2x16_t a, b;
  uint2x32_t c;
  uint64_t r;
  memcpy(a, &rs1, 4);
  memcpy(b, &rs2, 4);
  c[0] = a[0] * b[1];
  c[1] = a[1] * b[0];
  memcpy(&r, c, 8);
  return r;
}
#endif // __riscv
  
  unsigned int a = 0x01234567;

#define CHECK_SIGILL

#if defined(CHECK_SIGILL)
#include <signal.h>
#include <setjmp.h>

static jmp_buf jb;

static void sighandler(int x)
{
     longjmp(jb, 1);
}
#endif // CHECK_SIGILL

int main(int argc, char **argv) {
  unsigned int b = 0xdeadbeef;
  unsigned int c = 0;
  unsigned int d = 0xC0FFEE00;
  unsigned int index;
  unsigned int index2;
  unsigned long long cq = 0;
#if defined(CHECK_SIGILL)
  void (*oldsig)(int);
  oldsig = signal(SIGILL, sighandler);
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
 #if 1
  T2(__rv__add8);
  T2(__rv__radd8);
  T2(__rv__rsub8);
  T2(__rv__cmpeq8);
  T1(__rv__clz8);
  T1(__rv__clo8);
  T1(__rv__clrs8);
  T1(__rv__swap8);
  T2(__rv__scmple8);
  T2(__rv__scmplt8);
  T2(__rv__sll8);
  T2(__rv__srl8);
  T2(__rv__sra8);
  T2(__rv__smax8);
  T2(__rv__smin8);
  T2(__rv__ucmple8);
  T2(__rv__ucmplt8);
  T2(__rv__umax8);
  T2(__rv__umin8);
  T2(__rv__uradd8);
  T2(__rv__ursub8);

  T2(__rv__add16);
  T2(__rv__radd16);
  T2(__rv__rsub16);
  T2(__rv__cmpeq16);
  //T1(__rv__clz16); /* unimplemented */
  //T1(__rv__clo16); /* unimplemented */
  //T1(__rv__clrs16); /* unimplemented */
  T1(__rv__swap16);
  T2(__rv__scmple16);
  T2(__rv__scmplt16);
  T2(__rv__sll16);
  T2(__rv__srl16);
  T2(__rv__sra16);
  T2(__rv__smax16);
  T2(__rv__smin16);
  T2(__rv__ucmple16);
  T2(__rv__ucmplt16);
  T2(__rv__umax16);
  T2(__rv__umin16);
  T2(__rv__uradd16);
  T2(__rv__ursub16);
  
  T2(__rv__pkbb16);
  T2(__rv__pkbt16);
  T2(__rv__pktb16);
  T2(__rv__pktt16);
  
  T2(__rv__raddw);
  T2(__rv__rsubw);
  T2(__rv__uraddw);
  T2(__rv__ursubw);
  T2(__rv__ave);
  T2(__rv__bitrev);
 #endif
  T2(__rv__pbsad);
  T3(__rv__pbsada);

  T2(__rv__insb0);
  T2(__rv__insb1);
  T2(__rv__insb2);
  T2(__rv__insb3);

  T2W(__rv__smul8);
  T2W(__rv__umul8);
  T2W(__rv__smul16);
  T2W(__rv__umul16);
  T2W(__rv__smulx8);
  T2W(__rv__umulx8);
  T2W(__rv__smulx16);
  T2W(__rv__umulx16);
  
  b = 0x0100F004 + index;
  }

  return 0;
}
