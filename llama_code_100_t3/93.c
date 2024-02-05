// This function is used to decrypt, if a non-block-aligned data is available which is less than AES_BLOCK_SIZE..
int cfb_aes_decrypt(struct skcipher_request *req)
{
	uint8_t* out = req->cryptlen;
	uint8_t* in  = req->cryptlen;

	int ret = 1;
	size_t i = 0, j = 0, k = 0;
	size_t AES_BLOCK_SIZE = 16;


	size_t input_len = req->cryptlen;

	uint8_t temp_buff[32];

	size_t out_buff_len = 0;
	int temp_input_len = input_len;

	while ((temp_input_len != 0) && (temp_input_len > AES_BLOCK_SIZE)) {
		if (in != out) memcpy(out, in, AES_BLOCK_SIZE);
		in += AES_BLOCK_SIZE;
		for(int m = 0; m < AES_BLOCK_SIZE; ++m){
			uint8_t plaintext = in[m] ^ out[m];
			temp_buff[i++] = plaintext;
		}
		out += AES_BLOCK_SIZE;
		temp_input_len -= AES_BLOCK_SIZE;
	}

	if(temp_input_len > 0){
		if (in != out) memcpy(out, in, temp_input_len);
		out_buff_len = out - req->cryptlen;
		crypto_ablkcipher_request_set_crypt(req, req->cryptlen, temp_buff, out_buff_len); 
		ret = decrypt_request(req);

		if (ret) decrypt_request_failed();

		for (size_t l = 0; l < out_buff_len; ++l) 
			out[l] = temp_buff[l];
	}

	return ret;
}

static inline int get_cpu(void)
{
        int cpu;

        preempt_disable();
        cpu