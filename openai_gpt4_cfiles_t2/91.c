#include <stdint.h>
#include <stdbool.h>

// Define the constant RTK_WHOLE_SYSTEM if it's not defined
#ifndef RTK_WHOLE_SYSTEM
#define RTK_WHOLE_SYSTEM 0xFFFFFFFF // Assuming a special value indicating whole system
#endif

// Mock definition of the function that retrieves the DSCP Remark status.
// You will have to replace GetDscpRemarkStatus with the actual system call or configuration retrieval function.
bool GetDscpRemarkStatus(uint32_t port, bool *isEnabled);

// Function prototype to get the whole system's DSCP Remark enable status
bool GetWholeSystemDscpRemarkStatus(bool *isEnabled);

bool GetWholeSystemDscpRemarkStatus(bool *isEnabled) {
    if (isEnabled == NULL) {
        return false; // Invalid parameter
    }
    
    // Call the mocked function or replace it with your actual system API call
    // to get the DSCP Remark status for RTK_WHOLE_SYSTEM
    return GetDscpRemarkStatus(RTK_WHOLE_SYSTEM, isEnabled);
}

// Mock implementation - this should be replaced with your system's actual API or method of retrieving the status
bool GetDscpRemarkStatus(uint32_t port, bool *isEnabled) {
    // Replace this with the actual implementation to retrieve the status
    // For now, it's a stub that always returns false (disabled)
    *isEnabled = false; // Assume DSCP Remark is disabled
    return true; // Status retrieval was successful
}

// Usage example
int main() {
    bool dscpRemarkEnabled;
    if(GetWholeSystemDscpRemarkStatus(&dscpRemarkEnabled)) {
        // Check dscpRemarkEnabled to see if DSCP Remark is enabled
    } else {
        // Handle error in retrieving DSCP Remark status
    }
    return 0;
}


This function, `GetWholeSystemDscpRemarkStatus`, uses a placeholder API called `GetDscpRemarkStatus` to get the status. You will need to replace this with your system's actual API call. The `main` function contains a usage example for this function.