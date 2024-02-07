#include <stdint.h>

// Assuming these are the predefined base addresses for the registers
// These values should be defined according to your specific hardware
#define GPIO_BASE_ADDR         0x12340000
#define IGR_ACL_POLARITY_REG   (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x10)) // Replace with the correct offset

// Define the bit position for GPIO POLARITY within the register, if it's a single bit
#define GPIO_POLARITY_BIT      (1U << 5) // Replace 5 with the correct bit position

// Function prototype for system reset of GPIO POLARITY
void SystemResetIGRACLGPIOPolarity(void);

// Function to modify IGR ACL GPIO POLARITY by user
void ModifyIGRACLGPIOPolarity(uint8_t polarity)
{
    uint32_t reg_value = IGR_ACL_POLARITY_REG;
    
    if (polarity)
    {
        // Set the polarity bit
        reg_value |= GPIO_POLARITY_BIT;
    }
    else
    {
        // Clear the polarity bit
        reg_value &= ~GPIO_POLARITY_BIT;
    }
    
    // Write back the modified value to the register
    IGR_ACL_POLARITY_REG = reg_value;
}

// Function to reset IGR ACL GPIO POLARITY by system to a default state (Assuming reset state is 0)
void SystemResetIGRACLGPIOPolarity(void)
{
    // Clear the polarity bit
    IGR_ACL_POLARITY_REG &= ~GPIO_POLARITY_BIT;
}

// Make sure to use the actual hardware constants provided by the hardware manufacturer for the addresses and bit masks.


This code sample provides two functions:

1. `ModifyIGRACLGPIOPolarity` - This function takes a `uint8_t` polarity argument, which the caller should provide based on the desired new state for the GPIO Polarity bit (often 1 or 0 for high or low polarity). The function reads the current register value, modifies the relevant bit, and writes it back.

2. `SystemResetIGRACLGPIOPolarity` - This system function resets the polarity to a default state, which is assumed to be 0 (cleared) in this example.