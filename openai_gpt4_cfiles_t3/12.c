#include <stdbool.h>

// Define or get the port mirror state from a hardware register or configuration
// For demonstration, the state of port mirroring is stored in a variable
static bool port_mirroring_enabled = false;

// Function to enable port mirroring
void enable_port_mirroring(void) {
    port_mirroring_enabled = true;
}

// Function to disable port mirroring
void disable_port_mirroring(void) {
    port_mirroring_enabled = false;
}

// Function to check if port mirroring is enabled
int is_port_mirroring_enabled(void) {
    return port_mirroring_enabled ? 1 : 0;
}
