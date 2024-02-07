#include <stdint.h>

#define PORT_ABILITY_STATUS_REG 0x40001000U // Example address for the port ability status register.
                                            // This should be set based on your hardware's specifics.

uint32_t read_register(uint32_t address); // Forward declaration of the function to read a register.

/**
 * Get the ability status of a single port.
 *
 * @return The ability status of the port as an unsigned 32-bit integer.
 */
uint32_t get_port_ability_status(void) {
    return read_register(PORT_ABILITY_STATUS_REG);
}
