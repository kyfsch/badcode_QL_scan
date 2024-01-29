#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Timer callback function
void timer_callback() {
    printf("Timer expired. Callback fired!\n");
}

// Function to set up a timer
void setup_timer(int seconds) {
    // Create an alarm to fire after the specified number of seconds
    alarm(seconds);
}

int main() {
    int timer_duration = 5; // Timer duration in seconds

    // Set up the timer
    setup_timer(timer_duration);

    // Wait for the timer to expire
    sleep(timer_duration);

    // Call the timer callback function
    timer_callback();

    return 0;
}
