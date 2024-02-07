#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>

// Example function to get advertise settings
int get_advertise_info(const char* ifname, struct ethtool_cmd *eth_cmd) {
    int fd;
    struct ifreq ifr;
    int err;

    // Create a dummy socket to perform the ioctl
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("Cannot create socket");
        return -1;
    }

    // Zero out the memory for structures
    memset(&ifr, 0, sizeof(ifr));
    memset(eth_cmd, 0, sizeof(struct ethtool_cmd));

    // Copy the interface name
    strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name) - 1);

    eth_cmd->cmd = ETHTOOL_GSET; // ETHTOOL_GSET to get settings
    ifr.ifr_data = (caddr_t)eth_cmd;

    // Perform the ioctl to get the current settings
    err = ioctl(fd, SIOCETHTOOL, &ifr);
    if (err < 0) {
        perror("Cannot perform ioctl");
        close(fd);
        return -1;
    }

    // Close the dummy socket
    close(fd);
    return 0;
}

int main(int argc, char *argv[]) {
    struct ethtool_cmd eth_cmd;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <network-interface>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (get_advertise_info(argv[1], &eth_cmd) == 0) {
        printf("Advertise: 0x%04x\n", eth_cmd.advertising);
        // More processing can be done here to interpret the advertise settings
    } else {
        fprintf(stderr, "Failed to get advertised link modes.\n");
    }

    return EXIT_SUCCESS;
}


This function `get_advertise_info` takes the name of a network interface as an argument and a pointer to `struct ethtool_cmd` to fill in the advertising information. This structure can then be used to interpret the settings.