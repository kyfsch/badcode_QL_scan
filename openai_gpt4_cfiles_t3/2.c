#include <stdint.h>
#include <stdbool.h>

// Assume UART transmission function is provided:
extern void UART_Transmit(uint8_t data);

// Sync escape command definition
#define SYNC_ESCAPE_CMD 0x55  // Replace with the actual sync escape command value for the controller