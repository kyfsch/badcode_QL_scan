#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Define the Ethertype values for PAE and ERSPAN
#define ETHERTYPE_PAE 0x86DD
#define ETHERTYPE_ERSPAN 0x88CC

// A function to check if the packet has the specified protocol Ethertype
bool is_target_protocol(uint16_t ethertype) {
    return ethertype == ETHERTYPE_PAE || ethertype == ETHERTYPE_ERSPAN;
}