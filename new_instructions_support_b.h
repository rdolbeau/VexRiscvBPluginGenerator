#ifndef __NEW_INSTRUCTION_SUPPORT_B_H__
#define __NEW_INSTRUCTION_SUPPORT_B_H__

#include <rvintrin.h> // assume we're using the B toolchain

#include "new_instructions_support.h" // for support macros

// for instructions currently missing in the toolchain
ASM2MACRO(XPERM_N,0x28002033)
ASM2MACRO(XPERM_B,0x28004033)
ASM2MACRO(XPERM_H,0x28006033)
ASM2MACRO(SH1ADD,0x20002033)
ASM2MACRO(SH2ADD,0x20004033)
ASM2MACRO(SH3ADD,0x20006033)
FUN2(xperm_n,XPERM_N)
FUN2(xperm_b,XPERM_B)
FUN2(xperm_h,XPERM_H)
FUN2(sh1add,SH1ADD)
FUN2(sh2add,SH2ADD)
FUN2(sh3add,SH3ADD)


#endif // __NEW_INSTRUCTION_SUPPORT_B_H__
