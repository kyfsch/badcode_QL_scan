#include <stdint.h>

// Assume these are the correct definitions for your system
#define EEPROM_BASE_ADDRESS 0x01000000 // Hypothetical base address
#define EEPROM_REGISTER_OFFSET 0x0000  // The offset for the EEE register

// Pointer to the EEE register
volatile uint32_t* const EEE_REGISTER = (volatile uint32_t*)(EEPROM_BASE_ADDRESS + EEPROM_REGISTER_OFFSET);

// Function to read the EEE register
uint32_t readEEEregister(void) {
    return *EEE_REGISTER; // Dereference the pointer to read the register
}

// Function to write to the EEE register
void writeEEEregister(uint32_t value) {
    *EEE_REGISTER = value; // Dereference the pointer to write to the register
}


In these functions, `volatile` tells the compiler that the value at the pointer's address can change at any time, without any action being taken by the code the compiler finds nearby. This prevents the compiler from optimizing away reads or writes to these registers.