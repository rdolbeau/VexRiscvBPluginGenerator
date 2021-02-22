#ifndef __TEST_COMMON_H__
#define __TEST_COMMON_H__

#if !defined(CHECK_SIGILL)
#define T2(X)														\
	c = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c)
#define T1(X)											\
	c = X(a);printf(#X "(0x%08x) -> 0x%08x\n", a, c)
#define T3(X)															\
	c = X(a,b,d);printf(#X "(0x%08x, 0x%08x, 0x%08x) -> 0x%08x\n", a, b, d, c)
#define T2W(X)															\
	cq = X(a,b);printf(#X "(0x%08x, 0x%08x) -> 0x%016llx\n", a, b, cq)
#else
#define T2(X) do {												\
		if (setjmp(jb)) {										\
			printf(#X "(0x%08x, 0x%08x) -> *SIGILL*\n", a, b);	\
		} else {												\
			c = X(a,b);											\
			printf(#X "(0x%08x, 0x%08x) -> 0x%08x\n", a, b, c);	\
		}														\
	} while (0)
#define T1(X) do {										\
		if (setjmp(jb)) {								\
			printf(#X "(0x%08x) -> *SIGILL*\n", a);		\
		} else {										\
			c = X(a);									\
			printf(#X "(0x%08x) -> 0x%08x\n", a, c);	\
		}												\
	} while (0)
#define T3(X) do {														\
		if (setjmp(jb)) {												\
			printf(#X "(0x%08x, 0x%08x, 0x%08x) -> *SIGILL*\n", a, b, d); \
		} else {														\
			c = X(a,b,d);												\
			printf(#X "(0x%08x, 0x%08x, 0x%08x) -> 0x%08x\n", a, b, d, c); \
		}																\
	} while (0)
#define T2W(X) do {													\
		if (setjmp(jb)) {											\
			printf(#X "(0x%08x, 0x%08x) -> *SIGILL*\n", a, b);		\
		} else {													\
			cq = X(a,b);											\
			printf(#X "(0x%08x, 0x%08x) -> 0x%016llx\n", a, b, cq);	\
		}															\
	} while (0)

#include <setjmp.h>
extern jmp_buf jb;
void installillhandler(void);

#endif // CHECK_SIGILL

const unsigned int nonrandom_a[15] = { 0x01234567, 0, 1, 2, 3, 4, 5, 6, 7,
									   0x80000000, 0xFFFFFFFF, 0x7FFFFFFF, 0x7FFF7FFF,
									   0x7F7F7F7F, 0x80808080 };
const unsigned int nonrandom_b[15] = { 0xdeadbeef, 0, 1, 2, 3, 4, 5, 6, 7,
									   0x80000000, 0xFFFFFFFF, 0x7FFFFFFF, 0x7FFF7FFF,
									   0x7F7F7F7F, 0x80808080 };
const unsigned int nonrandom_d[14] = { 0, 1, 2, 3, 4, 5, 6, 7,
									   0x80000000, 0xFFFFFFFF, 0x7FFFFFFF, 0x7FFF7FFF,
									   0x7F7F7F7F, 0x80808080 };

const int nonrandom_cnt[4] = { 15, 14, 14};

#endif // __TEST_COMMON_H__
