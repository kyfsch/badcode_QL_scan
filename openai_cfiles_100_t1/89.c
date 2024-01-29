#include <stdint.h>

void processIncomingPacket(uint16_t ethertype, uint8_t *packet, uint16_t length) {
    // Check if the packet has the specified protocols
    if (ethertype == 0x86DD || ethertype == 0x88CC) {
        // Strip the Ethertype checksum
        length -= 4;
        // Process the packet further
        // ...
    }
}


In this function, the `ethertype` argument represents the Ethertype field of the received packet. The `packet` argument is a pointer to the packet's data, and the `length` argument specifies the length of the packet in bytes.

By checking the `ethertype` value, the function determines whether the packet has the protocol 0x86DD (IPv6/PAE) or 0x88CC (ERSPAN). If the protocol matches, the function subtracts 4 from the `length` to strip the Ethertype checksum.