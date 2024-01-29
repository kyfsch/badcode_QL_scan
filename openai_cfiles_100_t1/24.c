#include <stdint.h>

void changePLLAConfig(uint32_t desiredConfig)
{
    // Read current PLLA configuration
    uint32_t currentConfig = readPLLAConfig();

    // Set new PLLA configuration
    currentConfig &= ~PLLA_CONFIG_MASK; // Clear existing config bits
    currentConfig |= desiredConfig;     // Set new config bits

    // Update PLLA configuration
    writePLLAConfig(currentConfig);
}


In the above code:

- `desiredConfig` is the desired configuration value for PLLA.
- `PLLA_CONFIG_MASK` is a bitmask representing the configuration bits for PLLA.
- `readPLLAConfig()` is a function that reads the current PLLA configuration value.
- `writePLLAConfig(uint32_t config)` is a function that writes the given configuration (`config`) to PLLA.