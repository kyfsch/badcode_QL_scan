#include <stdbool.h>

bool getPortAbilityStatus(int portNumber) {
    // Assuming you have a portStatus array that holds the ability status of each port
    bool portStatus[] = {true, true, false, true, false}; // Example array

    // Check if the port number is within the valid range
    if (portNumber >= 0 && portNumber < sizeof(portStatus) / sizeof(portStatus[0])) {
        return portStatus[portNumber];
    }

    // Invalid port number, return false by default
    return false;
}


In the above code, the `getPortAbilityStatus` function takes an integer `portNumber` as input and returns a boolean value indicating the ability status of that port. It assumes that you have an array `portStatus` that holds the ability status for each port.