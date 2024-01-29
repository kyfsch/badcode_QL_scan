#include <stdint.h>

// Register addresses
#define RTL8367C_REG_0 0x00
#define RTL8367C_REG_1 0x01
#define RTL8367C_REG_2 0x02
// ... add more register definitions here ...

// Function to set a bit in an 8367C register
void set_bit(uint8_t register_num, uint8_t bit_num, uint8_t value) {
    uint8_t reg_value;
    
    // Read the current value of the register
    switch (register_num) {
        case 0:
            reg_value = RTL8367C_REG_0;
            break;
        case 1:
            reg_value = RTL8367C_REG_1;
            break;
        case 2:
            reg_value = RTL8367C_REG_2;
            break;
        // ... add more cases for other register numbers here ...
        default:
            // Invalid register number, handle error
            return;
    }

    // Set or clear the specified bit based on the desired value
    if (value) {
        reg_value |= (1 << bit_num);
    } else {
        reg_value &= ~(1 << bit_num);
    }

    // Write the updated value back to the register
    switch (register_num) {
        case 0:
            RTL8367C_REG_0 = reg_value;
            break;
        case 1:
            RTL8367C_REG_1 = reg_value;
            break;
        case 2:
            RTL8367C_REG_2 = reg_value;
            break;
        // ... add more cases for other register numbers here ...
        default:
            // Invalid register number, handle error
            return;
    }
}

// Function to get the value of a bit in an 8367C register
uint8_t get_bit(uint8_t register_num, uint8_t bit_num) {
    uint8_t reg_value;
    
    // Read the current value of the register
    switch (register_num) {
        case 0:
            reg_value = RTL8367C_REG_0;
            break;
        case 1:
            reg_value = RTL8367C_REG_1;
            break;
        case 2:
            reg_value = RTL8367C_REG_2;
            break;
        // ... add more cases for other register numbers here ...
        default:
            // Invalid register number, handle error
            return 0;
    }

    // Get the value of the specified bit
    return (reg_value >> bit_num) & 0x01;
}
