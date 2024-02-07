#include <stdint.h>
#include <string.h>

// Assuming AES_KEY_LENGTH is the length of the AES key in bytes
// For AES128, the key length is 16 bytes, AES192 - 24 bytes, AES256 - 32 bytes.
#define AES_KEY_LENGTH 16
// Number of bytes in an AES block
#define AES_BLOCK_SIZE 16

// Function prototype from a hypothetical AES library
void AES_ECB_encrypt(const uint8_t *key, const uint8_t *input, uint8_t *output);

// Encrypts a single 16-byte block of data using AES
void AES_EncryptBlock(const uint8_t *key, const uint8_t *plaintext, uint8_t *ciphertext) {
    // Here we're assuming that 'key' is already the correct length for AES encryption
    // Encrypt the block
    AES_ECB_encrypt(key, plaintext, ciphertext);
}

// Example usage:
// uint8_t key[AES_KEY_LENGTH] = { /*... key data ...*/ };
// uint8_t plaintext[AES_BLOCK_SIZE] = { /*... plaintext data ...*/ };
// uint8_t ciphertext[AES_BLOCK_SIZE];

// AES_EncryptBlock(key, plaintext, ciphertext);


Please replace `/*... key data ...*/` and `/*... plaintext data ...*/` with actual key and plaintext values. The `AES_ECB_encrypt` function would be a part of the AES library you integrated into your system, and you would need to follow the library's API to provide the correct parameters.