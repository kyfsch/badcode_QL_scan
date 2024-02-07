#include <stdint.h>

// Define the base address for the SM interface registers if not defined
#ifndef SM_BASE_ADDR
#define SM_BASE_ADDR 0x40000000U // Example base address; update with actual address
#endif

// Define the specific offset if needed
#ifndef SM_DATA_REG_OFFSET
#define SM_DATA_REG_OFFSET 0x00U // Data register offset; update with actual offset
#endif

// Define the bit mask for the SM data register
#ifndef SM_DATA_REG_MASK
#define SM_DATA_REG_MASK 0xFFU // Mask for the SM data register; update with actual mask
#endif

// Assuming a simple memory mapped interface for example purposes
#define SM_DATA_REG (*((volatile uint32_t *)(SM_BASE_ADDR + SM_DATA_REG_OFFSET)))

/**
 * Writes a bit to a specific location on the SM interface.
 *
 * @param bit_value The bit value to write (0 or 1).
 * @param bit_position The bit position to write to [0-7].
 */
void SM_WriteBit(uint8_t bit_value, uint8_t bit_position)
{
    if(bit_position > 7) {
        return; // Invalid bit_position, exit the function
    }

    uint32_t reg_value = SM_DATA_REG; // Read current register value

    // Update the register value with the new bit value
    if(bit_value) {
        reg_value |= (1U << bit_position); // Set the bit at bit_position
    } else {
        reg_value &= ~(1U << bit_position); // Clear the bit at bit_position
    }

    SM_DATA_REG = reg_value; // Write updated value back to the data register
}
