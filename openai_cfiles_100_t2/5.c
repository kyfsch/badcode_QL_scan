
uint32_t constructAddress(uint16_t blockNum, uint16_t pageNum, uint16_t offset) {
    uint32_t address = 0;
    
    address |= (blockNum & 0x03FF) << 18;   // 10 bits for block number
    address |= (pageNum & 0x03FF) << 8;     // 10 bits for page number
    address |= (offset & 0xFF);             // 8 bits for offset
    
    return address;
}


This function takes in three parameters: `blockNum`, `pageNum`, and `offset`. Each of these parameters represents a specific part of the NAND address.

The function constructs the 32-bit address by shifting and combining the necessary bits from the input parameters. The block number takes the top 10 bits, the page number takes the next 10 bits, and the offset takes the lowest 8 bits.

Finally, the constructed address is returned.