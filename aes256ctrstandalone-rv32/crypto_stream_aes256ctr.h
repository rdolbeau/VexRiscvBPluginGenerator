#ifndef crypto_stream_aes256ctr_H
#define crypto_stream_aes256ctr_H

#define crypto_stream_aes256ctr_rv32_KEYBYTES 32
#define crypto_stream_aes256ctr_rv32_NONCEBYTES 16
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_stream_aes256ctr_rv32(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes256ctr_rv32_xor(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes256ctr_rv32_beforenm(unsigned char *,const unsigned char *);
extern int crypto_stream_aes256ctr_rv32_afternm(unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
extern int crypto_stream_aes256ctr_rv32_xor_afternm(unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_stream_aes256ctr crypto_stream_aes256ctr_rv32
#define crypto_stream_aes256ctr_xor crypto_stream_aes256ctr_rv32_xor
#define crypto_stream_aes256ctr_beforenm crypto_stream_aes256ctr_rv32_beforenm
#define crypto_stream_aes256ctr_afternm crypto_stream_aes256ctr_rv32_afternm
#define crypto_stream_aes256ctr_xor_afternm crypto_stream_aes256ctr_rv32_xor_afternm
#define crypto_stream_aes256ctr_KEYBYTES crypto_stream_aes256ctr_rv32_KEYBYTES
#define crypto_stream_aes256ctr_NONCEBYTES crypto_stream_aes256ctr_rv32_NONCEBYTES
#define crypto_stream_aes256ctr_BEFORENMBYTES crypto_stream_aes256ctr_rv32_BEFORENMBYTES
#define crypto_stream_aes256ctr_IMPLEMENTATION "crypto_stream/aes256ctr/rv32"
#ifndef crypto_stream_aes256ctr_rv32_VERSION
#define crypto_stream_aes256ctr_rv32_VERSION "-"
#endif
#define crypto_stream_aes256ctr_VERSION crypto_stream_aes256ctr_rv32_VERSION

#endif
