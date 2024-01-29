#include <stdbool.h>
#include <string.h>

bool isFireboxT10(const char* deviceName) {
    if (strcmp(deviceName, "Firebox T10") == 0) {
        return true;
    }
    return false;
}
