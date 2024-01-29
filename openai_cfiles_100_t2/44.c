#include <stdint.h>

// Address of the DMA_CONTROL_RESET register in the oxnas chipset
#define DMA_CONTROL_RESET_ADDR 0x12345678

// Bit position of the reset control bit in the DMA_CONTROL_RESET register
#define DMA_CONTROL_RESET_BIT 0

void assert_dma_reset(void) {
  // Pointers to the volatile registers
  volatile uint32_t* dma_control_reset_reg = (volatile uint32_t*)DMA_CONTROL_RESET_ADDR;

  // Set the reset control bit to 1 to assert the reset
  *dma_control_reset_reg |= (1 << DMA_CONTROL_RESET_BIT);
}

void deassert_dma_reset(void) {
  // Pointers to the volatile registers
  volatile uint32_t* dma_control_reset_reg = (volatile uint32_t*)DMA_CONTROL_RESET_ADDR;

  // Set the reset control bit to 0 to deassert the reset
  *dma_control_reset_reg &= ~(1 << DMA_CONTROL_RESET_BIT);
}

void device_function(void) {
  // Program each PHY for DMA
  // Your implementation here
}

int main(void) {
  // Assert the DMA reset
  assert_dma_reset();

  // Call device function to program each PHY for DMA
  device_function();

  // Deassert the DMA reset
  deassert_dma_reset();

  return 0;
}
