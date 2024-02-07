#include <stdint.h>
#include <stdbool.h>

/* Assume there's a system-specific function to set a timer which we can call */
extern bool set_system_timer(uint32_t timer_value);

/* Function to set the age-out timer */
bool set_age_out_timer(uint32_t age_out_seconds) {
    /* Call system-specific function to set the timer */
    bool result = set_system_timer(age_out_seconds);
    
    return result;
}


To use the `set_age_out_timer` function, you would call it with the desired number of seconds like so:

c
uint32_t age_out_time = 30; // Set the age-out timer to 30 seconds
bool success = set_age_out_timer(age_out_time);

if (success) {
    // Timer was set successfully
} else {
    // There was an error setting the timer
}
