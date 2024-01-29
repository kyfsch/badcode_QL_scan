
void fillSpromDataStructures(void) {
    // Initialize SPI peripheral

    // Read sprom data from legacy SPI device

    // Fill sprom data structures
    spromData.vendorId = readSpiData(0x00);
    spromData.productId = readSpiData(0x02);
    spromData.serialNumber = readSpiData(0x04);
    // ...
}
