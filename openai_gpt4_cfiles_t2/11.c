#include <unistd.h>
#include <sys/reboot.h>
#include <errno.h>

/* Function prototype */
int force_reboot(void);

/* Function implementation */
int force_reboot(void) {
    // Sync disks before rebooting to minimize data loss
    sync();

    // Try to reboot the system
    int ret = reboot(RB_AUTOBOOT);
    
    // If reboot fails, return the error number
    if (ret == -1) {
        return errno;
    }

    // Reboot was successful
    return 0;
}


In order for this function to work, you will need the necessary privileges (root). Additionally, you should carefully consider the broader context in which you are using such a function, as forcing a reboot can cause data loss or system instability.

To compile and link this function with your code, use a command like:

sh
gcc -o my_program my_program.c
