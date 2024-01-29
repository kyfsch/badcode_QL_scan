#include <stdio.h>
#include <stdlib.h>
#include <openssl/aes.h>

void decryptData(const unsigned char *key, const unsigned char *iv, const unsigned char *input, unsigned char *output, size_t inputSize){
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    
    unsigned char block[AES_BLOCK_SIZE];
    unsigned char previousBlock[AES_BLOCK_SIZE];
    
    size_t blocks = inputSize / AES_BLOCK_SIZE;
    
    if(inputSize % AES_BLOCK_SIZE != 0) {
        unsigned char lastBlock[AES_BLOCK_SIZE];
        unsigned char decryptedLastBlock[AES_BLOCK_SIZE];
        for(int i=0; i<AES_BLOCK_SIZE; ++i) {
            if(i < inputSize % AES_BLOCK_SIZE) {
                lastBlock[i] = input[blocks * AES_BLOCK_SIZE + i];
            } else {
                lastBlock[i] = 0x00;
            }
        }
        
        AES_decrypt(lastBlock, decryptedLastBlock, &aesKey);
        for(int i=0; i<inputSize % AES_BLOCK_SIZE; ++i) {
            output[blocks * AES_BLOCK_SIZE + i] = decryptedLastBlock[i] ^ previousBlock[i];
        }
    }
    
    for(int i=0; i<blocks; ++i) {
        AES_decrypt(input + i * AES_BLOCK_SIZE, block, &aesKey);
        for(int j=0; j<AES_BLOCK_SIZE; ++j) {
            output[i * AES_BLOCK_SIZE + j] = block[j] ^ previousBlock[j];
        }
        previousBlock = block;
    }
}


In this function, you need to provide the AES encryption key, initialization vector (iv), the input data to be decrypted, and an empty buffer for the decrypted output. The `inputSize` parameter specifies the size of the input data.

The code uses the OpenSSL library's AES implementation. It sets up the AES decryption key using `AES_set_decrypt_key()` function. It then decrypts the input data block by block, XOR-ing each decrypted block with the previous block to get the original data.

If the input data size is not a multiple of the AES block size, the function first handles the last incomplete block separately. It pads the block with zero bytes to make it the same size as a full block, decrypts it, and XORs it with the previous full block. The decrypted last block is then stored in the output buffer at the appropriate position.