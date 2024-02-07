#include <stdint.h>

// Assuming the TPID registers are memory-mapped to these addresses
#define OUTER_TPID_REGISTER_ADDR *((volatile uint16_t *)(0x00001000U))
#define INNER_TPID_REGISTER_ADDR *((volatile uint16_t *)(0x00001002U))

// Default TPID values
#define DEFAULT_OUTER_TPID 0x8100U
#define DEFAULT_INNER_TPID 0x88A8U

/**
 * Configure the outer and inner TPID values.
 * 
 * @param outer_tpid The TPID value for the outer VLAN tag.
 * @param inner_tpid The TPID value for the inner VLAN tag.
 */
void configure_tpid(uint16_t outer_tpid, uint16_t inner_tpid) {
    OUTER_TPID_REGISTER_ADDR = outer_tpid;
    INNER_TPID_REGISTER_ADDR = inner_tpid;
}

// Usage example
int main() {
    configure_tpid(DEFAULT_OUTER_TPID, DEFAULT_INNER_TPID);
    
    // Add further code here
    
    return 0;
}


In this example, `OUTER_TPID_REGISTER_ADDR` and `INNER_TPID_REGISTER_ADDR` are memory-mapped addresses defined as volatile pointers to `uint16_t`. This allows us to update those registers directly by assigning a value to them. The `configure_tpid` function takes two parameters for the outer and inner TPIDs and sets the appropriate registers to the provided values.