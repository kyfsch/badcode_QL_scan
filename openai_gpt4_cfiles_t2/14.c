#include <stdint.h>
#include <stddef.h>

// Assuming the function signature for rtl9300_i2c_write is as follows:
// int rtl9300_i2c_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t *data, size_t len);

// Function declaration for rtl9300_i2c_write (assumed to be implemented elsewhere)
int rtl9300_i2c_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t *data, size_t len);

// Encapsulation function for calling rtl9300_i2c_write
int encapsulated_i2c_write(uint8_t device_addr, uint8_t reg_addr, const uint8_t *data, size_t len) {
    // Perform any necessary setup before calling rtl9300_i2c_write, if required

    // Direct call to rtl9300_i2c_write function
    int result = rtl9300_i2c_write(device_addr, reg_addr, data, len);

    // Perform any necessary teardown after calling rtl9300_i2c_write, if required

    // Return the result of the write operation
    return result;
}
