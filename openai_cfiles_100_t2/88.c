
void write_phy_register(uint8_t reg_address, uint16_t value) {
    // Select the PHY register address
    // Write the register address to the MII address register
    MII_ADDRESS_REG = reg_address;
    
    // Write the value to the MII data register
    MII_DATA_REG = value;
    
    // Start the write operation by setting the write enable bit
    MII_CONTROL_REG = (1 << MII_CONTROL_WRITE_ENABLE);
    
    // Wait for the write operation to complete
    while (MII_CONTROL_REG & (1 << MII_CONTROL_WRITE_ENABLE)) {
        // Continue polling until the write operation is complete
    }
}
