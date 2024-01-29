#include <stdio.h>

void write_phy_register(unsigned int phy_addr, unsigned int reg_addr, unsigned int value) {
    // Implement the code to write the value to the PHY register here
    // ...
    // For demonstration purposes, we'll just print the values
    printf("Writing value %u to PHY register at address %u\n", value, reg_addr);
}

int main() {
    unsigned int phy_addr = 0;  // Replace 0 with the actual PHY address
    unsigned int reg_addr = 1;  // Replace 1 with the actual register address
    unsigned int value = 123;  // Replace 123 with the actual value to write

    write_phy_register(phy_addr, reg_addr, value);

    return 0;
}
