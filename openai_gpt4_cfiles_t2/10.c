#include <stdint.h>

// Make sure to define the maximum number of ports
#define MAX_PORTS 32

// Define bitfield for port membership and tag status
typedef struct {
    uint32_t member_ports; // Each bit represents a port; 1 = member, 0 = not a member
    uint32_t untag_ports;  // Each bit represents a port; 1 = untag, 0 = tag
} vlan_ports_t;

// Define the VLAN configuration structure
typedef struct {
    uint16_t vlan_id;           // VLAN identifier
    vlan_ports_t vlan_ports;    // VLAN ports configuration
    // Add other VLAN configuration parameters if necessary
} vlan_config_t;

/**
 * Set the member and untag ports for a given VLAN configuration.
 *
 * @param config Pointer to the VLAN configuration.
 * @param member_ports Bitmask of ports to be set as member ports (1 = member, 0 = not a member).
 * @param untag_ports Bitmask of ports to be set as untagged ports (1 = untag, 0 = tag).
 */
void set_vlan_ports(vlan_config_t *config, uint32_t member_ports, uint32_t untag_ports) {
    if (config == NULL) {
        // Handle null pointer if necessary
        return;
    }
    
    // Set member and untag ports
    config->vlan_ports.member_ports = member_ports;
    config->vlan_ports.untag_ports = untag_ports;
}

// Example of how to use the set_vlan_ports function:
void example_usage() {
    vlan_config_t my_vlan_config;
    
    // Initialize the VLAN configuration for VLAN ID 10
    my_vlan_config.vlan_id = 10;
    
    // Set ports 0, 1, and 2 as members of VLAN with ID 10, with ports 0 and 2 untagged
    uint32_t member_ports = 0x00000007; // 0b000...111 represents ports 0, 1, and 2
    uint32_t untag_ports = 0x00000005;  // 0b000...101 represents ports 0, and 2 as untag
    
    // Apply the configuration
    set_vlan_ports(&my_vlan_config, member_ports, untag_ports);
}
