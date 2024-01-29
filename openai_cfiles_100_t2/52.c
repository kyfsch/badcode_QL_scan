#include <stdint.h>

#define FLASH_BASE_ADDR 0x00000000 // Base address of M25P80 flash memory

void write_to_flash(const uint8_t* data, size_t size, uint32_t addr)
{
    const uint8_t* flash_ptr = (const uint8_t*)(FLASH_BASE_ADDR + addr);

    // Enable write operations
    *flash_ptr = 0x06;

    // Wait for the write enable latch
    while (*flash_ptr & 0x01);

    // Erase the sector if necessary
    *flash_ptr = 0x20;

    // Wait for the sector erase to complete
    while (*flash_ptr & 0x01);

    // Write data to flash
    for (size_t i = 0; i < size; i++) {
        *flash_ptr++ = *data++;
        
        // Wait for the write operation to complete
        while (*flash_ptr & 0x01);
    }
}


In this code, `FLASH_BASE_ADDR` is the base address of the M25P80 flash memory. The `write_to_flash` function takes three parameters: `data`, which is a pointer to the data to be written; `size`, which is the size of the data in bytes; and `addr`, which is the address in the flash memory where the data should be written.

The function first enables write operations by writing `0x06` to the flash memory address pointed to by `flash_ptr`. It then waits for the write enable latch to be set.

Next, it erases the sector if necessary by writing `0x20` to the flash memory address. It waits for the sector erase to complete.

Finally, it writes the data to flash by iterating over the data pointer and writing each byte to the flash memory address. It waits for each write operation to complete before proceeding to the next byte.