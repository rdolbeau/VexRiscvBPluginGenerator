#ifndef __NEW_INSTRUCTION_SUPPORT_K_H__
#define __NEW_INSTRUCTION_SUPPORT_K_H__

#include "new_instructions_support.h" // for support macros

ASM2FMACRO(AES32ESMI0,0x36000033)
ASM2FMACRO(AES32ESMI1,0x76000033)
ASM2FMACRO(AES32ESMI2,0xb6000033)
ASM2FMACRO(AES32ESMI3,0xf6000033)
ASM2FMACRO(AES32ESI0,0x32000033)
ASM2FMACRO(AES32ESI1,0x72000033)
ASM2FMACRO(AES32ESI2,0xb2000033)
ASM2FMACRO(AES32ESI3,0xf2000033)
FUN2F(aes32esmi0,AES32ESMI0)
FUN2F(aes32esmi1,AES32ESMI1)
FUN2F(aes32esmi2,AES32ESMI2)
FUN2F(aes32esmi3,AES32ESMI3)
FUN2F(aes32esi0,AES32ESI0)
FUN2F(aes32esi1,AES32ESI1)
FUN2F(aes32esi2,AES32ESI2)
FUN2F(aes32esi3,AES32ESI3)
ASM2FMACRO(AES32DSMI0,0x3e000033)
ASM2FMACRO(AES32DSMI1,0x7e000033)
ASM2FMACRO(AES32DSMI2,0xbe000033)
ASM2FMACRO(AES32DSMI3,0xfe000033)
ASM2FMACRO(AES32DSI0,0x3a000033)
ASM2FMACRO(AES32DSI1,0x7a000033)
ASM2FMACRO(AES32DSI2,0xba000033)
ASM2FMACRO(AES32DSI3,0xfa000033)
FUN2F(aes32dsmi0,AES32DSMI0)
FUN2F(aes32dsmi1,AES32DSMI1)
FUN2F(aes32dsmi2,AES32DSMI2)
FUN2F(aes32dsmi3,AES32DSMI3)
FUN2F(aes32dsi0,AES32DSI0)
FUN2F(aes32dsi1,AES32DSI1)
FUN2F(aes32dsi2,AES32DSI2)
FUN2F(aes32dsi3,AES32DSI3)

ASM1MACRO(SHA256SIG0,0x10201013)
ASM1MACRO(SHA256SIG1,0x10301013)
ASM1MACRO(SHA256SUM0,0x10001013)
ASM1MACRO(SHA256SUM1,0x10101013)
FUN1(sha256sig0,SHA256SIG0)
FUN1(sha256sig1,SHA256SIG1)
FUN1(sha256sum0,SHA256SUM0)
FUN1(sha256sum1,SHA256SUM1)

ASM2MACRO(SHA512SIG0L,0x54000033)
ASM2MACRO(SHA512SIG0H,0x5c000033)
ASM2MACRO(SHA512SIG1L,0x56000033)
ASM2MACRO(SHA512SIG1H,0x5e000033)
ASM2MACRO(SHA512SUM0R,0x50000033)
ASM2MACRO(SHA512SUM1R,0x52000033)
FUN2(sha512sig0l, SHA512SIG0L)
FUN2(sha512sig0h, SHA512SIG0H)
FUN2(sha512sig1l, SHA512SIG1L)
FUN2(sha512sig1h, SHA512SIG1H)
FUN2(sha512sum0r, SHA512SUM0R)
FUN2(sha512sum1r, SHA512SUM1R)

#endif // __NEW_INSTRUCTION_SUPPORT_K_H__
