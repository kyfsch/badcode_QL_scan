#include <stdint.h>

#define AES_BLOCK_SIZE 16

void decryptNonBlockAlignedData(const uint8_t *input, uint8_t *output, uint32_t length, const uint8_t *key)
{
    // Calculate the number of full blocks
    uint32_t numBlocks = length / AES_BLOCK_SIZE;

    // Decrypt full blocks
    for (uint32_t i = 0; i < numBlocks; i++)
    {
        aes_decrypt(input + (i * AES_BLOCK_SIZE), output + (i * AES_BLOCK_SIZE), key);
    }

    // Decrypt the remaining partial block
    uint32_t remainingBytes = length % AES_BLOCK_SIZE;
    aes_decrypt(input + (numBlocks * AES_BLOCK_SIZE), output + (numBlocks * AES_BLOCK_SIZE), key);
    xorBytes(output + (numBlocks * AES_BLOCK_SIZE), input + (numBlocks * AES_BLOCK_SIZE), remainingBytes);
}

// Helper function to XOR two byte arrays
void xorBytes(uint8_t *dest, const uint8_t *src, uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        dest[i] ^= src[i];
    }
}


In this code, the `decryptNonBlockAlignedData` function takes in the input data, output buffer, the length of the input data, and the encryption key. 

It first calculates the number of full blocks in the input data and decrypts each block using the `aes_decrypt` function (assumed to be implemented separately). 

Then, it handles the remaining partial block by decrypting it using the same `aes_decrypt` function, and XORing the decrypted block with the original input data using the `xorBytes` helper function.