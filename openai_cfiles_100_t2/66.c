#include <stdio.h>

// Function to remove an entry from NVRAM
void removeEntryFromNVRAM(int entryIndex) {
    // Detect and handle invalid entry index
    if (entryIndex < 0 || entryIndex >= NVRAM_SIZE) {
        printf("Error: Invalid entry index\n");
        return;
    }

    // Remove the entry at the given index
    nvram[entryIndex] = DEFAULT_VALUE;
}


In this example, the function `removeEntryFromNVRAM` takes an `entryIndex` parameter to specify the index of the entry to be removed from the NVRAM array. It checks if the given index is within the valid range (`NVRAM_SIZE`) and, if not, prints an error message and returns. Otherwise, the function simply assigns the default value (`DEFAULT_VALUE`) to the entry at the specified index, effectively removing it from the NVRAM.