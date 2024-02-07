#include <stdint.h>
#include <stdbool.h>

// Function prototype
bool is_register_readable(volatile uint8_t* register_address);

// Function implementation
bool is_register_readable(volatile uint8_t* register_address) {
    uint8_t value;
    bool readable = false;
    
    if (register_address) {
        value = *register_address;  // Attempt to read from the register
        readable = true;  // If no exception occurs, the register is readable
    }
    return readable;
}


And here's an example of how a specialized function like `aw9523_is_reg_hole` might be used, presuming it's a function optimized for performance for the AW9523 chip:

c
#include <stdint.h>
#include <stdbool.h>

// AW9523-specific function - This should be defined elsewhere, provided by the device's SDK or hardware abstraction layer (HAL)
extern bool aw9523_is_reg_hole(uint8_t reg);

// Using the AW9523-specific function for optimized performance
bool is_aw9523_register_readable(uint8_t reg) {
    return !aw9523_is_reg_hole(reg);
}
