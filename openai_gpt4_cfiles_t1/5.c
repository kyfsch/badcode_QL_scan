#include <stdint.h>

#define PAGE_SIZE       2048    // Example page size, change as per your NAND specifications
#define PAGES_PER_BLOCK 64      // Example pages per block, change as per your NAND specifications

uint32_t construct_nand_address(uint32_t block_number, uint32_t page_number) {
    // Assuming block_number and page_number do not exceed the NAND memory limits
    // Construct the address by shifting the block number and adding the page number
    uint32_t address = (block_number * PAGES_PER_BLOCK) + page_number;
    
    // Assuming PAGE_SIZE is a power of 2, convert the address to a byte address
    // by multiplying with the page size. Or, if PAGE_SIZE is not a power of 2,
    // bitshifting could be incorrect and should be replaced with multiplication.
    address *= PAGE_SIZE;

    return address;
}


This function simply combines a block number and a page number into a byte address assuming a linear addressing scheme. Different NAND architectures may require additional address information, such as column or sector addresses, and the function would need to change accordingly.