
void write_register(uint8_t phy_addr, uint8_t reg_addr, uint16_t value) {
    // Generate the write command
    uint16_t command = (phy_addr << 8) | (reg_addr & 0x1F); // bit 15:11 = PHY address, bit 4:0 = register address

    // Write the value to the register
    *(volatile uint16_t*)command = value;
}


In this function, the parameters `phy_addr`, `reg_addr`, and `value` represent the PHY address, register address, and value to be written to the register, respectively.

The function generates a command by left-shifting the `phy_addr` by 8 bits and bitwise ORing it with the lower 5 bits of the `reg_addr`. This command is then used as the address to write the `value` to. Note that the cast `(volatile uint16_t*)` is used to dereference and write to the address as a `volatile` 16-bit integer, ensuring that the write operation is not optimized away by the compiler.