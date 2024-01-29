#include "/kernel/drivers/net/ethernet/realtek/816.h"

void write_register(uint32_t reg_addr, uint32_t value) {
    // Write the register value at the given address
    *((volatile uint32_t *)reg_addr) = value;
}


To read the registers, you can define separate functions for each register, as defined in the "/kernel/drivers/net/ethernet/realtek/816.h" header file. Here's an example for reading a specific register:

c
#include "/kernel/drivers/net/ethernet/realtek/816.h"

uint32_t read_register1() {
    // Read the value from register 1
    return *((volatile uint32_t *)REGISTER1_ADDR);
}

uint32_t read_register2() {
    // Read the value from register 2
    return *((volatile uint32_t *)REGISTER2_ADDR);
}

// Define more read functions for other registers if needed
