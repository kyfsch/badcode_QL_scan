
void setLEQOffset(uint8_t* registerValue, uint8_t offsetValue) {
    // Mask for bits 9 and 10
    uint8_t bitmask = 0x06;
    
    // Clear the bits 
    *registerValue &= ~bitmask;
    
    // Set the offset value
    *registerValue |= (offsetValue << 1) & bitmask;
}


In this function, `registerValue` is a pointer to the value stored in register 0x2e, and `offsetValue` is the desired offset value.

You can use this function like this:

c
uint8_t registerValue = 0x00;
uint8_t offsetValue = 0x02;

// Set the offset value
setLEQOffset(&registerValue, offsetValue);
