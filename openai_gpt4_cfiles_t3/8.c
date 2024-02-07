#include <stdbool.h>

// Define constants and types for the SFP module and port.
#define SFP_MODULE_INSERTED_SUCCESSFULLY 0
#define SFP_MODULE_INSERT_ERROR -1

typedef enum {
    PORT_EMPTY,
    PORT_OCCUPIED
} PortStatus;

typedef struct {
    PortStatus status;
    // Other properties can be defined here
} SfpPort;

// Function to insert an SFP module into the port.
int insertSfpModule(SfpPort *port) {
    if (port == NULL) {
        // Port pointer is not valid
        return SFP_MODULE_INSERT_ERROR;
    }

    if (port->status == PORT_OCCUPIED) {
        // The port is already occupied
        return SFP_MODULE_INSERT_ERROR;
    }

    // Simulate inserting the SFP module.
    port->status = PORT_OCCUPIED;

    // If there are additional steps required to activate or initialize the SFP module,
    // they would be performed here.

    return SFP_MODULE_INSERTED_SUCCESSFULLY;
}

// Example usage:
// SfpPort port = {PORT_EMPTY};
// int result = insertSfpModule(&port);
// if (result == SFP_MODULE_INSERTED_SUCCESSFULLY) {
//     // Handle successful insertion
// } else {
//     // Handle insertion error
// }


This code defines a `PortStatus` enum to represent whether a port is empty or occupied, and a `SfpPort` struct to encapsulate the state of an SFP port. The `insertSfpModule` function checks whether the provided port is NULL or already occupied before simulating the insertion of an SFP module.