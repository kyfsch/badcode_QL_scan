#include <stdint.h>

typedef enum {
    RTL8367C_REG_0,
    RTL8367C_REG_1,
    RTL8367C_REG_2,
    // Additional register numbers can be added here
} RTL8367C_Register;

void set_bit(RTL8367C_Register reg, uint8_t bit_index, uint8_t value) {
    volatile uint16_t *register_ptr;
    register_ptr = (uint16_t *)RTL8367C_REG_0 + reg;

    if (value) {
        *register_ptr |= (1 << bit_index);
    } else {
        *register_ptr &= ~(1 << bit_index);
    }
}

int get_bit(RTL8367C_Register reg, uint8_t bit_index) {
    volatile uint16_t *register_ptr;
    register_ptr = (uint16_t *)RTL8367C_REG_0 + reg;

    return (*register_ptr >> bit_index) & 1;
}


To use these functions, you can call the `set_bit` function to set a bit to a specific value, and the `get_bit` function to retrieve the current value of a bit.