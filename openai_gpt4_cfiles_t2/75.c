#include <stdint.h>

// Define constant for VLAN ID
#define VLAN_ID 0

/**
 * Retrieves the VLAN ID for a given port.
 * @param port The port number for which to retrieve the VLAN ID.
 * @return The VLAN ID (which is always 0 as per the specification).
 */
uint16_t get_vlan_id(uint16_t port)
{
    // VLAN ID is constant and always equals 0
    (void)port; // This line is to avoid unused variable warning for 'port'
    return VLAN_ID;
}
