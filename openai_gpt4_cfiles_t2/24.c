#include <stdint.h>

// Placeholder definitions for control registers
// Replace these with actual register definitions for your specific hardware.
#define PLLA_CONTROL_REGISTER (*(volatile uint32_t*)0x40008010)
#define PLLA_ENABLE_BIT       (1 << 0)  // Bit to enable PLLA
#define PLLA_CONFIG_BITMASK   (0x0000FF00) // Bitmask for the configuration bits
#define PLLA_LOCK_BIT         (1 << 16) // Bit indicating PLLA lock status

// Function to change PLLA configuration
// config_value should be the value you wish to set in the configuration bitmask section
void changePllaConfiguration(uint32_t config_value)
{
    // Mask out the configuration bits
    uint32_t current_value = PLLA_CONTROL_REGISTER & ~PLLA_CONFIG_BITMASK;
    
    // Set the new configuration value
    current_value |= (config_value << 8) & PLLA_CONFIG_BITMASK;
    
    // Apply the new configuration
    PLLA_CONTROL_REGISTER = current_value;
    
    // Enable PLLA (if this is required by hardware after changing configuration)
    PLLA_CONTROL_REGISTER |= PLLA_ENABLE_BIT;
    
    // Wait for PLLA to lock (if applicable)
    while(!(PLLA_CONTROL_REGISTER & PLLA_LOCK_BIT)) {
        // Wait loop or possibly insert a timeout mechanism here
    }
}

// Example usage
// Set PLLA configuration to a specific configuration value (assuming 8-bit configuration)
void configurePllaExample()
{
    uint32_t new_config_value = 0x5A; // Example configuration value; should be replaced by actual configuration
    changePllaConfiguration(new_config_value);
}
