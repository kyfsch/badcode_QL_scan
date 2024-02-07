#include <stdint.h>
#include <stdbool.h>

/* Assuming the RTL8367C_REG_xxx are defined somewhere as this: */
/* #define RTL8367C_REG_xxx (specific register address) */

/* Base address for the RTL8367C registers - replace with actual address */
#define RTL8367C_REGS_BASE_ADDR 0x00000000

/* Functions to read from / write to the RTL8367C register */
uint16_t read_rtl8367c_register(uint16_t reg_num);
void write_rtl8367c_register(uint16_t reg_num, uint16_t value);

/* Set a specific bit in the register */
void setBit(uint16_t reg_num, uint8_t bit_num) {
    uint16_t reg_value = read_rtl8367c_register(reg_num);
    reg_value |= (1 << bit_num);
    write_rtl8367c_register(reg_num, reg_value);
}

/* Clear a specific bit in the register */
void clearBit(uint16_t reg_num, uint8_t bit_num) {
    uint16_t reg_value = read_rtl8367c_register(reg_num);
    reg_value &= ~(1 << bit_num);
    write_rtl8367c_register(reg_num, reg_value);
}

/* Get the status of a specific bit in the register */
bool getBit(uint16_t reg_num, uint8_t bit_num) {
    uint16_t reg_value = read_rtl8367c_register(reg_num);
    return (reg_value & (1 << bit_num)) != 0;
}

/* These are placeholders for actual read/write implementations, which would
 * interact with the hardware. You must replace these with appropriate
 * hardware access code specific to your system.
 */
uint16_t read_rtl8367c_register(uint16_t reg_num) {
    // Placeholder: Insert actual register read code here
    return *((volatile uint16_t *)(RTL8367C_REGS_BASE_ADDR + reg_num));
}

void write_rtl8367c_register(uint16_t reg_num, uint16_t value) {
    // Placeholder: Insert actual register write code here
    *((volatile uint16_t *)(RTL8367C_REGS_BASE_ADDR + reg_num)) = value;
}


Some notes on the code: