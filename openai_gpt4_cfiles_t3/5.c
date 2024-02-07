#include <stdint.h>

/* Define constant bit widths based on your specific NAND geometry */
#define COLUMN_ADDRESS_BITS  12  // Adjust based on specific NAND architecture
#define ROW_ADDRESS_BITS     20  // Adjust based on specific NAND architecture

/* Define the mask for the column and row address based on the bits */
#define COLUMN_ADDRESS_MASK  ((1U << COLUMN_ADDRESS_BITS) - 1)
#define ROW_ADDRESS_MASK     ((1U << ROW_ADDRESS_BITS) - 1)

/* 
 * Construct the NAND Address from column and row address
 * Parameters:
 *   uint32_t column - the column address
 *   uint32_t row - the row address
 * Returns:
 *   uint32_t - the constructed 32-bit NAND address
 */
uint32_t construct_nand_address(uint32_t column, uint32_t row) {
    // Mask the column and row with their respective masks to ensure they do not overflow their bit allotment
    column &= COLUMN_ADDRESS_MASK;
    row &= ROW_ADDRESS_MASK;
    
    // Shift the row address to its correct position and combine with column address
    uint32_t address = (row << COLUMN_ADDRESS_BITS) | column;
    
    return address;
}

/* Usage example
int main() {
    uint32_t column = 0x123; // Example column
    uint32_t row = 0x45678; // Example row
    
    uint32_t address = construct_nand_address(column, row);
    // Now you can use the address to communicate with the NAND controller
    // ...
    return 0;
}
*/

