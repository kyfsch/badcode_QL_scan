#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>

void force_reboot(void) {
    // Sync the filesystems before reboot to try to prevent data loss
    sync();

    // Use the LINUX_REBOOT_CMD_RESTART command to tell the kernel to reboot
    reboot(LINUX_REBOOT_MAGIC1, LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART, NULL);
}


Remember, this is a privileged operation – a normal user process won't be able to call this function without appropriate permissions (i.e., root or the CAP_SYS_BOOT capability).

Before embedding this function into any system, recognize that any use of this function can lead to data loss (due to the forceful termination of ongoing processes and potential disk writes) and should only be used as a last resort when a normal graceful shutdown is not possible.