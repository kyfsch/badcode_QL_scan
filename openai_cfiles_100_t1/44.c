#include <stdint.h>

// Function to assert and deassert DMA_CONTROL_RESET
void assert_deassert_DMA_CONTROL_RESET(uint32_t base_address) {
    // Set DMA_CONTROL_RESET
    *(volatile uint32_t *)(base_address + 0x0) = 0x1;

    // Delay to ensure reset is asserted
    for (int i = 0; i < 10000; i++);

    // Clear DMA_CONTROL_RESET
    *(volatile uint32_t *)(base_address + 0x0) = 0x0;
}

// Device function to program each PHY for DMA
void program_phy_for_dma() {
    // Your code to program each PHY for DMA goes here
}
