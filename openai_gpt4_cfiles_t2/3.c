#include <stdint.h>

// Variables or defines that could be specific to your hardware
#define PHY_BASE_ADDR 0x0000    // Base address for the PHY registers (Change as necessary)
#define PHY_WRITE_CMD 0x1       // Command to write to the PHY (Change as necessary)

// Replace `hardware_write_function` with your actual hardware write function
// This is a placeholder for whatever function sends the write command to the PHY
void hardware_write_function(uint32_t address, uint32_t value);

// Function to write a value to a PHY register
void PHY_WriteRegister(uint8_t phy_addr, uint8_t reg, uint16_t value) {
    uint32_t address = PHY_BASE_ADDR + (phy_addr << 5) + reg;
    uint32_t write_command = (PHY_WRITE_CMD << 16) | value;
    
    hardware_write_function(address, write_command);
}

The function `hardware_write_function` is a placeholder for the actual function call that performs the register write operation. This could involve setting up a write transaction on a bus, such as I2C or SPI, or writing to a memory-mapped register, depending on the microcontroller or processor used and how the PHY is interfaced. Make sure you replace it with the correct function provided by your hardware's SDK or HAL.

The exact implementation details will also depend on the protocol used to communicate with the PHY (MDIO, SPI, etc.), the register layout of the PHY, and the requirements of the system in terms of setting up and confirming the completion of write operations.