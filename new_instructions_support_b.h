#ifndef __NEW_INSTRUCTION_SUPPORT_B_H__
#define __NEW_INSTRUCTION_SUPPORT_B_H__

#include <rvintrin.h> // assume we're using the B toolchain

#include "new_instructions_support.h" // for support macros

#ifdef ENABLE_XAR
ASM3RMACRO(XAR, 0xc8000077)
FUN3R(__rv__xar, XAR)
#endif
#ifdef ENABLE_CHACHA
ASM3RMACRO(CHACHA16,0xa0000077)
ASM3RMACRO(CHACHA12,0xa8000077)
ASM3RMACRO(CHACHA8, 0xb0000077)
ASM3RMACRO(CHACHA7, 0xb8000077)
#endif

#endif // __NEW_INSTRUCTION_SUPPORT_B_H__
