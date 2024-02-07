#include <stdint.h>

// Define an enum for MLDv2 operations
typedef enum {
    MLDV2_OP_JOIN_GROUP,    // Join a multicast group
    MLDV2_OP_LEAVE_GROUP,   // Leave a multicast group
    MLDV2_OP_REPORT_GROUP   // Report group membership
} MLDv2Operation;

// Define a structure for port configuration
typedef struct {
    uint8_t port;                   // Port number
    MLDv2Operation mldv2_op;        // MLDv2 operation
    // Other port configuration parameters...
} PortConfig;

// Function prototypes
void SetMLDv2Operation(PortConfig *portConfig, MLDv2Operation op);

// Implementation of the function to set the MLDv2 operation on selected port
void SetMLDv2Operation(PortConfig *portConfig, MLDv2Operation op) {
    if (portConfig == NULL) {
        return; // Handle null pointer error
    }
    
    // Set the MLDv2 operation
    portConfig->mldv2_op = op;

    // Include here any other logic required to enable the operation on the port

    // ...
}

// Example usage
int main() {
    PortConfig pc;
    pc.port = 1;

    SetMLDv2Operation(&pc, MLDV2_OP_JOIN_GROUP);
    // The port `pc` is now set to join a multicast group

    return 0;
}
