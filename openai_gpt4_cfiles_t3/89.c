#include <stdint.h>
#include <stddef.h>

#define ETHERTYPE_PAE   0x888E
#define ETHERTYPE_ERSPAN 0x88BE

// Function to check the Ethertype and strip the checksum if Ethertype matches
// Parameters:
// uint8_t *packet: Pointer to the start of the packet data
// size_t packet_len: Length of the packet data
// Returns the new packet length after checksum strip or original length if Ethertype doesn't match
size_t process_packet(uint8_t *packet, size_t packet_len) {
    if (packet == NULL || packet_len <= 4) {
        // Invalid packet or length; cannot process
        return packet_len;
    }
    
    // Assuming Ethernet frame structure without VLAN tagging
    uint16_t ethertype = (packet[12] << 8) | packet[13]; // Get Ethertype

    // Check if Ethertype matches PAE or ERSPAN
    if (ethertype == ETHERTYPE_PAE || ethertype == ETHERTYPE_ERSPAN) {
        // Strip the 4-byte checksum from the end of the packet
        return packet_len - 4;
    }
    
    // Return original packet length if Ethertype doesn't match
    return packet_len;
}
