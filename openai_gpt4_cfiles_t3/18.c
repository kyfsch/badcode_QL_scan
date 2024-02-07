#include <stdint.h> // for uint32_t definition

#define VALID_TIMER_VALUE_SECONDS 60 // Assuming 60 seconds is a valid timer default value

// Function to set the age-out timer in seconds
void setAgeOutTimer(uint32_t *timer, uint32_t seconds) {
    // Check if the timer pointer is valid before attempting to update it
    if (timer != NULL) {
        // Further checks can be added here to validate 'seconds' if needed
        *timer = seconds;
    }
}