
#define EEE_REG_ADDR 0x1234 // Replace with the actual address of the EEE register

// Function to read the EEE register
uint32_t readEEERegister() {
    volatile uint32_t* eeeReg = (volatile uint32_t*)EEE_REG_ADDR;
    return *eeeReg;
}

// Function to write to the EEE register
void writeEEERegister(uint32_t value) {
    volatile uint32_t* eeeReg = (volatile uint32_t*)EEE_REG_ADDR;
    *eeeReg = value;
}
