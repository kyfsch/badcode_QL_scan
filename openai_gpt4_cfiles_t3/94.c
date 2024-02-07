#include <stdint.h>
#include <stdbool.h>

// Define constants for IDE device initialization as needed
#define IDE_CONTROL_REGISTER_BASE 0x3F6
#define IDE_STATUS_REGISTER_BASE  0x1F7
#define IDE_COMMAND_REGISTER_BASE 0x1F7
#define IDE_DATA_REGISTER_BASE    0x1F0

#define IDE_CONTROL_RESET         0x04
#define IDE_CONTROL_NIEN          0x02

#define IDE_COMMAND_IDENTIFY      0xEC
#define IDE_STATUS_BUSY           0x80
#define IDE_STATUS_DRQ            0x08

// IO operation function declarations (stub versions)
void outb(uint16_t port, uint8_t val); // Stub for writing a byte to a port
uint8_t inb(uint16_t port);            // Stub for reading a byte from a port

// Delay function that should be implemented according to the platform specifics
void delay_400ns() {
    // Platform-specific delay to wait for at least 400 nanoseconds
    // Implement this according to the embedded system's requirements
}

// Function to check if the IDE device is ready to accept commands
bool ide_device_ready() {
    // Read status until the BSY bit is clear
    while (inb(IDE_STATUS_REGISTER_BASE) & IDE_STATUS_BUSY) {
        delay_400ns();
    }
    
    // Check if the DRQ bit is set
    return inb(IDE_STATUS_REGISTER_BASE) & IDE_STATUS_DRQ;
}