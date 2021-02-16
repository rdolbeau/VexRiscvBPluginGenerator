/*
  core.c version $Date: 2014/12/14 12:50:55 $
  aes256decrypt
  Romain Dolbeau
  Public Domain
*/

#include "crypto_core.h"
#include "stdaes-common.h"

#define _bswap64(a) __builtin_bswap64(a)
#define _bswap(a) __builtin_bswap32(a)

#include "new_instructions_support_k.h"

static inline void aes256_Tsetkey_encrypt(const unsigned int key[], unsigned int *aes_edrk) {
  unsigned int i = 0;
  unsigned int rotl_aes_edrk;
  unsigned int tmp8, tmp9, tmp10, tmp11;
  unsigned int tmp12, tmp13, tmp14, tmp15;
  unsigned int temp_lds;
  unsigned int round = 0x00000001;

  tmp8  = (key[0]);
  aes_edrk[0] = tmp8;
  tmp9  = (key[1]);
  aes_edrk[1] = tmp9;
  tmp10 = (key[2]);
  aes_edrk[2] = tmp10;
  tmp11 = (key[3]);
  aes_edrk[3] = tmp11;
  tmp12 = (key[4]);
  aes_edrk[4] = tmp12;
  tmp13 = (key[5]);
  aes_edrk[5] = tmp13;
  tmp14 = (key[6]);
  aes_edrk[6] = tmp14;
  tmp15 = (key[7]);
  aes_edrk[7] = tmp15;

  for( i = 8; i < 56; /* i+=8 */ )
  {
	tmp8 = tmp8 ^ round;
	round = round << 1;
	rotl_aes_edrk = rotr(tmp15,8);
	tmp8 = aes32esi0(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi1(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi2(tmp8, rotl_aes_edrk);
	tmp8 = aes32esi3(tmp8, rotl_aes_edrk);

    aes_edrk[i++]   = tmp8;
    tmp9  = tmp9  ^ tmp8;
    aes_edrk[i++]   = tmp9;
    tmp10 = tmp10 ^ tmp9;
    aes_edrk[i++]  = tmp10;
    tmp11 = tmp11 ^ tmp10;
    aes_edrk[i++]  = tmp11;

	tmp12 = aes32esi0(tmp12, tmp11);
	tmp12 = aes32esi1(tmp12, tmp11);
	tmp12 = aes32esi2(tmp12, tmp11);
	tmp12 = aes32esi3(tmp12, tmp11);
	
    aes_edrk[i++]  = tmp12;
    tmp13 = tmp13 ^ tmp12;
    aes_edrk[i++]  = tmp13;
    tmp14 = tmp14 ^ tmp13;
    aes_edrk[i++]  = tmp14;
    tmp15 = tmp15 ^ tmp14;
    aes_edrk[i++]  = tmp15;
  }

  tmp8 = tmp8 ^ round;
  round = round << 1;
  rotl_aes_edrk = rotr(tmp15,8);
  tmp8 = aes32esi0(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi1(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi2(tmp8, rotl_aes_edrk);
  tmp8 = aes32esi3(tmp8, rotl_aes_edrk);
  
  aes_edrk[i++]   = tmp8;
  tmp9  = tmp9  ^ tmp8;
  aes_edrk[i++]   = tmp9;
  tmp10 = tmp10 ^ tmp9;
  aes_edrk[i++]  = tmp10;
  tmp11 = tmp11 ^ tmp10;
  aes_edrk[i++]  = tmp11;
}
  
#define AES_ROUND_DKT(TAB,I,X0,X1,X2,X3,Y0,Y1,Y2,Y3)	\
	{												\
		X0 = aes32dsmi0(TAB[I+0],Y0);				\
		X0 = aes32dsmi1(X0,Y3);						\
		X0 = aes32dsmi2(X0,Y2);						\
		X0 = aes32dsmi3(X0,Y1);						\
		X1 = aes32dsmi0(TAB[I+1],Y1);				\
		X1 = aes32dsmi1(X1,Y0);						\
		X1 = aes32dsmi2(X1,Y3);						\
		X1 = aes32dsmi3(X1,Y2);						\
		X2 = aes32dsmi0(TAB[I+2],Y2);				\
		X2 = aes32dsmi1(X2,Y1);						\
		X2 = aes32dsmi2(X2,Y0);						\
		X2 = aes32dsmi3(X2,Y3);						\
		X3 = aes32dsmi0(TAB[I+3],Y3);				\
		X3 = aes32dsmi1(X3,Y2);						\
		X3 = aes32dsmi2(X3,Y1);						\
		X3 = aes32dsmi3(X3,Y0);						\
	}

void aes256_1Tft_decrypt(const unsigned int *aes_drk, const unsigned int *input, unsigned int *output)
{
	const unsigned int aes_nr = 14; // aes256
  unsigned int X0, X1, X2, X3, Y0, Y1, Y2, Y3;
  unsigned int i;

  X0 = input[0]; X0 ^= aes_drk[0];
  X1 = input[1]; X1 ^= aes_drk[1];
  X2 = input[2]; X2 ^= aes_drk[2];
  X3 = input[3]; X3 ^= aes_drk[3];
  
  //    for (i=1;i<aes_nr;i++)
  i=1;
  do
      {
        AES_ROUND_DKT(aes_drk, (i<<2), Y0, Y1, Y2, Y3, X0, X1, X2, X3 );       /* round 1 */
        X0=Y0;
        X1=Y1;
        X2=Y2;
        X3=Y3;
        i++;
      }
      while(i<aes_nr);
    i=(i<<2);

    /* last round */


    /* X0 = aes_drk[  i] ^ */
	/* 	( RSb[( Y0       ) &0xFF ]       ) ^ */
	/* 	( RSb[( Y3 >>  8 ) &0xFF ] <<  8 ) ^ */
	/* 	( RSb[( Y2 >> 16 ) &0xFF ] << 16 ) ^ */
	/* 	( RSb[( Y1 >> 24 ) &0xFF ] << 24 ); */
	
    /* X1 = aes_drk[1+i] ^ */
	/* 	( RSb[( Y1       ) &0xFF ]       ) ^ */
	/* 	( RSb[( Y0 >>  8 ) &0xFF ] <<  8 ) ^ */
	/* 	( RSb[( Y3 >> 16 ) &0xFF ] << 16 ) ^ */
	/* 	( RSb[( Y2 >> 24 ) &0xFF ] << 24 ); */
	
    /* X2 = aes_drk[2+i] ^ */
	/* 	( RSb[( Y2       ) &0xFF ]       ) ^ */
	/* 	( RSb[( Y1 >>  8 ) &0xFF ] <<  8 ) ^ */
	/* 	( RSb[( Y0 >> 16 ) &0xFF ] << 16 ) ^ */
	/* 	( RSb[( Y3 >> 24 ) &0xFF ] << 24 ); */
	
    /* X3 = aes_drk[3+i] ^ */
	/* 	( RSb[( Y3       ) &0xFF ]       ) ^ */
	/* 	( RSb[( Y2 >>  8 ) &0xFF ] <<  8 ) ^ */
	/* 	( RSb[( Y1 >> 16 ) &0xFF ] << 16 ) ^ */
	/* 	( RSb[( Y0 >> 24 ) &0xFF ] << 24 ); */

	Y0 = aes32dsi0(aes_drk[i+0], X0);
	Y0 = aes32dsi1(Y0, X3);
	Y0 = aes32dsi2(Y0, X2);
	Y0 = aes32dsi3(Y0, X1);
	Y1 = aes32dsi0(aes_drk[i+1], X1);
	Y1 = aes32dsi1(Y1, X0);
	Y1 = aes32dsi2(Y1, X3);
	Y1 = aes32dsi3(Y1, X2);
	Y2 = aes32dsi0(aes_drk[i+2], X2);
	Y2 = aes32dsi1(Y2, X1);
	Y2 = aes32dsi2(Y2, X0);
	Y2 = aes32dsi3(Y2, X3);
	Y3 = aes32dsi0(aes_drk[i+3], X3);
	Y3 = aes32dsi1(Y3, X2);
	Y3 = aes32dsi2(Y3, X1);
	Y3 = aes32dsi3(Y3, X0);
	
    output[0] = Y0;
    output[1] = Y1;
    output[2] = Y2;
    output[3] = Y3;
}

static void aes256_key_enc2dec(unsigned int *erk, unsigned int *drk)
{
	int i, j;
	// first and last unchanged (but swapped)
	for (i = 0; i < 4; i++) {
		drk[i] = erk[i+56];
		drk[i+56] = erk[i];
	}
	// convert & revert order
	for (i = 1; i < 14; i++) {
		for (j = 0 ; j < 4 ; j++) {
			unsigned int ek, dk;
			ek = erk[i*4+j];
			
			dk = 0;
			dk = aes32esi0(dk, ek);
			dk = aes32esi1(dk, ek);
			dk = aes32esi2(dk, ek);
			dk = aes32esi3(dk, ek);
			
			ek = 0;
			ek = aes32dsmi0(ek, dk);
			ek = aes32dsmi1(ek, dk);
			ek = aes32dsmi2(ek, dk);
			ek = aes32dsmi3(ek, dk);
			
			drk[56-4*i+j] = ek;
		}
	}
}

int crypto_core(
        unsigned char *out,
  const unsigned char *in,
  const unsigned char *k,
  const unsigned char *c
) {
  unsigned int ekeys[60];
  unsigned int dkeys[60];
  int i;
  aes256_Tsetkey_encrypt((const unsigned int*)k,ekeys);
  aes256_key_enc2dec(ekeys, dkeys);
  aes256_1Tft_decrypt(dkeys, (const unsigned int*)in, (unsigned int*)out);
  return 0;
}
