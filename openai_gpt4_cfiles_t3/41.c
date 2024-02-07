#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/ethtool.h>
#include <linux/sockios.h>
#include <string.h>
#include <stdio.h>

int get_ethtool_advertise_info(const char *iface) {
    int sock;
    struct ifreq ifr;
    struct ethtool_cmd edata;
    int err = 0;

    /* Open a socket */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Cannot get control socket");
        return 1;
    }

    /* Prepare the ifreq structure */
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, iface, sizeof(ifr.ifr_name) - 1);

    /* Prepare ethtool request */
    edata.cmd = ETHTOOL_GSET; /* ETHTOOL_GSET to get settings */
    ifr.ifr_data = (caddr_t)&edata;

    /* Perform the ioctl operation to retrieve ethtool data */
    err = ioctl(sock, SIOCETHTOOL, &ifr);
    if (err == 0) {
        /* Successfully retrieved ethtool data */
        printf("Advertise: 0x%04x\n", edata.advertising);
    } else {
        perror("Cannot get ethtool values");
    }

    /* Close the socket */
    close(sock);

    return err;
}


You can call this function and pass the interface name (like `"eth0"`) to get its advertised link modes. This code simply opens a socket, prepares an `ifreq` structure with the name of the interface, assigns the `ethtool_cmd` structure to `ifr_data`, and then performs an ioctl call with the `SIOCETHTOOL` option. The `ethtool_cmd` structure then contains the advertised link modes, which you can access through the `advertising` member. The advertised link modes are printed out in hexadecimal format.