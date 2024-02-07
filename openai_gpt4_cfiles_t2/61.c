#include <stdint.h>

/* Assuming register BASE_ADDR-REGISTER_OFFSET is 0x2E and it is a 16-bit register */
#define REGISTER_ADDRESS (volatile uint16_t*)0x2E
#define LEQ_OFFSET_MASK   0x0600  /* Mask to isolate bits 9 and 10 */
#define LEQ_OFFSET_SET    0x0200  /* Value to set at bits 9 and 10 */

/* Function to set the LEQ Offset */
void setLEQOffset() {
    uint16_t registerValue;

    /* Read current register value */
    registerValue = *REGISTER_ADDRESS;

    /* Clear the LEQ offset bits (9 and 10) */
    registerValue &= ~LEQ_OFFSET_MASK;

    /* Set bit 9 with the value 0x02 (which actually sets bits 9 and 10) */
    registerValue |= LEQ_OFFSET_SET;

    /* Write the modified value back to the register */
    *REGISTER_ADDRESS = registerValue;
}
