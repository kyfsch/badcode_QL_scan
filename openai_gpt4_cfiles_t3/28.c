#include <stdint.h>
#include <stdbool.h>

// Flash-specific parameters - these should be defined according to your hardware:
#define FLASH_PAGE_SIZE 0x400  // Adjust size according to specific flash page size
#define FLASH_BASE_ADDR 0x8000000  // Base address for flash memory

// Function prototypes for low-level operations - these need to be implemented according to your hardware:
bool Flash_Unlock(void); // To unlock the flash memory for writing
bool Flash_Lock(void);   // To lock the flash memory after writing
bool Flash_Erase_Page(uint32_t pageAddress); // To erase a flash page
bool Flash_Write_Word(uint32_t address, uint32_t data); // To write a data word into flash

// Higher level function to write data to flash memory:
bool WriteDataToFlash(uint32_t startAddress, const uint8_t *data, uint32_t dataSize) {
    if (data == NULL || dataSize == 0) {
        return false; // Nothing to write
    }

    // Unlock flash memory for writing
    if (!Flash_Unlock()) {
        return false;
    }

    // Calculate start page
    uint32_t startPage = (startAddress - FLASH_BASE_ADDR) / FLASH_PAGE_SIZE;
    
    // Erasing the pages where data will be written
    for (uint32_t pageOffset = 0; pageOffset < dataSize; pageOffset += FLASH_PAGE_SIZE) {
        if (!Flash_Erase_Page(startPage + pageOffset)) {
            Flash_Lock();
            return false; // Erase operation failed
        }
    }

    // Writing the data one word at a time
    for (uint32_t offset = 0; offset < dataSize; offset += sizeof(uint32_t)) {
        // Construct a word from the data bytes
        uint32_t wordToWrite = 0;
        for (uint32_t byteIndex = 0; byteIndex < sizeof(uint32_t) && (offset + byteIndex) < dataSize; ++byteIndex) {
            wordToWrite |= ((uint32_t)data[offset + byteIndex]) << (byteIndex * 8);
        }

        if (!Flash_Write_Word(startAddress + offset, wordToWrite)) {
            Flash_Lock();
            return false; // Write operation failed
        }
    }

    // Lock flash memory to avoid accidental writes
    if (!Flash_Lock()) {
        return false;
    }

    return true;
}

// Example implementations (pseudo-code, to be replaced with hardware-specific instructions)
bool Flash_Unlock(void) {
    // Implement the flash unlock sequence for your specific flash hardware
    return true; // Return true if the unlock sequence was successful
}

bool Flash_Lock(void) {
    // Implement the flash lock sequence for your specific flash hardware
    return true; // Return true if the lock sequence was successful
}

bool Flash_Erase_Page(uint32_t pageAddress) {
    // Implement the page erase sequence for your specific flash hardware
    return true; // Return true if the page erase was successful
}

bool Flash_Write_Word(uint32_t address, uint32_t data) {
    // Implement the word write sequence for your specific flash hardware
    return true; // Return true if the word write was successful
}
