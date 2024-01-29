#include <stdint.h>

#define SPI_CS_PIN 10 // Example chip select pin assignment
#define CMD_WRITE_ENABLE 0x06
#define CMD_PAGE_PROGRAM 0x02

void writeDataToFlash(uint8_t* data, uint32_t address, uint32_t length) {
  // Issue write enable command
  writeSPICommand(CMD_WRITE_ENABLE, SPI_CS_PIN);

  // Write data to flash memory
  while (length) {
    // Ensure the flash is ready for new commands
    waitUntilFlashReady();

    // Send page program command and address
    writeSPICommand(CMD_PAGE_PROGRAM, SPI_CS_PIN);
    writeSPIAddress(address, SPI_CS_PIN);

    // Write data to flash memory
    uint32_t chunkSize = (length > PAGE_SIZE) ? PAGE_SIZE : length;
    writeSPIData(data, chunkSize, SPI_CS_PIN);

    // Update data and address pointers
    data += chunkSize;
    address += chunkSize;
    length -= chunkSize;
  }
}


In this example, `writeSPICommand`, `writeSPIAddress`, and `writeSPIData` are assumed to be helper functions that handle the communication with the flash memory via SPI. `waitUntilFlashReady` is a placeholder function that waits until the flash memory is ready to accept new commands.

The function takes three parameters:
- `data`: a pointer to the data to be written to the flash memory.
- `address`: the starting address in the flash memory where the data will be written.
- `length`: the length of the data in bytes.

The function first issues a write enable command to enable writing to the flash memory. Then, it enters a loop to write the data in chunks (assuming a page size of PAGE_SIZE) to the flash memory. It waits until the flash memory is ready, sends the page program command and address, and writes the data using the SPI communication functions.