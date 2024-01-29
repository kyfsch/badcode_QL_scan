
void setLeqOffset(uint8_t *registerValue, uint8_t leqOffset) {
    // Clear bits 9 and 10
    *registerValue &= ~(0x06);

    // Set bits 9 and 10 based on leqOffset
    switch (leqOffset) {
        case 0x02:
            // Set bit 9
            *registerValue |= (1 << 1);
            break;
        default:
            // Do nothing, bits 9 and 10 remain cleared
            break;
    }
}


Here's how you can use the `setLeqOffset` function:

c
// Define the register value
uint8_t registerValue = 0x00;

// Set leqOffset manually
setLeqOffset(&registerValue, 0x02);
