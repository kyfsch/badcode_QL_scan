#include <stdint.h>

void write_register(uint32_t reg_addr, uint32_t reg_value) {
    volatile uint32_t *reg_ptr = (volatile uint32_t *)reg_addr;
    *reg_ptr = reg_value;
}


This function takes two parameters: `reg_addr` is the address of the register you want to write to, and `reg_value` is the value you want to write to the register.

Using a `volatile` pointer ensures that the compiler will not optimize out the write operation. Casting the `reg_addr` to a `volatile uint32_t*` allows us to dereference the pointer and store the value in the register.