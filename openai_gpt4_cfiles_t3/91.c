#include <stdbool.h>  // For using bool type
#include <stdint.h>   // For specific integer type definitions

// Assuming RTK_WHOLE_SYSTEM and DSCP_REMARK_ENABLE_API are defined in the system's API.
#define RTK_WHOLE_SYSTEM 0xFFFF
#define DSCP_REMARK_ENABLE_API 0x1234 // Hypothetical value for API to get DSCP Remark status.

// Mocked result and error codes
#define RTK_SUCCESS 0
#define RTK_FAIL -1

// Function prototype for the hypothetical API provided by the system to get DSCP Remark status.
// This is a placeholder and doesn't represent a real API.
int getDscpRemarkStatus(uint16_t port, bool *status);

// Function to get the whole system's DSCP Remark enable status.
bool getSystemDscpRemarkEnableStatus(void) {
    bool enableStatus = false;
    int result;

    result = getDscpRemarkStatus(RTK_WHOLE_SYSTEM, &enableStatus);
    if (result != RTK_SUCCESS) {
        // Handle error, possibly set enableStatus to a known safe value or retrieve a cached value.
    }
    
    return enableStatus;
}

// Mock implementation for getDscpRemarkStatus to work in absence of real API.
// This function needs to be replaced with the actual system call that retrieves the DSCP Remark enable status.
int getDscpRemarkStatus(uint16_t port, bool *status) {
    // Here we'll just return a fixed value for demo purposes.
    // You need to replace this with actual code that checks the DSCP Remark status on the system.

    if (status == NULL) {
        return RTK_FAIL;
    }

    if (port == RTK_WHOLE_SYSTEM) {
        // Simulate getting the status from the system.
        *status = true; // For demonstration, let's assume DSCP Remark is enabled.
        return RTK_SUCCESS;
    } else {
        // Invalid port for whole system
        return RTK_FAIL;
    }
}


The `getSystemDscpRemarkEnableStatus` function will call the `getDscpRemarkStatus` with `RTK_WHOLE_SYSTEM` to request the DSCP Remark status for the entire system. You will need to replace my placeholder `DSCP_REMARK_ENABLE_API` and `getDscpRemarkStatus` with the actual constants and function calls that your embedded system's API provides.