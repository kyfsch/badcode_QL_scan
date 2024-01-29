#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*Callback)(void);

void timer_handler(int sig) {
    // Callback function can be called here
    // Implement the desired behavior inside this function
    printf("Timer expired. Calling callback...\n");
}

void start_timer(int timeout, Callback callback) {
    // Register the signal handler for the timer
    signal(SIGALRM, timer_handler);

    // Set the timer
    alarm(timeout);

    // Sleep to wait for the timer to expire
    sleep(timeout);

    // Call the callback function
    callback();
}

void callback_function() {
    // Do something inside the callback function
    printf("Callback is called!\n");
}

int main() {
    // Start the timer with 3 seconds timeout and the callback function
    start_timer(3, callback_function);

    return 0;
}


Note that this example uses the `signal()` function from `signal.h` to handle the timer expiration event. The `alarm()` function is used to set the timer, and `sleep()` is used to block the main thread until the timer expires. In a real-world application, timers are usually implemented using hardware timers or the operating system's timer mechanisms.