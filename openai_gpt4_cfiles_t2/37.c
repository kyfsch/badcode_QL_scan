#include <stddef.h> /* for NULL definition */

/* Type definition for the callback function */
typedef void (*timer_callback)(void);

/* Global variable to hold the timer callback function */
timer_callback g_timer_callback = NULL;

/* Function to set up the timer callback */
void setup_timer(timer_callback callback) {
    g_timer_callback = callback;
}

/* Function that gets called when the timer has expired */
void timer_expired(void) {
    if (g_timer_callback != NULL) {
        /* Fire the callback */
        g_timer_callback();
    }
}

/* Example callback function */
void example_callback_function(void) {
    /* Implement callback functionality here */
}

/* Example of setting up the callback and simulating the timer expiration */
void example_usage(void) {
    setup_timer(example_callback_function);
    timer_expired(); /* Simulate timer expiration */
}
