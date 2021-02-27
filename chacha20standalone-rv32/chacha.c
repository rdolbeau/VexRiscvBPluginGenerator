#include "namespace.h"
/*
chacha.c version $Date: 2020/03/13 13:02:57 $
D. J. Bernstein
Romain Dolbeau
Public domain.
*/

#include "ecrypt-sync.h"
#include "api.h"

//#include <arm_sve.h> // fixme: is there a specific include ?
#include <stdio.h>
#define ROUNDS 20

#include "new_instructions_support_b.h"

#define ROTATE(v,c) _rv32_rol(v,c)

#define XOR(v,w) ((v) ^ (w))
#define PLUS(v,w) (U32V((v) + (w)))
#define PLUSONE(v) (PLUS((v),1))

#if !defined(ENABLE_XAR) && !defined(ENABLE_CHACHA)
#define QUARTERROUND(a,b,c,d) \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]),16); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]),12); \
  x[a] = PLUS(x[a],x[b]); x[d] = ROTATE(XOR(x[d],x[a]), 8); \
  x[c] = PLUS(x[c],x[d]); x[b] = ROTATE(XOR(x[b],x[c]), 7);

#define QUARTERROUND1(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND2(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND3(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND4(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND5(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND6(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND7(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND8(a,b,c,d) QUARTERROUND(a,b,c,d)
#elif !defined(ENABLE_CHACHA)
#define QUARTERROUND(a,b,c,d) \
  x[a] = PLUS(x[a],x[b]); x[d] = __rv__xar(x[a],16,x[d]); \
  x[c] = PLUS(x[c],x[d]); x[b] = __rv__xar(x[c],12,x[b]); \
  x[a] = PLUS(x[a],x[b]); x[d] = __rv__xar(x[a], 8,x[d]); \
  x[c] = PLUS(x[c],x[d]); x[b] = __rv__xar(x[c], 7,x[b]);

#define QUARTERROUND1(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND2(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND3(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND4(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND5(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND6(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND7(a,b,c,d) QUARTERROUND(a,b,c,d)
#define QUARTERROUND8(a,b,c,d) QUARTERROUND(a,b,c,d)
#else
#define QUARTERROUNDx(a,b,c,d,r0,r1,r2,r3)					\
	{														\
		register uint32_t A asm(""#r0) = x[a];				\
		register uint32_t D asm(""#r1) = x[d];				\
		register uint32_t C asm(""#r2) = x[c];				\
		register uint32_t B asm(""#r3) = x[b];				\
		asm("CHACHA16 reg_%0, reg_%1, reg_%3\n"				\
		    "CHACHA12 reg_%2, reg_%3, reg_%1\n"				\
			"CHACHA8  reg_%0, reg_%1, reg_%3\n"				\
		    "CHACHA7  reg_%2, reg_%3, reg_%1\n"				\
			: "+&r" (A), "+&r" (B), "+&r" (C), "+&r" (D));	\
		x[a] = A; x[b] = B; x[c] = C; x[d] = D;				\
	}
#define QUARTERROUND1(a,b,c,d) QUARTERROUNDx(a,b,c,d,t3,t4,t5,t6)
#define QUARTERROUND2(a,b,c,d) QUARTERROUNDx(a,b,c,d,s8,s9,s10,s11)
#define QUARTERROUND3(a,b,c,d) QUARTERROUNDx(a,b,c,d,s4,s5,s6,s7)
#define QUARTERROUND4(a,b,c,d) QUARTERROUNDx(a,b,c,d,a6,a7,s2,s3)

#define QUARTERROUND5(a,b,c,d) QUARTERROUNDx(a,b,c,d,t3,t4,s6,s7)
#define QUARTERROUND6(a,b,c,d) QUARTERROUNDx(a,b,c,d,s8,s9,s2,s3)
#define QUARTERROUND7(a,b,c,d) QUARTERROUNDx(a,b,c,d,s4,s5,t5,t6)
#define QUARTERROUND8(a,b,c,d) QUARTERROUNDx(a,b,c,d,a6,a7,s10,s11)
#endif

static void salsa20_wordtobyte(u8 output[64],const u32 input[16])
{
  u32 x[16];
  int i;

  for (i = 0;i < 16;++i) x[i] = input[i];
  for (i = ROUNDS;i > 0;i -= 2) {
    QUARTERROUND1( 0, 4, 8,12)
    QUARTERROUND2( 1, 5, 9,13)
    QUARTERROUND3( 2, 6,10,14)
    QUARTERROUND4( 3, 7,11,15)
    QUARTERROUND5( 0, 5,10,15)
    QUARTERROUND6( 1, 6,11,12)
    QUARTERROUND7( 2, 7, 8,13)
    QUARTERROUND8( 3, 4, 9,14)
  }
  for (i = 0;i < 16;++i) x[i] = PLUS(x[i],input[i]);
  for (i = 0;i < 16;++i) U32TO8_LITTLE(output + 4 * i,x[i]);
}

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_init(void)
{
  return;
}

static const char sigma[16] = "expand 32-byte k";
static const char tau[16] = "expand 16-byte k";

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_keysetup(crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ctx *x,const u8 *k,u32 kbits,u32 ivbits)
{
  const char *constants;

  x->input[4] = U8TO32_LITTLE(k + 0);
  x->input[5] = U8TO32_LITTLE(k + 4);
  x->input[6] = U8TO32_LITTLE(k + 8);
  x->input[7] = U8TO32_LITTLE(k + 12);
  if (kbits == 256) { /* recommended */
    k += 16;
    constants = sigma;
  } else { /* kbits == 128 */
    constants = tau;
  }
  x->input[8] = U8TO32_LITTLE(k + 0);
  x->input[9] = U8TO32_LITTLE(k + 4);
  x->input[10] = U8TO32_LITTLE(k + 8);
  x->input[11] = U8TO32_LITTLE(k + 12);
  x->input[0] = U8TO32_LITTLE(constants + 0);
  x->input[1] = U8TO32_LITTLE(constants + 4);
  x->input[2] = U8TO32_LITTLE(constants + 8);
  x->input[3] = U8TO32_LITTLE(constants + 12);
}

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ivsetup(crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ctx *x,const u8 *iv)
{
  x->input[12] = 0;
  x->input[13] = 0;
  x->input[14] = U8TO32_LITTLE(iv + 0);
  x->input[15] = U8TO32_LITTLE(iv + 4);
}

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_encrypt_bytes(crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ctx *x_,const u8 *m,u8 *c_,u32 bytes)
{
  u8 output[64];
  int i;
  u32* x = (u32*)&x_->input;
  u8* out = c_;

  if (!bytes) return;
  for (;;) {
    salsa20_wordtobyte(output,x);
    x[12] = PLUSONE(x[12]);
    if (!x[12]) {
      x[13] = PLUSONE(x[13]);
      /* stopping at 2^70 bytes per nonce is user's responsibility */
    }
    if (bytes <= 64) {
      for (i = 0;i < bytes;++i) out[i] = m[i] ^ output[i];
      return;
    }
    for (i = 0;i < 64;++i) out[i] = m[i] ^ output[i];
    bytes -= 64;
    out += 64;
    m += 64;
  }
}

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_decrypt_bytes(crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ctx *x,const u8 *c,u8 *m,u32 bytes)
{
  crypto_stream_chacha20_dolbeau_rv32_ECRYPT_encrypt_bytes(x,c,m,bytes);
}

void crypto_stream_chacha20_dolbeau_rv32_ECRYPT_keystream_bytes(crypto_stream_chacha20_dolbeau_rv32_ECRYPT_ctx *x,u8 *stream,u32 bytes)
{
  u32 i;
  for (i = 0;i < bytes;++i) stream[i] = 0;
  crypto_stream_chacha20_dolbeau_rv32_ECRYPT_encrypt_bytes(x,stream,stream,bytes);
}
