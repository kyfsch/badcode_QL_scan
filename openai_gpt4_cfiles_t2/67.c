#include <stdint.h>

// Define the base address for the registers controlling the LED_SERIAL output
#define LED_SERIAL_BASE_ADDRESS 0x40021000

// Define the portmask register offset from the base address.
// The actual offset needs to be specified according to the hardware specification
#define LED_SERIAL_PORTMASK_OFFSET 0x04

// Write to a memory-mapped register
static void writeRegister(uint32_t address, uint32_t value)
{
    *(volatile uint32_t *)(address) = value;
}

// A function to assign the LED_SERIAL output channel to the specified portmask
void assignLedSerialOutput(uint32_t portmask)
{
    uint32_t portmaskRegisterAddress = LED_SERIAL_BASE_ADDRESS + LED_SERIAL_PORTMASK_OFFSET;
    writeRegister(portmaskRegisterAddress, portmask);
}
