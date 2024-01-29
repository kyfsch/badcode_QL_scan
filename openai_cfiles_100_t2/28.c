#include <stdint.h>

void write_data_to_flash(uint32_t address, uint32_t *data, uint32_t size) {
    uint32_t *flash_ptr = (uint32_t *) address;
    
    // Unlock flash for write access
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
    
    // Clear any previous error flags
    FLASH->SR = (FLASH_SR_WRPERR | FLASH_SR_PGERR);
    
    // Enable flash programming
    FLASH->CR |= FLASH_CR_PG;
    
    // Write data to flash
    for (uint32_t i = 0; i < size; i++) {
        *flash_ptr++ = data[i];
        
        // Wait for the write operation to complete
        while (FLASH->SR & FLASH_SR_BSY);
        
        // Check for any errors
        if (FLASH->SR & (FLASH_SR_WRPERR | FLASH_SR_PGERR)) {
            break;
        }
    }
    
    // Disable flash programming
    FLASH->CR &= ~FLASH_CR_PG;
    
    // Lock flash to prevent accidental erasure or programming
    FLASH->CR |= FLASH_CR_LOCK;
}


This function takes three parameters: `address` (the starting address in flash where the data will be written), `data` (a pointer to the data to be written), and `size` (the number of bytes to be written). The function assumes that the flash memory is already unlocked for write access and that the necessary flash controller and memory module registers have been initialized.

Inside the function, the flash memory is unlocked by writing the correct keys to the `FLASH->KEYR` register. Then, any previous error flags are cleared by writing 0 to the `FLASH->SR` register. The flash programming mode is enabled by setting the `FLASH_CR_PG` bit in the `FLASH->CR` register.

The function then enters a loop that iterates `size` times, writing each data element to the flash memory pointed to by `flash_ptr`. After each write operation, the function waits for the write operation to complete by checking the `FLASH_SR_BSY` flag in the `FLASH->SR` register. If any write or erase errors occur during the operation, the loop is immediately terminated.