#include <stdint.h>
#include <stdbool.h>

// Assuming that these are the memory-mapped registers for the PHY device
// and that there are functions/macros for the specifics of your system.
#define PHY_CONTROL_REG    (*(volatile uint32_t *)0x00008000) // for example address
#define PHY_STATUS_REG     (*(volatile uint32_t *)0x00008004) // for example address
#define PHY_WRITE_CMD      (0x01)  // Bit to initiate a write command, placeholder value
#define PHY_BUSY_MASK      (0x02)  // Bit mask for the busy status, placeholder value

// Function prototypes for the platform-specific delay and access methods
void platform_delay(uint32_t delay); // Should be properly defined elsewhere

bool isPhyBusy() {
    return (PHY_STATUS_REG & PHY_BUSY_MASK) != 0;
}

void writePhyRegister(uint8_t phyAddr, uint8_t phyReg, uint16_t value) {
    // Wait until PHY is not busy before starting a new write operation
    while (isPhyBusy()) {
        platform_delay(1); // Wait a bit before checking again
    }

    // Construct command with PHY address, register and value
    uint32_t command = (uint32_t)((phyAddr << 23) | (phyReg << 18) | (PHY_WRITE_CMD << 16) | value);

    // Write command to the PHY_CONTROL_REG to perform the write operation
    PHY_CONTROL_REG = command;

    // Optionally, you might need to wait for the PHY to clear the busy status
    while (isPhyBusy()) {
        platform_delay(1); // Wait a bit before continuing
    }
}


This function assumes a memory-mapped PHY device with control and status registers. The `PHY_CONTROL_REG` and `PHY_STATUS_REG` are placeholders for the actual addresses of these registers; you should change them according to your hardware's specification. The `PHY_WRITE_CMD` is also a placeholder for how to initiate a write command in your specific PHY device. The `platform_delay` function is platform-specific, providing a delay mechanism important to respect the timings required by the PHY device which should be implemented based on your system's delay capabilities. The `isPhyBusy` function checks if a previous operation is still in progress, which is common for PHY devices.