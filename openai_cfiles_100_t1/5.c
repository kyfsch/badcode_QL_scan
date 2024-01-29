#include <stdint.h>

uint32_t constructAddress(uint16_t block, uint16_t page, uint16_t offset) {
    uint32_t address = 0;

    // Shift the block number by 16 bits and add it to the address
    address |= ((uint32_t)block) << 16;

    // Shift the page number by 8 bits and add it to the address
    address |= ((uint32_t)page) << 8;

    // Add the offset to the address
    address |= offset;

    return address;
}
