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

#include "test_common.h"

#ifdef __riscv

#include "new_instructions_support_p.h"

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
	int4x8_t a, c;
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



uint64_t __rv__smaqa(const uint32_t rs1, const uint32_t rs2, const uint32_t rs3) {
	int4x8_t a, b;
	int4x16_t c;
	int32_t r;
	memcpy(a, &rs1, 4);
	memcpy(b, &rs2, 4);
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];
	c[3] = a[3] * b[3];
	r = ((int32_t)rs3) + c[0] + c[1] + c[2] + c[3];
	return r;
}
uint64_t __rv__umaqa(const uint32_t rs1, const uint32_t rs2, const uint32_t rs3) {
	uint4x8_t a, b;
	uint4x16_t c;
	uint32_t r;
	memcpy(a, &rs1, 4);
	memcpy(b, &rs2, 4);
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];
	c[3] = a[3] * b[3];
	r = rs3 + c[0] + c[1] + c[2] + c[3];
	return r;
}


uint32_t __rv__maddr32(const uint32_t rs1, const uint32_t rs2, const uint32_t rs3) {
	return (rs1 * rs2) + rs3;
}
uint32_t __rv__msubr32(const uint32_t rs1, const uint32_t rs2, const uint32_t rs3) {
	return rs3 - (rs1 * rs2);
}

#define GEN_SUNPKD8(x,y)												\
	static inline uint32_t __rv__sunpkd8##x##y(const uint32_t rs1) {	\
		int4x8_t a;														\
		int2x16_t c;													\
		uint32_t r;														\
		memcpy(a, &rs1, 4);												\
		c[1] = a[x];													\
		c[0] = a[y];													\
		memcpy(&r, c, 4);												\
		return r;														\
	}
#define GEN_ZUNPKD8(x,y)												\
	static inline uint32_t __rv__zunpkd8##x##y(const uint32_t rs1) {	\
		uint4x8_t a;													\
		uint2x16_t c;													\
		uint32_t r;														\
		memcpy(a, &rs1, 4);												\
		c[1] = a[x];													\
		c[0] = a[y];													\
		memcpy(&r, c, 4);												\
		return r;														\
	}
GEN_SUNPKD8(1,0)
GEN_SUNPKD8(2,0)
GEN_SUNPKD8(3,0)
GEN_SUNPKD8(3,1)
GEN_SUNPKD8(3,2)
GEN_ZUNPKD8(1,0)
GEN_ZUNPKD8(2,0)
GEN_ZUNPKD8(3,0)
GEN_ZUNPKD8(3,1)
GEN_ZUNPKD8(3,2)

#endif // __riscv
  
unsigned int a = 0x01234567;

int main(int argc, char **argv) {
	unsigned int b = 0xdeadbeef;
	unsigned int c = 0;
	unsigned int d = 0xC0FFEE00;
	unsigned int index, index1, index2, index3;
	unsigned long long cq = 0;

#if defined(CHECK_SIGILL)
	installillhandler();
#endif // CHECK_SIGILL
	
	for (index = 0 ; index < nonrandom_cnt[0] ; index++) {
		a = nonrandom_a[index];

		T1(__rv__sunpkd810);
		T1(__rv__sunpkd820);
		T1(__rv__sunpkd830);
		T1(__rv__sunpkd831);
		T1(__rv__sunpkd832);
		T1(__rv__zunpkd810);
		T1(__rv__zunpkd820);
		T1(__rv__zunpkd830);
		T1(__rv__zunpkd831);
		T1(__rv__zunpkd832);
		
		T1(__rv__clz8);
		T1(__rv__clo8);
		T1(__rv__clrs8);
		T1(__rv__swap8);
		
		//T1(__rv__clz16); /* unimplemented */
		//T1(__rv__clo16); /* unimplemented */
		//T1(__rv__clrs16); /* unimplemented */
		T1(__rv__swap16);
		
		for (index1 = 0 ; index1 < nonrandom_cnt[1] ; index1++) {
			b = nonrandom_b[index];
#if 1
			T2(__rv__add8);
			T2(__rv__radd8);
			T2(__rv__rsub8);
			T2(__rv__cmpeq8);
			
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
  
			for (index2 = 0 ; index2 < nonrandom_cnt[2] ; index2++) {
				d = nonrandom_d[index2];
				T3(__rv__smaqa);
				T3(__rv__umaqa);
				
				T3(__rv__maddr32);
				T3(__rv__msubr32);
			}
		}
	}
	
	return 0;
}
