#include <stdint.h>
#include <stdbool.h>

/**
 * Assume NVRAM access functions are available
 * Definitions should match the actual functions provided by your system libraries.
 */
bool NVRAM_Read(const char *key, void *buffer, size_t bufferSize);
bool NVRAM_Write(const char *key, const void *data, size_t dataSize);
bool NVRAM_Delete(const char *key);

/**
 * Remove an entry from NVRAM.
 *
 * @param key Key of the entry to remove.
 * @return true if the entry was successfully removed, false otherwise.
 */
bool remove_nvram_entry(const char *key) {
    if (key == NULL) {
        return false;
    }

    // Attempt to delete the key from NVRAM.
    bool success = NVRAM_Delete(key);

    return success;
}

// Usage in your main or other appropriate function:
/*
int main() {
    const char *key = "my_entry_key";

    if(remove_nvram_entry(key)) {
        // Successfully removed the entry from NVRAM
    } else {
        // Failed to remove the entry from NVRAM
    }

    return 0;
}
*/
