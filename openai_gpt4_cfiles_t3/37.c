#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// Define a callback function type
typedef void (*TimerCallback)(void);

// Timer struct to encapsulate state
typedef struct {
    time_t start;
    unsigned int duration;
    TimerCallback callback;
    bool is_active;
} Timer;

// Function to initialize the timer
void setupTimer(Timer *timer, unsigned int duration, TimerCallback callback) {
    if (timer == NULL || callback == NULL) return;
    
    timer->start = time(NULL);
    timer->duration = duration;
    timer->callback = callback;
    timer->is_active = true;
}

// Function to check the timer and fire the callback if the time has elapsed
void checkAndFireTimer(Timer *timer) {
    // Verify that the timer is active and has been set up properly
    if (timer == NULL || timer->callback == NULL || !timer->is_active) {
        return;
    }

    // Check if the duration has passed
    if ((time(NULL) - timer->start) >= timer->duration) {
        timer->callback(); // Fire the callback
        timer->is_active = false; // Disable the timer after the callback has been fired
    }
}

// Example of a callback function
void onTimerExpired(void) {
    printf("Timer expired!\n");
}

// Main function, demonstrating a simple example of how to use the timer
int main(void) {
    Timer myTimer;
    
    // Setup the timer for 5 seconds and assign the callback function
    setupTimer(&myTimer, 5, onTimerExpired);
    
    // Dummy loop to imitate a program's execution over time
    while (myTimer.is_active) {
        checkAndFireTimer(&myTimer);
        
        // Simulate doing other work
        sleep(1);
    }
    
    return 0;
}
