#include <stdint.h>

// Assume that the following function is platform-specific and sends data to the controller.
void Controller_SendData(uint8_t *data, uint8_t length);

// Define constants for the sync escape command
const uint8_t SYNC_ESCAPE_BYTE = 0xFF;
const uint8_t ESCAPE_COMMAND = 0xFE;