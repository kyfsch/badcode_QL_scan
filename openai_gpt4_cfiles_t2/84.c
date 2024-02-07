#include <stdint.h>

// Define GPIO registers and their addresses.
// These will be specific to the target microcontroller and should be defined
// according to its datasheet.

#define PORT_CONFIG_REGISTER (*(volatile uint32_t*)0x50000000)
#define PORT_OUTPUT_REGISTER (*(volatile uint32_t*)0x50000004)

// Bit masks for port configuration (assuming 32-bit registers)
// These need to be defined according to the bits responsible for each port.
#define PORT_PIN_0 (1 << 0)
#define PORT_PIN_1 (1 << 1)
// ... continue for all the bits that control individual ports.

/**
 * @brief Configure the direction of a port pin.
 *
 * @param pin_mask Bitmask that selects the pin(s) to configure.
 * @param is_output Non-zero to configure as output, zero for input.
 */
void ConfigurePortPin(uint32_t pin_mask, uint8_t is_output)
{
    if (is_output)
    {
        PORT_CONFIG_REGISTER |= pin_mask; // Set selected bits to configure as output.
    }
    else
    {
        PORT_CONFIG_REGISTER &= ~pin_mask; // Clear selected bits to configure as input.
    }
}

/**
 * @brief Set the output level of a port pin.
 *
 * @param pin_mask Bitmask that selects the pin(s) to set.
 * @param level Non-zero to set high, zero to set low.
 */
void SetPortPinLevel(uint32_t pin_mask, uint8_t level)
{
    if (level)
    {
        PORT_OUTPUT_REGISTER |= pin_mask; // Set selected bits to make the pin(s) high.
    }
    else
    {
        PORT_OUTPUT_REGISTER &= ~pin_mask; // Clear selected bits to make the pin(s) low.
    }
}

// Example usage of the above functions
void Example_Setup()
{
    // Set PORT_PIN_0 as output and set its level to high.
    ConfigurePortPin(PORT_PIN_0, 1);
    SetPortPinLevel(PORT_PIN_0, 1);