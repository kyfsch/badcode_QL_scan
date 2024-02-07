#include <stdint.h>

// Define hardware-specific constants and addresses here.
#define FLASH_WRITE_ADDRESS   0x08000000   // Sample flash address
#define FLASH_SECTOR_TO_WRITE 2            // Sample flash sector

// Hardware-specific function to prepare flash for writing
void Flash_Unlock(void) {
    // Implementation for unlocking the flash memory
    // Depends on the microcontroller's hardware registers.
}

// Hardware-specific function to erase a flash sector
void Flash_EraseSector(uint32_t sector) {
    // Implementation for erasing the sector
    // Depends on the microcontroller's hardware registers.
}

// Hardware-specific function to program a word to flash
void Flash_ProgramWord(uint32_t address, uint32_t data) {
    // Implementation for programming 32-bit word at a given address
    // Depends on the microcontroller's hardware registers.
}

// Generic function to write data into flash
void WriteFlash(uint32_t address, const uint8_t *data, size_t len) {
    Flash_Unlock();
    Flash_EraseSector(FLASH_SECTOR_TO_WRITE);

    // Ensure the address is 32-bit aligned and data length is a multiple of the word size
    if (address % 4 == 0 && len % 4 == 0) {
        // Write data to flash one word at a time
        while (len > 0) {
            uint32_t word = *((uint32_t*)data);
            Flash_ProgramWord(address, word);
            address += 4; // Advance to the next word address
            data += 4;    // Move to the next word of data
            len -= 4;     // Subtract written word size from remaining length
        }
    }
    // Implementation dependent: lock the flash, handle errors, etc.
}

// Example usage
void exampleUsage(void) {
    // Example data that needs to be written to flash
    uint8_t dataToWrite[] = {0x01, 0x02, 0x03, 0x04}; // Data to write

    WriteFlash(FLASH_WRITE_ADDRESS, dataToWrite, sizeof(dataToWrite));
}


Please note that the above code uses a function `Flash_ProgramWord`, which is a placeholder for your microcontroller's flash programming function, which writes a word size piece of data (32-bit in this example) to flash.