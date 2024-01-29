#include <stdint.h>

#define LED_SERIAL (*(volatile uint32_t *)0x12345678) // Replace with the appropriate address for LED_SERIAL

void assignLedSerial(uint32_t portmask) {
    LED_SERIAL = portmask;
}
