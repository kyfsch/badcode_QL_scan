#include <stdint.h>

void configure_PLLA(uint32_t div, uint32_t mul, uint32_t count)
{
    // Disable PLLA
    REG_PLLA_CR &= ~PLL_CR_PLLAEN;
    
    // Wait for PLLA to become unlocked
    while ((REG_PLLA_SR & PLL_SR_LOCKA) != 0);
    
    // Set PLLA divider
    REG_PLLA_MR = (REG_PLLA_MR & ~PLL_MR_DIVA_Msk) | (div << PLL_MR_DIVA_Pos);
    
    // Set PLLA multiplier
    REG_PLLA_MR = (REG_PLLA_MR & ~PLL_MR_MULA_Msk) | (mul << PLL_MR_MULA_Pos);
    
    // Set PLLA startup counter
    REG_PLLA_MR = (REG_PLLA_MR & ~PLL_MR_PLLACOUNT_Msk) | (count << PLL_MR_PLLACOUNT_Pos);
    
    // Enable PLLA
    REG_PLLA_CR |= PLL_CR_PLLAEN;
    
    // Wait for PLLA to become locked
    while ((REG_PLLA_SR & PLL_SR_LOCKA) == 0);
}


This function takes three parameters: `div`, `mul`, and `count`. The `div` parameter is used to set the PLLA divider, the `mul` parameter is used to set the PLLA multiplier, and the `count` parameter is used to set the PLLA startup counter. The function first disables the PLLA, waits for it to become unlocked, sets the PLLA divider, multiplier, and startup counter, enables the PLLA, and then waits for it to become locked again.