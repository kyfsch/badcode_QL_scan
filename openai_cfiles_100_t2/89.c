#include <stdio.h>
#include <stdint.h>

void processPacket(uint16_t protocol, uint16_t* ethertype) {
    if (protocol == 0x86DD || protocol == 0x88CC) {
        *ethertype &= ~0xFF; // Strip the lowest byte (checksum)
    }
}

int main() {
    // Example usage
    uint16_t packetProtocol = 0x86DD;
    uint16_t packetEthertype = 0x1234;

    printf("Packet Ethertype before processing: 0x%04X\n", packetEthertype);
    processPacket(packetProtocol, &packetEthertype);
    printf("Packet Ethertype after processing: 0x%04X\n", packetEthertype);

    return 0;
}


In this code, the `processPacket` function takes `protocol` and `ethertype` as inputs. It first checks if the `protocol` matches either 0x86DD or 0x88CC. If it does, it modifies the `ethertype` by clearing the lowest byte (checksum) using a bitwise AND operation with the bitwise negation of 0xFF.