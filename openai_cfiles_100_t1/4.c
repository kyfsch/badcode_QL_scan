#include <stdint.h>

void modify_gpio_polarity(volatile uint32_t *gpio_polarity, uint32_t polarity_mask, uint32_t reset_mask) {
    // Modify the GPIO polarity
    *gpio_polarity |= polarity_mask;
    
    // Reset the GPIO polarity
    *gpio_polarity &= ~reset_mask;
}


In this function, `gpio_polarity` is a pointer to the IGR ACL GPIO polarity register. The `polarity_mask` parameter determines which bits of the register to modify, while the `reset_mask` parameter determines which bits to reset.

To use this function, you can pass the address of the GPIO polarity register along with the desired polarity and reset masks. For example:

c
volatile uint32_t *gpio_polarity_register = (volatile uint32_t *)0x12345678;  // Replace with actual address
uint32_t polarity_mask = 0x0000000F;  // Replace with desired mask
uint32_t reset_mask = 0x00000000;    // Replace with desired mask

modify_gpio_polarity(gpio_polarity_register, polarity_mask, reset_mask);
