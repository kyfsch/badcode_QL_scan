#include <stdint.h>

// Mock memory-mapped control register address
#define SYSTEM_CONTROL_REGISTER_ADDR 0x4000F000

// Bit position for power down mode in the control register
#define POWER_DOWN_MODE_BIT 0

// Define the control register as a pointer to a volatile uint32_t
#define SYSTEM_CONTROL_REGISTER ((volatile uint32_t *)SYSTEM_CONTROL_REGISTER_ADDR)

// Function to set the system into power down mode
void setPowerDownMode(void)
{
    // Set the power down mode bit in the control register
    *SYSTEM_CONTROL_REGISTER |= (1 << POWER_DOWN_MODE_BIT);
}


You should replace `SYSTEM_CONTROL_REGISTER_ADDR` and `POWER_DOWN_MODE_BIT` with the actual hardware-specific address and bit position for your embedded system.