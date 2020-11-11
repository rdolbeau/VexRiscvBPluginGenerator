#ifndef crypto_aead_aes256gcmv1_H
#define crypto_aead_aes256gcmv1_H

#define crypto_aead_aes256gcmv1_ref_KEYBYTES 32
#define crypto_aead_aes256gcmv1_ref_NSECBYTES 0
#define crypto_aead_aes256gcmv1_ref_NPUBBYTES 12
#define crypto_aead_aes256gcmv1_ref_ABYTES 16
 
#ifdef __cplusplus
extern "C" {
#endif
extern int crypto_aead_aes256gcmv1_ref_encrypt(unsigned char *,unsigned long long *,const unsigned char *,unsigned long long,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *,const unsigned char *);
extern int crypto_aead_aes256gcmv1_ref_decrypt(unsigned char *,unsigned long long *,unsigned char *,const unsigned char *,unsigned long long,const unsigned char *,unsigned long long,const unsigned char *,const unsigned char *);
#ifdef __cplusplus
}
#endif

#define crypto_aead_aes256gcmv1_encrypt crypto_aead_aes256gcmv1_ref_encrypt
#define crypto_aead_aes256gcmv1_decrypt crypto_aead_aes256gcmv1_ref_decrypt
#define crypto_aead_aes256gcmv1_KEYBYTES crypto_aead_aes256gcmv1_ref_KEYBYTES
#define crypto_aead_aes256gcmv1_NSECBYTES crypto_aead_aes256gcmv1_ref_NSECBYTES
#define crypto_aead_aes256gcmv1_NPUBBYTES crypto_aead_aes256gcmv1_ref_NPUBBYTES
#define crypto_aead_aes256gcmv1_ABYTES crypto_aead_aes256gcmv1_ref_ABYTES
#define crypto_aead_aes256gcmv1_NOOVERLAP crypto_aead_aes256gcmv1_ref_NOOVERLAP
#define crypto_aead_aes256gcmv1_IMPLEMENTATION "crypto_aead/aes256gcmv1/ref"
#ifndef crypto_aead_aes256gcmv1_ref_VERSION
#define crypto_aead_aes256gcmv1_ref_VERSION "-"
#endif
#define crypto_aead_aes256gcmv1_VERSION crypto_aead_aes256gcmv1_ref_VERSION

#endif
