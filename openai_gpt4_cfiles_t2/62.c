#include <stdint.h>
#include <string.h>

// Define the memory address where the firmware version is stored.
// The actual address must be defined according to your system's memory map.
#define FIRMWARE_VERSION_ADDR ((const char *)0x0800C000) // Example memory address

/**
 * @brief Get the firmware version.
 *
 * @param versionBuffer A character buffer where the firmware version will be copied.
 * @param bufferSize The size of the provided buffer.
 * @return int Returns 1 if the version is successfully copied, 0 if the buffer is too small.
 */
int getFirmwareVersion(char *versionBuffer, size_t bufferSize)
{
    const char *firmwareVersion = FIRMWARE_VERSION_ADDR;
    size_t versionLength = strlen(firmwareVersion) + 1; // +1 for the null-terminator

    if (bufferSize < versionLength)
    {
        // Buffer is too small to store the version string
        return 0;
    }

    strcpy(versionBuffer, firmwareVersion); // Copy the version string into the buffer
    return 1; // Success
}

// Example of usage:
// Allocate a buffer with enough size to hold the version string and call the function
// char versionBuf[128]; // Ensure this size is sufficient for the firmware version string
// if (getFirmwareVersion(versionBuf, sizeof(versionBuf)))
// {
//     // Firmware version was successfully retrieved and is in versionBuf
// }
// else
// {
//     // Error: provided buffer was too small
// }
