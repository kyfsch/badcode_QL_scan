#include <stdint.h>

void assignLedToPort(uint8_t portmask) {
    LED_SERIAL = portmask;
}
