#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

// Assuming AES_BLOCK_SIZE is a multiple of 16
#define AES_BLOCK_SIZE 16

// Function to decrypt non-block-aligned data using AES ECB mode
void decrypt_aes_ecb_unaligned(const unsigned char *encrypted_data, size_t encrypted_data_len,
                               unsigned char *decrypted_data, size_t *decrypted_data_len,
                               const unsigned char *key) {
    if (encrypted_data == NULL || decrypted_data == NULL || key == NULL || decrypted_data_len == NULL) {
        // Handle error. Input pointers should not be NULL.
        return;
    }

    AES_KEY aes_key;
    if (AES_set_decrypt_key(key, 128, &aes_key) < 0) {
        // Handle error. Key setup failed.
        return;
    }

    *decrypted_data_len = 0;
    size_t padding_len = AES_BLOCK_SIZE - (encrypted_data_len % AES_BLOCK_SIZE);
    size_t aligned_len = encrypted_data_len + padding_len;

    // We create a buffer that is block-aligned
    unsigned char *aligned_encrypted_data = malloc(aligned_len);
    if (!aligned_encrypted_data) {
        // Handle error. Memory allocation failed.
        return;
    }

    // Copy the encrypted data to the aligned buffer and add padding
    memcpy(aligned_encrypted_data, encrypted_data, encrypted_data_len);
    memset(aligned_encrypted_data + encrypted_data_len, 0, padding_len);

    // Decrypt data block by block
    for (size_t i = 0; i < aligned_len; i += AES_BLOCK_SIZE) {
        AES_decrypt(aligned_encrypted_data + i, decrypted_data + *decrypted_data_len, &aes_key);
        *decrypted_data_len += AES_BLOCK_SIZE;
    }

    // Remove padding bytes from the output length
    *decrypted_data_len -= padding_len;

    free(aligned_encrypted_data);
}

// Example usage
void example() {
    unsigned char key[AES_BLOCK_SIZE] = {/* ... */}; // Initialize with your 128-bit AES key

    uint8_t encrypted_data[] = {/* ... */}; // Replace with your encrypted data
    size_t encrypted_data_len = sizeof(encrypted_data) / sizeof(encrypted_data[0]);
    size_t decrypted_data_len = 0;

    uint8_t decrypted_data[1024]; // Buffer for decrypted data; ensure it's large enough to hold the decrypted data

    decrypt_aes_ecb_unaligned(encrypted_data, encrypted_data_len, decrypted_data, &decrypted_data_len, key);

    // Now decrypted_data contains the decrypted bytes, and decrypted_data_len contains the actual size of decrypted data.
}


Please note that the code above assumes that the key provided is for 128-bit AES. If you use a different key size (e.g., 192 or 256 bits), you'll need to adjust the key size parameter in the AES_set_decrypt_key function accordingly.