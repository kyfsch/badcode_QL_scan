#include <stdint.h>
#include <stddef.h>

// Assuming memory mapped IO access
#define RTL839X_BASE_ADDRESS 0xABCDE000   // Replace with the actual base address for the rtl839x registers
#define RTL839X_REGISTER_SIZE sizeof(uint32_t)

volatile uint32_t* const RTL839X_REGISTER_BASE = (volatile uint32_t*)RTL839X_BASE_ADDRESS;

/**
 * Writes a value to a register of the rtl839x chip.
 *
 * @param offset The offset from the base address for the register.
 * @param value The value to write to the register.
 */
void rtl839x_write_register(uint32_t offset, uint32_t value) {
    if (offset % RTL839X_REGISTER_SIZE != 0) {
        // Handle the error: offset should be aligned to the size of the register
        // This could be an assertion or another form of error handling
        return;
    }
    
    // Compute the actual pointer to the register
    volatile uint32_t* reg_address = RTL839X_REGISTER_BASE + (offset / RTL839X_REGISTER_SIZE);
    
    // Write the value to the register
    *reg_address = value;
}

// Example usage: rtl839x_write_register(0x100, 0x1); // Writes 0x1 to the register at offset 0x100


Remember to replace `RTL839X_BASE_ADDRESS` with the actual base address of the rtl839x chip registers in your specific setup. This function accesses the hardware directly, and it assumes the hardware is memory-mapped into the processor's address space, which is common for many embedded systems. If the access method for your specific system is different (e.g., through some bus communication), you will need to adjust the access mechanism accordingly.