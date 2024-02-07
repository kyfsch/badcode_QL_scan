#include <stdint.h>

// Assuming that you have defined functions to read and write to the device registers
extern void writeRegister(uint8_t reg, uint16_t value);
extern uint16_t readRegister(uint8_t reg);

// Define the register address and bitmask constants for LEQ-offset
#define REG_LEQ_OFFSET 0x2E
#define BIT9_MASK 0x0200
#define BIT10_MASK 0x0400

/**
 * Function to set the LEQ-offset manually.
 * 
 * @param offset Value of the offset to set (only bit9 and bit10 are considered).
 */
void setLEQOffset(uint16_t offset) {
    // Read the current value of the register
    uint16_t regValue = readRegister(REG_LEQ_OFFSET);

    // Clear bit9 and bit10 in the register
    regValue &= ~(BIT9_MASK | BIT10_MASK);

    // Set bit9 and bit10 based on the offset value
    regValue |= (offset & (BIT9_MASK | BIT10_MASK));