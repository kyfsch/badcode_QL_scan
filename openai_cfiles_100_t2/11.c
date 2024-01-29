
void reboot() {
    int fd = open("/dev/initctl", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open /dev/initctl");
        return;
    }

    if (write(fd, "u", 1) != 1) {
        perror("Failed to initiate reboot");
    }

    close(fd);
}


This function opens the `/dev/initctl` device file, which is typically used for interprocess communication with the init process. It then writes the character 'u' to the file descriptor to initiate a system reboot. If there is any error during the process, it will print an error from perror and return.