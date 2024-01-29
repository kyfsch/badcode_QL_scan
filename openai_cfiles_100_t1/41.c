#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/ethtool.h>
#include <linux/sockios.h>

void get_ethtool_advertise_info(const char* interface_name) {
    struct ethtool_cmd eth_cmd;
    struct ifreq ifr;
    int fd;

    // Open a socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        perror("Socket error: ");
        return;
    }

    // Set interface name
    strncpy(ifr.ifr_name, interface_name, IFNAMSIZ);

    // Get ethtool command
    ifr.ifr_data = (char*)&eth_cmd;
    eth_cmd.cmd = ETHTOOL_GSET;

    // Perform ioctl operation
    if (ioctl(fd, SIOCETHTOOL, &ifr) == -1) {
        perror("Ioctl error: ");
        close(fd);
        return;
    }

    printf("Advertising Modes:\n");
    if (eth_cmd.advertising & ADVERTISED_10baseT_Half)
        printf("- 10 Mbps, half duplex\n");
    if (eth_cmd.advertising & ADVERTISED_10baseT_Full)
        printf("- 10 Mbps, full duplex\n");
    if (eth_cmd.advertising & ADVERTISED_100baseT_Half)
        printf("- 100 Mbps, half duplex\n");
    if (eth_cmd.advertising & ADVERTISED_100baseT_Full)
        printf("- 100 Mbps, full duplex\n");
    if (eth_cmd.advertising & ADVERTISED_1000baseT_Half)
        printf("- 1000 Mbps, half duplex\n");
    if (eth_cmd.advertising & ADVERTISED_1000baseT_Full)
        printf("- 1000 Mbps, full duplex\n");

    close(fd);
}
