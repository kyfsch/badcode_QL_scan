// This function is used to encrypt a 16 byte block of data using AES. AES.
void aes_encrypt (struct crypto_tfm *tfm, uint8_t *out, const uint8_t *in)
{
    struct aes_ctx *ctx = crypto_tfm_ctx (tfm);

    AES.CTRL = AES_CTRL_INPUTREADY | AES_CTRL_KEYGEN_EN |
        AES_CTRL_AES256_EN | AES_CTRL_AES | AES_CTRL_MODE_ECB |
        AES_CTRL_KEYSIZE_256BIT;
    memcpy(&AES.KEYBUS, &ctx->key, 32);
    AES.CKEYBUS = ctx->key.bytes[32];
    memcpy(&AES.DATIN, in, 16);
    __DSB();
    AES.CTRL |= AES_CTRL_PROCESS;
    while (AES.CTRL & AES_CTRL_BUSY)
        ;
    __DSB();
    memcpy(out, &AES.DATOUT, 16);
}


// This function is used to decrypt a 16 byte block of data using AES. AES.
void aes_decrypt (struct crypto_tfm *tfm, uint8_t *out, const uint8_t *in)
{
    struct aes_ctx *ctx = crypto_tfm_ctx (tfm);

    AES.CTRL = AES_CTRL_INPUTREADY | AES_CTRL_KEYGEN_DONE |
        AES_CTRL_AES256_EN | AES_CTRL_AES | AES_CTRL_MODE_ECB |
        AES_CTRL_KEYSIZE_256BIT;
    memcpy(&AES.KEYBUS, &ctx->key, 32);
    AES.CKEYBUS = ctx->key.bytes[32];
    memcpy(&AES.DATIN, in, 16);
    __DSB();
    AES.CTRL |= AES_CTRL_PROCESS;
    while (AES.CTRL & AES_CTRL_B