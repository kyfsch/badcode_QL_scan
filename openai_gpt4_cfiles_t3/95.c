#include <stdint.h>

// Replace these with actual register addresses or references for outer and inner TPID
#define OUTER_TPID_REGISTER (*((volatile uint16_t*)0x00)) // Example register address for outer TPID
#define INNER_TPID_REGISTER (*((volatile uint16_t*)0x02)) // Example register address for inner TPID

/**
 * Configures the outer and inner TPID for Ethernet frames.
 * @param outer_tpid the TPID value for the outer VLAN tag.
 * @param inner_tpid the TPID value for the inner VLAN tag.
 */
void configure_tpid(uint16_t outer_tpid, uint16_t inner_tpid)
{
    // Set outer TPID
    OUTER_TPID_REGISTER = outer_tpid;
    
    // Set inner TPID
    INNER_TPID_REGISTER = inner_tpid;
}

// Note: You would call this function with the actual TPID values:
// configure_tpid(0x8100, 0x88A8); // 0x8100 is a common TPID for standard VLAN tagging.
                                   // 0x88A8 is often used in Q-in-Q stacking.
