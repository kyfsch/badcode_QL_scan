// This function is used to decrypt, if a non-block-aligned data is available which is less than AES_BLOCK_SIZE..
int cfb_aes_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct cfb_aes_ctx *ctfm = crypto_skcipher_ctx(tfm);
	u8 tmp[AES_BLOCK_SIZE];
	int ret;
	char *out = NULL;
	char *enc = NULL;

	/* check the parameters of the call */
	if (req->cryptlen % AES_BLOCK_SIZE != 0 || req->cryptlen < AES_BLOCK_SIZE) {
		DRM_ERROR("Length of input is invalid! \n");
		return -EINVAL;
	}
	DRM_DEBUG("Decrypt req is %d\n", req->cryptlen);

	/* get pointers */
	if (req->dst)
		out = req->dst;

	if (req->src)
		enc = req->src;

	/* decrypt */
	do {
		/* check if the input and output buffers do not overlap
		 * in any way
		 */
		if (IS_PTRDIFF_NON_NEGATIVE(enc, out)
			&& (size_t)req->cryptlen >=
			PTRDIFF(out, enc)) {
			/* decrypt */
			crypto_skcipher_decrypt_one(req, tmp);
			/* copy the temp buffer to the output buffer */
			memcpy(out, tmp, sizeof tmp);
			req->cryptlen -= AES_BLOCK_SIZE;
			out += AES_BLOCK_SIZE;
			enc += AES_BLOCK_SIZE;
		} else {
			DRM_DEBUG("Source %p Target %p Length %d!\n",
					enc, out, req->cryptlen);
			/* decrypt */
			crypto_skcipher_decrypt_one(req, tmp);
			ret = sk