#include <stdint.h>
#include <stdbool.h>

// I2C address for AW9523, needs to be defined according to your setup (check datasheet)
#define AW9523_I2C_ADDRESS 0x58

// Define the registers of the AW9523 that are writable
#define AW9523_REG_WRITABLE_1 0x10 // Replace with actual writable register address
// Add definitions for other writable registers if necessary

// Fake function signatures for I2C read/write, replace with actual functions of your platform
bool i2c_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t *data, size_t length);
bool i2c_read(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, size_t length);

// Write data to a register in the AW9523
bool aw9523_write_register(uint8_t reg, uint8_t data) {
    // Assuming a register is writable if it is declared in the AW9523 datasheet as such.
    // You might need more sophisticated checking based on your requirements.
    switch (reg) {
        case AW9523_REG_WRITABLE_1:
            // Add cases for other writable registers if necessary
            // case AW9523_REG_WRITABLE_2:
            // case AW9523_REG_WRITABLE_3:
            // ...
            return i2c_write(AW9523_I2C_ADDRESS, reg, &data, 1);
        default:
            // Register is not writable
            return false;
    }
}


This code is hypothetical and likely needs adapting to the actual I2C library you're using and the AW9523's register definitions. You would also need to add all the writable registers that you are planning to access.

Make sure to replace the placeholders with actual register addresses from the AW9523 datasheet and replace the `i2c_write()` and `i2c_read()` with the specific functions provided by your platform's I2C library.