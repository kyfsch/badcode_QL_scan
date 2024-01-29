#include <stdint.h>

void sendToCPLD(uint8_t data)
{
    // Your code to send the data to the CPLD goes here
    // For example, you could use an SPI interface or a parallel bus
    
    // Assuming you are using an SPI interface:
    // Clear any previous data in the SPI transmit buffer
    // before sending the new data
    while (SPI0_SR & (1 << 1)) {}
    
    // Send the data to the CPLD via SPI
    SPI0_DR = data;
    
    // Wait until the SPI transmission is complete
    while (!(SPI0_SR & (1 << 7))) {}
}
