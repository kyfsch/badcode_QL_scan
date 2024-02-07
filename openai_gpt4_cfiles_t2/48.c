#include <stdint.h>

/* Assuming a global log counter */
int log_counter = 0;

/**
 * Sets the logging counter to the specified value.
 *
 * @param value The value to set the logging counter to.
 */
void setLogCounter(int value) {
    log_counter = value;
}


In this example, `log_counter` is a global variable that represents the counter and `setLogCounter` is the function that sets this counter to the provided `value`. The `#include <stdint.h>` is present to ensure that integer types are defined properly according to the C99 standard; however, since we're only using `int` here, it's optional.