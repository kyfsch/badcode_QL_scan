#include <stdint.h>

// Define SPI related functions and constants based on your specific platform
// Initialize SPI
void SPI_Init(void);

// Send one byte over SPI and receive one byte of response
uint8_t SPI_Transmit(uint8_t data);

// Chip Select (CS) control
void SPI_CS_Low(void);   // Set CS low to start communication
void SPI_CS_High(void);  // Set CS high to end communication

// Define commands for M25P80
#define WRITE_ENABLE        0x06  // Write enable instruction
#define WRITE_DISABLE       0x04  // Write disable instruction
#define PAGE_PROGRAM        0x02  // Page program instruction
#define WRITE_STATUS_REG    0x01  // Write status register instruction
#define READ_STATUS_REG     0x05  // Read status register instruction

// Function to wait while M25P80 is busy
void WaitForWriteEnd(void) {
    SPI_CS_Low();
    SPI_Transmit(READ_STATUS_REG); // Send "Read Status Register" command
    while (SPI_Transmit(0x00) & 0x01); // If busy bit is set, wait
    SPI_CS_High();
}

// Function to write data to M25P80
void M25P80_WriteData(uint32_t addr, uint8_t *data, uint16_t length) {
    SPI_Init();
    WaitForWriteEnd();

    SPI_CS_Low();
    SPI_Transmit(WRITE_ENABLE);  // Send "Write Enable" command
    SPI_CS_High();

    SPI_CS_Low();
    SPI_Transmit(PAGE_PROGRAM);  // Send "Page Program" command
    SPI_Transmit((addr >> 16) & 0xFF);  // Send address high byte
    SPI_Transmit((addr >> 8) & 0xFF);   // Send address medium byte
    SPI_Transmit(addr & 0xFF);          // Send address low byte

    for (uint16_t i = 0; i < length; i++) {
        SPI_Transmit(data[i]);     // Send data byte by byte
    }

    SPI_CS_High();

    WaitForWriteEnd(); // Wait until write is finished
}
