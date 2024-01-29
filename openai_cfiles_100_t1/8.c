#include <stdio.h>

void insertSFPModule(int port) {
    // Check if the port is currently empty
    if (isPortEmpty(port)) {
        // Perform the necessary steps to insert the SFP module
        powerOnSFPModule(port);
        resetSFPModule(port);
        printf("SFP module has been successfully inserted into port %d.\n", port);
    } else {
        printf("Port %d is already occupied by an SFP module.\n", port);
    }
}

int isPortEmpty(int port) {
    // Check if the port is empty based on your implementation
    // This function should return 1 if the port is empty, otherwise return 0
}

void powerOnSFPModule(int port) {
    // Perform the necessary steps to power on the SFP module in the given port
}

void resetSFPModule(int port) {
    // Perform the necessary steps to reset the SFP module in the given port
}

int main() {
    int port = 1;  // Port number to insert the SFP module into

    insertSFPModule(port);

    return 0;
}
