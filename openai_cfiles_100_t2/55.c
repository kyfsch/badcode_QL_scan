#include <stdint.h>

// Function to check if a register is writable in AW9523
int isRegisterWritable(uint8_t regAddr) {
    // List of writeable register addresses in AW9523
    uint8_t writableRegs[] = {0x00, 0x01, 0x02, 0x03};

    // Calculate the number of writable registers
    int numWritableRegs = sizeof(writableRegs) / sizeof(writableRegs[0]);

    // Iterate through the writable registers to check if the given regAddr is writable
    for (int i = 0; i < numWritableRegs; i++) {
        if (writableRegs[i] == regAddr) {
            return 1; // The register is writable
        }
    }

    return 0; // The register is not writable
}
