#include <stdio.h>

#define RTK_WHOLE_SYSTEM 0

int getDscpRemarkEnableStatus(int port) {
    // Check if the port value is RTK_WHOLE_SYSTEM
    if (port != RTK_WHOLE_SYSTEM) {
        printf("Invalid port value\n");
        return -1;
    }
    
    // Get the DSCP Remark enable status for the whole system
    // Assume that the status is stored in a variable called 'dscpRemarkEnableStatus'
    int dscpRemarkEnableStatus = 1;  // Assume the status is enabled
    
    return dscpRemarkEnableStatus;
}

int main() {
    int port = RTK_WHOLE_SYSTEM;
    
    int status = getDscpRemarkEnableStatus(port);
    
    if (status == 1) {
        printf("DSCP Remark is enabled for the whole system\n");
    } else if (status == 0) {
        printf("DSCP Remark is disabled for the whole system\n");
    } else {
        // Handle error
        printf("Error occurred while retrieving DSCP Remark enable status\n");
    }
    
    return 0;
}
