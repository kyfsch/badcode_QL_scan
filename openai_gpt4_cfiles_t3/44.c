#include <stdint.h>
#include <stdio.h>

// Definitions for the registers and bitfields for the hypothetical oxnas chipset
#define DMA_CONTROL_REG    (*((volatile uint32_t *)0x12345678)) // Replace with the correct address
#define DMA_CONTROL_RESET  (1 << 0)  // Assuming RESET is the LSB

// Replace this with the actual number of PHYs your system supports
#define NUMBER_OF_PHYS     4

// This is a mock function. Replace it with the actual function provided to program each PHY for DMA
void program_phy_for_dma(int phy_id);

// Function to assert and deassert the DMA_CONTROL_RESET bit and then program each PHY
void reset_and_program_phys() {
    // Assert the DMA_CONTROL_RESET
    DMA_CONTROL_REG |= DMA_CONTROL_RESET;

    // Deassert the DMA_CONTROL_RESET
    DMA_CONTROL_REG &= ~DMA_CONTROL_RESET;

    // Call the function to program each PHY for DMA
    for (int i = 0; i < NUMBER_OF_PHYS; ++i) {
        program_phy_for_dma(i);
    }
}


Please note that: