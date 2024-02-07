#include <stdint.h>
#include <stdbool.h>

// You should define these constants according to your system requirements.
#define IDE_CONTROL_PORT 0x3F6
#define IDE_STATUS_PORT 0x1F7
#define IDE_DATA_PORT 0x1F0
#define IDE_STATUS_READY 0x40
#define IDE_STATUS_ERROR 0x01

// Define function prototypes for system-specific I/O operations
void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

// External variable indicating if the device was initialized
volatile bool ide_device_initialized = false;

// Function to initialize the IDE block device
void init_ide_device(void) {
    uint8_t status;
    
    // Signal that the IDE device initialization starts
    // Insert diagnostics or logging here if necessary
    
    // Reset the device
    outb(IDE_CONTROL_PORT, 0x04);
    outb(IDE_CONTROL_PORT, 0x00);
    
    // Wait for the device to become ready
    do {
        status = inb(IDE_STATUS_PORT);
    } while ((status & IDE_STATUS_READY) == 0);
    
    // Check if the device reported an error
    if (status & IDE_STATUS_ERROR) {
        // Report error: the device could not be initialized
        // Insert diagnostics or logging here if necessary
        return;
    }
    
    // The device is ready for use
    ide_device_initialized = true;
    
    // Signal that the IDE device was successfully initialized
    // Insert diagnostics or logging here if necessary
}

// Example usage in your embedded system's initialization code
int main(void) {
    init_ide_device();
    // Check if the device was initialized successfully
    if (ide_device_initialized) {
        // Proceed with the rest of your system's initialization
    } else {
        // Handle the error when device initialization fails
    }

    // ...rest of the main function...

    return 0;
}
