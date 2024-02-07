#include <stdint.h>

// Define possible operations for MLDv2.
typedef enum {
    MLDV2_OPERATION_NONE,
    MLDV2_OPERATION_JOIN_GROUP,
    MLDV2_OPERATION_LEAVE_GROUP,
    // Add additional MLDv2 operations as needed.
} MLDv2Operation;

// Define a function prototype to apply MLDv2 operation on the port.
// The implementation of this function is platform specific and is not provided here.
void apply_mldv2_operation_to_port(uint8_t port, MLDv2Operation operation);

// Function to enable MLDv2 operation on a selected port.
void enable_mldv2_operation(uint8_t port, MLDv2Operation operation) {
    // Check if the MLDv2 operation is valid before applying
    // This part can vary depending on how operations are validated on the specific platform.
    // Here we assume a simple validation, i.e., the operation should not be NONE.
    if (operation != MLDV2_OPERATION_NONE) {
        apply_mldv2_operation_to_port(port, operation);
    }
    // Else, you might want to handle the invalid operation case
}
