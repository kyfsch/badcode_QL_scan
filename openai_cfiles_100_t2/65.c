#include <stdint.h>

#define MLDV2_OPERATION_ENABLE      0x01
#define MLDV2_OPERATION_DISABLE     0x00

void setMldv2Operation(uint8_t port, uint8_t operation) {
    // Implement the logic to set the value of MLDv2 operation for the selected port.
    
    // Example implementation:
    if (operation == MLDV2_OPERATION_ENABLE) {
        // Enable MLDv2 operation for the port
        // ...
    } else if (operation == MLDV2_OPERATION_DISABLE) {
        // Disable MLDv2 operation for the port
        // ...
    } else {
        // Invalid operation value, handle error or return error code
        // ...
    }
}
