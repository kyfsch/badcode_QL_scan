
void write_phy_register(unsigned int phy_address, unsigned int reg, unsigned int value) {
    unsigned int command = 0;
    
    // Set the PHY address in the command
    command |= (phy_address << 11);
    
    // Set the register address in the command
    command |= (reg << 6);
    
    // Set the write command in the command
    command |= (1 << 1);
    
    // Set the value in the command
    command |= value;
    
    // Output the command to the PHY device
    // (You will need to implement the actual write to the PHY)
    write_to_phy(command);
}


In the above function:

- `phy_address` is the address of the PHY device.
- `reg` is the address of the register in the PHY device that you want to write to.
- `value` is the value to be written to the register.