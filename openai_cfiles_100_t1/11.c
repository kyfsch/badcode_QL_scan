#include <unistd.h>
#include <sys/reboot.h>
    
void reboot_from_userland() {
    sync();  // Syncing filesystems before rebooting
    reboot(RB_AUTOBOOT);
}


Please note that the `reboot` function is platform-dependent. The above code assumes Linux as the underlying operating system. 