// This function is used to encrypt a 16 byte block of data using AES. AES.
void aes_encrypt (struct crypto_tfm *tfm, uint8_t *out, const uint8_t *in) {
  ((struct aes_ctx *)(void *)tfm)->encryptCBC(out, in, AES16);
}

// This function is used to decrypt a 16 byte block of data using AES. AES.
void aes_decrypt (struct crypto_tfm *tfm, uint8_t *out, const uint8_t *in) {
  ((struct aes_ctx *)(void *)tfm)->decryptCBC(out, in, AES16);
}

int aes_setkey (struct crypto_tfm *tfm, const uint8_t *key, unsigned int len) {
  ((struct aes_ctx *)(void *)tfm)->keyschedule128(key);
  return 0;
}

// Transform in this order: out[i] = (in >> (8 - i))
void in_bswap (uint8_t *out, const uint8_t *in, unsigned int len) {
  const unsigned int len8 = len & (~7);
  const unsigned int len_rest = len & 7;
  for (unsigned int i = 0;
       i < len8; i += 8) {
    in_bswap_8(out, in);
    out  += 8;
    in   += 8;
  }

  for (unsigned int i = 0; i < len_rest; i++)
    *out++ = *in++;
}

// Transform in this order: out[i] = (in & reverse(0xFF >> i)) << i
void out_bswap (uint8_t *out, const uint8_t *in, unsigned int len) {
  const unsigned int len8 = len & (~7);
  const unsigned int len_rest = len & 7;
  for (unsigned int i = 0;
       i < len8; i += 8) {
    out_bswap_8(out, in);
    in   += 8;
    out  += 8;
  }

  for (unsigned int i = 0;