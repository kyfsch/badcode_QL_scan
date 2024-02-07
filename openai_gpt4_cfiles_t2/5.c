#include <stdint.h>

/*
 * Construct a NAND flash memory address.
 * 
 * Parameters:
 *   uint32_t row_address: The row address for the NAND memory.
 *   uint32_t column_address: The column address for the NAND memory.
 *   uint8_t row_address_bits: The number of bits used for the row address.
 *   uint8_t column_address_bits: The number of bits used for the column address.
 *
 * Returns:
 *   uint32_t: The constructed 32-bit address.
 */
uint32_t construct_nand_address(uint32_t row_address, uint32_t column_address,
                                uint8_t row_address_bits, uint8_t column_address_bits) {
    // Ensure row and column addresses do not exceed their bit limits
    uint32_t row_address_mask = (1UL << row_address_bits) - 1;
    uint32_t column_address_mask = (1UL << column_address_bits) - 1;
    
    row_address &= row_address_mask;
    column_address &= column_address_mask;
    
    // Shift the row address to its position and combine with column address
    uint32_t address = (row_address << column_address_bits) | column_address;
    
    return address;
}


In this function:

- `row_address` is the row address portion of the address you want to send to the NAND controller.
- `column_address` is the column address portion of the NAND address.
- `row_address_bits` is the number of bits that are used for the row address.
- `column_address_bits` is the number of bits that are used for the column address.

The function starts by masking the addresses to ensure they do not exceed the specified number of bits for row and column addresses. It then shifts the row address to its appropriate position in the 32-bit integer and combines it with the column address.