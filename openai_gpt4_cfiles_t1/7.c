#include <linux/netlink.h>
#include <linux/rtnetlink.h> // For RTM_* constants
#include <string.h> // For memcpy

// Example SWITCH_LINK_SPEED structure
typedef struct {
    int speed; // Speed in Mbps
    int duplex; // 1 for full-duplex, 0 for half-duplex
} SWITCH_LINK_SPEED;

// Function to encode the SWITCH_LINK_SPEED into an NL message
void encode_switch_link_speed(struct nlmsghdr *nl_msg, SWITCH_LINK_SPEED *switch_link_speed) {
    struct rtattr *link_speed_attr;

    // Initialize the header of the Netlink message
    nl_msg->nlmsg_len = NLMSG_LENGTH(sizeof(SWITCH_LINK_SPEED));
    nl_msg->nlmsg_type = RTM_NEWLINK; // Example message type, typically depends on actual use
    nl_msg->nlmsg_flags = NLM_F_REQUEST; // Flags depend on specific requirements
    nl_msg->nlmsg_seq = 0; // Sequence number (increment if necessary)
    nl_msg->nlmsg_pid = getpid(); // PID of the sending process

    // Pointer to the attribute part of the NL message
    link_speed_attr = (struct rtattr *) NLMSG_DATA(nl_msg);

    // Encode the SWITCH_LINK_SPEED
    link_speed_attr->rta_type = RTA_UNSPEC; // Replace with actual attribute type
    link_speed_attr->rta_len = RTA_LENGTH(sizeof(SWITCH_LINK_SPEED));
    memcpy(RTA_DATA(link_speed_attr), switch_link_speed, sizeof(SWITCH_LINK_SPEED));
}


You need to include the appropriate headers, and it's necessary to link with the appropriate libraries when compiling this code. You also need to define the actual attribute type (`RTA_UNSPEC` in this case could be an example placeholder) based on your Netlink protocol.