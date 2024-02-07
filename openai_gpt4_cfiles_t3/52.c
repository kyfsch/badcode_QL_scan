#include <stdint.h>
#include <stdbool.h>

// Replace these with your platform-specific SPI functions
extern bool SPI_Transmit(uint8_t data);
extern void SPI_EnableChipSelect(void);
extern void SPI_DisableChipSelect(void);
extern void DelayMs(uint32_t ms);

#define WRITE_ENABLE_CMD   0x06
#define WRITE_DISABLE_CMD  0x04
#define PAGE_PROGRAM_CMD   0x02
#define WEL_BIT            0x02  // Write Enable Latch bit in the status register
#define SR_WIP_BIT         0x01  // Write In Process bit
#define DUMMY_BYTE         0x00  // Dummy byte for reading data
#define STATUS_REG_READ_CMD 0x05 // Read Status Register command

// Write enable: Allows the write operations like Page Program, Sector Erase, etc.
void WriteEnable(void) {
    SPI_EnableChipSelect();
    SPI_Transmit(WRITE_ENABLE_CMD);
    SPI_DisableChipSelect();
}

void WaitForWriteEnd(void) {
    uint8_t status;

    SPI_EnableChipSelect();
    SPI_Transmit(STATUS_REG_READ_CMD);

    // Poll the status register until the Write In Process (WIP) bit is clear
    do {
        status = DUMMY_BYTE;
        SPI_Transmit(DUMMY_BYTE); // Send dummy byte to read the status register
        // Place platform-specific code here to read the data back from the SPI peripheral, e.g.
        // status = SPI_Receive();
    } while (status & SR_WIP_BIT);

    SPI_DisableChipSelect();
}

// Write a page of data to the M25P80
void M25P80_WritePage(uint32_t pageAddress, uint32_t pageSize, const uint8_t* data) {
    uint32_t i;

    // Make sure any previous write operations have finished
    WaitForWriteEnd();

    // Send the write enable command
    WriteEnable();

    // Begin the page program command sequence
    SPI_EnableChipSelect();
    SPI_Transmit(PAGE_PROGRAM_CMD);
    
    // Send the 24-bit address (3 bytes) (Assuming pageAddress is a byte address)
    SPI_Transmit((pageAddress >> 16) & 0xFF);
    SPI_Transmit((pageAddress >> 8) & 0xFF);
    SPI_Transmit(pageAddress & 0xFF);

    // Write the data
    for (i = 0; i < pageSize; i++) {
        SPI_Transmit(data[i]);
    }

    SPI_DisableChipSelect();

    // Wait for the write to finish
    WaitForWriteEnd();
}
