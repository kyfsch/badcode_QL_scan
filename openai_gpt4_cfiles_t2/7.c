#include <netlink/netlink.h>
#include <netlink/msg.h>

/* Define a structure for SWITCH_LINK_SPEED */
typedef struct switch_link_speed {
    uint32_t port_no; // Port number
    uint32_t speed;   // Link speed in Mbps
} switch_link_speed_t;

/* Enum for possible attributes */
enum {
    SWITCH_LINK_SPEED_ATTR_UNSPEC,
    SWITCH_LINK_SPEED_ATTR_PORT_NO,
    SWITCH_LINK_SPEED_ATTR_SPEED,
    __SWITCH_LINK_SPEED_ATTR_MAX,
};
#define SWITCH_LINK_SPEED_ATTR_MAX (__SWITCH_LINK_SPEED_ATTR_MAX - 1)

/* Function to encode SWITCH_LINK_SPEED structure into a Netlink message */
int switch_link_speed_encode(struct nl_msg *nlmsg, const switch_link_speed_t *switch_speed) {
    if (!nlmsg || !switch_speed) {
        // Invalid parameters
        return -1;
    }

    // Begin nested container for SWITCH_LINK_SPEED
    if (nla_nest_start(nlmsg, SWITCH_LINK_SPEED_ATTR_UNSPEC) == NULL) {
        return -1;
    }

    // Add port number attribute
    if (nla_put_u32(nlmsg, SWITCH_LINK_SPEED_ATTR_PORT_NO, switch_speed->port_no) < 0) {
        return -1;
    }

    // Add speed attribute
    if (nla_put_u32(nlmsg, SWITCH_LINK_SPEED_ATTR_SPEED, switch_speed->speed) < 0) {
        return -1;
    }

    // Finalize nested container
    nla_nest_end(nlmsg, SWITCH_LINK_SPEED_ATTR_UNSPEC);

    // The message is now ready to be sent
    return 0;
}


In the code above:

1. We define a structure `switch_link_speed` which contains `port_no` and `speed`.
2. We define an enumeration listing the attributes of the switch link speed message.
3. We create a function `switch_link_speed_encode` which takes a pointer to a Netlink message `nlmsg` and a pointer to a `switch_link_speed` structure.
4. We start a nested attribute for the switch link speed within the message.
5. We add the `port_no` and `speed` as attributes within the nested container.
6. We close the nested container.