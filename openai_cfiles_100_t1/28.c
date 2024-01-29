
void writeDataToFlash(const uint32_t* data, uint32_t addr, size_t size) {
    // Enable flash write access by clearing the WP bit in the Flash Control Register
    FLASH->CR &= ~(FLASH_CR_WPRG);
    
    // Wait for any ongoing flash operations to complete
    while (FLASH->SR & FLASH_SR_BSY);
    
    // Enable programming of the flash memory
    FLASH->CR |= FLASH_CR_PG;
    
    // Perform word programming (32-bits) on each address location
    for (size_t i = 0; i < size; i++) {
        *(volatile uint32_t*)(addr + i * sizeof(uint32_t)) = data[i];
        
        // Wait for the programming operation to complete
        while (FLASH->SR & FLASH_SR_BSY);
        
        // Check for any write errors
        if (FLASH->SR & (FLASH_SR_PGERR | FLASH_SR_WRPERR)) {
            // Handle error (e.g., log error message, retry, etc.)
            break;
        }
    }
    
    // Disable programming of the flash memory
    FLASH->CR &= ~(FLASH_CR_PG);
    
    // Lock flash write access by setting the WP bit in the Flash Control Register
    FLASH->CR |= FLASH_CR_WPRG;
}


In this function, we first clear the Write Protection (WP) bit in the Flash Control Register to enable flash write access. We then wait for any ongoing flash operations to complete by checking the Busy (BSY) flag in the Status Register.

Next, we enable programming of the flash memory by setting the Program (PG) bit in the Flash Control Register. We use a loop to perform word programming on each address location, using a pointer to access the memory location and assigning the data. After each programming operation, we wait for it to complete and check for any write errors (e.g., programming error or write protection error) in the Status Register.