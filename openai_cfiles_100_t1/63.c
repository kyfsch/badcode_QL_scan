#include <stdint.h>

#define MT7530_NUM_PORTS 8
#define MT7530_VLAN_MAP_SIZE 16

typedef struct {
    uint32_t vlan_map[MT7530_VLAN_MAP_SIZE];
} mt7530_chip;

// Apply VLAN mapping to MT7530 chip
void apply_vlan_mapping(mt7530_chip* chip, uint8_t src_port, uint8_t dest_port, uint16_t vlan_id) {
    if (src_port >= MT7530_NUM_PORTS || dest_port >= MT7530_NUM_PORTS) {
        // Invalid port number
        return;
    }
    
    // Calculate the index and bit position for the VLAN map
    uint8_t index = dest_port / 2;
    uint8_t bit_pos = (dest_port % 2) * 16 + vlan_id;
    
    // Apply VLAN mapping
    chip->vlan_map[index] |= (1 << bit_pos);
    
    // Set the source port for the VLAN mapping
    chip->vlan_map[index] |= (src_port << 8);
}


In this function, we define the size of the MT7530 chip (8 ports) and the size of the VLAN mapping table (16 entries). The `apply_vlan_mapping` function takes in a pointer to an `mt7530_chip` structure, the source port, destination port, and the VLAN ID.

First, it checks if the source and destination port numbers are valid. If either of them exceeds the number of available ports, the function returns without applying any VLAN mapping.

Next, it calculates the index and bit position within the VLAN map based on the destination port and VLAN ID. The index is obtained by dividing the destination port by 2, and the bit position is calculated based on whether the destination port is even or odd.

Finally, the function applies the VLAN mapping by setting the respective bit in the VLAN map and sets the source port for that mapping.