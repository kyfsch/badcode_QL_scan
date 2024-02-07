#include <stdint.h>

// Define the address of the GPIO polarity control register
#define GPIO_POLARITY_REGISTER_ADDR 0x4000

// Define the default polarity for the GPIO
#define GPIO_DEFAULT_POLARITY 0x01

// Function to modify the GPIO polarity
void set_IGR_ACL_GPIO_Polarity(uint8_t polarity) {
    volatile uint8_t *gpio_polarity_register = (volatile uint8_t *)GPIO_POLARITY_REGISTER_ADDR;
    *gpio_polarity_register = polarity;
}

// Function to reset the GPIO polarity to the system default
void reset_IGR_ACL_GPIO_Polarity(void) {
    set_IGR_ACL_GPIO_Polarity(GPIO_DEFAULT_POLARITY);
}

// Example usage of the functions
int main(void) {
    // User modifies the GPIO polarity
    set_IGR_ACL_GPIO_Polarity(0xFF);

    // Perform operations...

    // System resets the GPIO polarity
    reset_IGR_ACL_GPIO_Polarity();

    return 0;
}
