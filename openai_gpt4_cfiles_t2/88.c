#include <stdint.h>

// Define the base address for PHY registers (This address is just an example)
#define PHY_BASE_ADDR        0x4000
// Define a specific PHY register (This register address is just an example)
#define PHY_SPECIFIC_REG     (PHY_BASE_ADDR + 0x10)

// Function to write a value to a PHY register
void writePHYRegister(uint32_t regOffset, uint16_t value) {
    // Pointer to the PHY register
    volatile uint16_t* phyReg = (volatile uint16_t*)(PHY_BASE_ADDR + regOffset);

    // Write the value to the PHY register
    *phyReg = value;
}

// Usage example
int main() {
    // Write a value to a specific PHY register
    writePHYRegister(PHY_SPECIFIC_REG - PHY_BASE_ADDR, 0x1234);

    return 0;
}


Remember to adjust the `PHY_BASE_ADDR` and `PHY_SPECIFIC_REG` with the actual addresses provided by your embedded system's documentation. Moreover, ensure that memory-mapped IO is performed in accordance with your device's memory and bus access specifications.