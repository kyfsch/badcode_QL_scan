#include <stdbool.h>
#include <stdio.h>

// Definitions
#define MAX_PORTS 8
#define SUCCESS 0
#define ERROR_PORT_BUSY -1
#define ERROR_PORT_OUT_OF_RANGE -2

// Port status representation (for simplification)
bool portStatus[MAX_PORTS] = {false}; // false indicates port is free, true indicates port is in use.

/**
 * Attempts to insert an SFP module into a specified port.
 * Returns an integer indicating the result of the operation.
 *
 * @param portNumber The port number into which the SFP module is to be inserted.
 * @return SUCCESS if the module is successfully inserted,
 *         ERROR_PORT_BUSY if the port is already in use,
 *         ERROR_PORT_OUT_OF_RANGE if the portNumber is out of valid range.
 */
int insertSFPModule(int portNumber) {
    // Check if portNumber is within valid range
    if (portNumber < 0 || portNumber >= MAX_PORTS) {
        return ERROR_PORT_OUT_OF_RANGE;
    }

    // Check if the specified port is already in use
    if (portStatus[portNumber]) {
        return ERROR_PORT_BUSY;
    }
    
    // Insert the SFP module (placeholder for the actual hardware interaction code)
    // Actual Hardware code to interface with would go here
    // For e.g., setting the correct bits in a hardware register to power up and initialize the port.
    // ...

    // Update port status
    portStatus[portNumber] = true;

    // Return success
    return SUCCESS;
}

// Example usage
int main() {
    int portNumber = 3; // Example port to insert SFP module into
    int result = insertSFPModule(portNumber);

    if (result == SUCCESS) {
        printf("SFP module inserted successfully into port %d.\n", portNumber);
    } else if (result == ERROR_PORT_BUSY) {
        printf("Error: Port %d is already in use.\n", portNumber);
    } else if (result == ERROR_PORT_OUT_OF_RANGE) {
        printf("Error: Port %d is out of range. Please select a port from 0 to %d.\n", portNumber, MAX_PORTS - 1);
    }

    return 0;
}
