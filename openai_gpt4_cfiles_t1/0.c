#include <stdint.h>
#include <stdbool.h>

// Example register hole definitions for illustration
#define REG_BASE_ADDR       0x00
#define REG_HOLE_START      0x10
#define REG_HOLE_END        0x20
#define REG_MAX_ADDR        0xFF

// Your assignable constants for your specific use case.
// These should be replaced with the actual values for your hardware.
const uint8_t readable_register_start = REG_BASE_ADDR;
const uint8_t readable_register_end = REG_MAX_ADDR;
const uint8_t non_readable_register_start = REG_HOLE_START;
const uint8_t non_readable_register_end = REG_HOLE_END;

// Prototype for aw9523_is_reg_hole if it exists and if you're supposed to use it
bool aw9523_is_reg_hole(uint8_t reg);

// Function to determine if a register is readable or not
bool is_register_readable(uint8_t reg) {
    if (aw9523_is_reg_hole) {
        // Use the existing function if it's suitable and faster.
        return !aw9523_is_reg_hole(reg);
    } else {
        // Check for readability manually if aw9523_is_reg_hole isn't available or suitable
        if (reg >= readable_register_start && reg <= readable_register_end) {
            if (reg >= non_readable_register_start && reg <= non_readable_register_end) {
                return false; // Register is in the non-readable "hole"
            }
            return true; // Register is not in the non-readable "hole"
        }
        return false; // Register is outside the readable range
    }
}


In the above code snippet, replace `REG_BASE_ADDR`, `REG_HOLE_START`, `REG_HOLE_END`, and `REG_MAX_ADDR` with the actual start and end addresses of the readable registers and the hole (non-readable region) for your specific hardware.