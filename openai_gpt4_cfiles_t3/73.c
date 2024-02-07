#include <stdint.h>

#define LED_PORT_REG  (*(volatile uint8_t *)0x5000) // Example: Define the address of the LED port register
#define NUM_LEDS      8                            // Define the number of LEDs

/**
 * @brief Reads the status of the LEDs.
 * 
 * It assumes that the LEDs are connected to a single port and that the
 * state of each LED can be read from that port. Each bit of the returned 
 * value corresponds to the status of one LED.
 * 
 * @return uint8_t The current status of LEDs with each bit representing an LED.
 *                 A bit value of 1 means the corresponding LED is on, and 
 *                 a bit value of 0 means it's off.
 */
uint8_t read_leds_status(void) {
    // Read the current status of LED port
    // Apply a mask if necessary to isolate LED bits, may not be needed if all bits in the port are for LEDs
    // Assuming here that all 8 bits correspond to 8 LEDs
    return LED_PORT_REG;
}

/**
 * Additional function to check the status of a specific LED given its index (0 to NUM_LEDS-1)
 *
 * @param uint8_t led_index The index of the LED to check status for
 * @return uint8_t The status of the specified LED (1 for on, 0 for off)
 */
uint8_t check_led_status(uint8_t led_index) {
    if (led_index >= NUM_LEDS) {
        // handle error or return a specific value indicating invalid index
        return 0xFF; // For example, returning 0xFF to indicate error
    }

    return (read_leds_status() >> led_index) & 0x01;
}


Remember to adjust `LED_PORT_REG` definition with the correct port register address of your microcontroller. Also, ensure to set `NUM_LEDS` to the correct number of LEDs you're dealing with. If your system has the LEDs spread across different ports or if further bit manipulation is required to read the LED states, you will need to modify the `read_leds_status()` function accordingly.