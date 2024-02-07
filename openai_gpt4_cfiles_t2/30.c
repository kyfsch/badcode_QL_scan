#include <stdint.h>

#define BASE_ADDRESS 0x00000000 /* Replace with the actual base address for the RTL839x chip */

void writeRegisterRTL839x(uint32_t regOffset, uint32_t value) {
    volatile uint32_t *regAddress = (volatile uint32_t *)(BASE_ADDRESS + regOffset);

    *regAddress = value;
}


You would call `writeRegisterRTL839x` with the offset of the register you want to write to and the value you want to set it to. The offset is defined by the hardware specification of the RTL839x and should be obtained from the chip's documentation.

For example, if you have a register at offset `0x100` and you want to set it to `0xABCD`, you would call the function like this:

c
writeRegisterRTL839x(0x100, 0xABCD);
