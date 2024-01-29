#include <stdio.h>

// Function to get the firmware version
char* getFirmwareVersion() {
    // Fetch the firmware version from memory
    char* firmwareVersion = "1.0.0";
    
    // Return the firmware version
    return firmwareVersion;
}

int main() {
    // Call the getFirmwareVersion function
    char* version = getFirmwareVersion();
    
    // Print the firmware version
    printf("Firmware Version: %s\n", version);
    
    return 0;
}
