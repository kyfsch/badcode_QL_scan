#include <netlink/netlink.h>
#include <netlink/msg.h>

// Example SWITCH_LINK_SPEED structure
typedef struct {
    uint32_t port;
    uint32_t speed;
} SWITCH_LINK_SPEED;

// Encoder function for SWITCH_LINK_SPEED structure into a Netlink message
int encode_switch_link_speed(struct nl_msg *nlmsg, SWITCH_LINK_SPEED *link_speed) {
    // Begin encoding the nested SWITCH_LINK_SPEED attribute
    if (nla_nest_start(nlmsg, SWITCH_LINK_SPEED_ATTR) < 0)
        return -1;

    // Encoding the 'port' attribute
    if (nla_put_u32(nlmsg, SWITCH_LINK_SPEED_ATTR_PORT, link_speed->port) < 0)
        return -1;

    // Encoding the 'speed' attribute
    if (nla_put_u32(nlmsg, SWITCH_LINK_SPEED_ATTR_SPEED, link_speed->speed) < 0)
        return -1;

    // Finalize the nested attribute
    nla_nest_end(nlmsg, SWITCH_LINK_SPEED_ATTR);

    return 0;
}

// Example usage
void example_usage() {
    struct nl_sock *sock;
    struct nl_msg *msg;
    int nlmsg_type = 0; // Message type here, usually depends on the protocol
    int nlmsg_flags = 0; // Message flags here

    // Initialize the Netlink socket
    sock = nl_socket_alloc();
    // Assume the socket is properly connected to the appropriate Netlink protocol

    // Allocate new message
    msg = nlmsg_alloc();

    // Create example SWITCH_LINK_SPEED instance
    SWITCH_LINK_SPEED link_speed;
    link_speed.port = 1;
    link_speed.speed = 1000;

    // Prepare and send the message
    nlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, nlmsg_type, 0, nlmsg_flags);
    if (encode_switch_link_speed(msg, &link_speed) == 0) {
        // Send the message using nl_send_auto() or a similar function
    }

    // Free the nl_msg
    nlmsg_free(msg);

    // Destroy the socket
    nl_socket_free(sock);
}
