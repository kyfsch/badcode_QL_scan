
void write_nand_command(volatile unsigned int *gpio_base, unsigned int command) {
    // Write command to NAND command register (e.g., GPIO Pin 1)
    *gpio_base = (command << 1); // Assuming GPIO Pin 1 is used for Nand command register
    
    // Set control lines (e.g., GPIO Pin 2) to appropriate levels
    *gpio_base |= (1 << 2); // Assuming GPIO Pin 2 is used for control lines
}
