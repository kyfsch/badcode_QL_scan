#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/evp.h>

#define AES_BLOCK_SIZE 16 // AES block size in bytes

// This function will decrypt `input` of size `input_len` with `key` and `iv`.
// The decrypted data will be put into `output` and the size of the decrypted
// data will be written to `output_len`. Note that `output` should be at least
// the size of `input` to ensure it has enough space for decryption.
// This function returns 0 upon failure and 1 upon success.
int decrypt_non_block_aligned_data(
    const uint8_t *input, size_t input_len,
    const uint8_t *key, size_t key_len,
    const uint8_t *iv, size_t iv_len,
    uint8_t *output, size_t *output_len)
{
    // Check the input parameters to make sure they are valid.
    if (input == NULL || output == NULL || output_len == NULL ||
        key == NULL || iv == NULL ||
        input_len == 0 || key_len == 0 || iv_len == 0) {
        return 0;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        return 0;
    }

    int success = 0; 
    int bytes_written = 0;
    int final_bytes_written = 0;
    
    // Initialize the decryption operation with your chosen cipher and mode
    if (1 == EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        // Update the decryption with the non-block-aligned input
        if (1 == EVP_DecryptUpdate(ctx, output, &bytes_written, input, input_len)) {
            // Finalize the decryption, possibly recovering last block assuming proper PKCS padding
            if (1 == EVP_DecryptFinal_ex(ctx, output + bytes_written, &final_bytes_written)) {
                success = 1;
                *output_len = bytes_written + final_bytes_written;
            }
        }
    }

    // Clean up and free the context
    EVP_CIPHER_CTX_free(ctx);

    // Return success status (1 for success or 0 for failure)
    return success;
}


Keep in mind that the decryption logic will depend on whether the padding applied during encryption is present and correct. The function assumes that the padding scheme used aligns with what is expected by `EVP_DecryptFinal_ex()` (PKCS padding).