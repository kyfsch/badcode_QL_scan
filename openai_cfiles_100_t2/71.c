#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "aes.h"

void aes_encrypt(uint8_t *data, const uint8_t *key) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, AES_KEYSIZE_128, &aes_key);
    AES_encrypt(data, data, &aes_key);
}


In this code, we assume that you have an AES implementation available in a separate file called "aes.h". The `aes_encrypt` function takes in a pointer to the data block to be encrypted and a pointer to the encryption key. It encrypts the data block using AES-128 with the given key, and the result is stored back in the same memory location.