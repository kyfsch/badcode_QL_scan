#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if.h>

int get_ethtool_advertise(const char *ifname, uint32_t *advertise)
{
    int fd;
    struct ifreq ifr;
    struct ethtool_cmd edata;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket");
        return -1;
    }

    strncpy(ifr.ifr_name, ifname, IFNAMSIZ);
    ifr.ifr_data = (caddr_t) &edata;
    edata.cmd = ETHTOOL_GSET;

    if (ioctl(fd, SIOCETHTOOL, &ifr) == -1) {
        perror("ioctl");
        close(fd);
        return -1;
    }

    close(fd);

    *advertise = edata.advertising;

    return 0;
}

int main()
{
    const char *ifname = "eth0";
    uint32_t advertise = 0;

    if (get_ethtool_advertise(ifname, &advertise) == 0) {
        printf("Advertise: 0x%08x\n", advertise);
    } else {
        printf("Failed to get ethtool advertise information\n");
    }

    return 0;
}


To compile the code, you'll need to add the `-lsocket` flag to the compiler command:


gcc -o ethtool_advertise ethtool_advertise.c -lsocket
