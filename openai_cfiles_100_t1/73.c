#include <stdint.h>

// Define the address of the LEDs status register
#define LEDS_STATUS_REGISTER 0x1234

// Function to read the LEDs status
uint16_t readLEDsStatus()
{
    // Read the value from the LEDs status register
    uint16_t status = *((volatile uint16_t*)LEDS_STATUS_REGISTER);
    
    return status;
}
