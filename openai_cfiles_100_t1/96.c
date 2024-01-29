#include <linux/gpio.h>

void register_gpio_driver(struct gpio_config *config) {
    struct gpio_chip *chip = gpiochip_find_data(config);

    if (chip == NULL) {
        // GPIO chip not found
        return;
    }

    if (config->register_whole_chip) {
        // Register and initialize the entire chip
        gpiochip_add(chip);
        gpiochip_add_pin_ranges(chip, chip->base, chip->ngpio, chip->label);
        gpiochip_add_irqchip(chip);

        // Additional initialization code
        // ...

        return;
    }

    // Register and initialize selectively based on configuration
    for (int i = 0; i < config->num_pins; i++) {
        unsigned int pin = config->pins[i].pin;
        char *label = config->pins[i].label;
        unsigned long flags = config->pins[i].flags;

        if (gpiochip_is_requested(chip, pin)) {
            // Register and initialize the pin
            gpiochip_add_pin_with_key(chip, pin, label);
            gpiochip_add_irqchip(chip);

            // Set additional pin configuration
            gpio_direction_input(chip, pin);
            if (flags & GPIO_ACTIVE_LOW) {
                gpio_set_active_low(chip, pin, 1);
            }
            if (flags & GPIO_OPEN_DRAIN) {
                gpio_set_open_drain(chip, pin, 1);
            }
            // ...
        }
    }
}


In the above code, `struct gpio_config` is a user-defined structure that holds the GPIO configuration for the device. It contains the necessary fields to determine the GPIO chip and the pins to be registered. The `gpiochip_find_data()` function is used to find the GPIO chip based on the configuration data.

The `register_gpio_driver()` function first checks whether to register and initialize the entire chip (`register_whole_chip` field in the `config` structure). If set to `true`, it registers the entire chip using `gpiochip_add()`, adds pin ranges using `gpiochip_add_pin_ranges()`, and adds the IRQ chip using `gpiochip_add_irqchip()`.

If `register_whole_chip` is set to `false`, the function iterates over the pins specified in the `num_pins` and `pins` fields of the `config` structure. For each pin, it checks whether the pin is requested (`gpiochip_is_requested()`). If requested, it registers the pin using `gpiochip_add_pin_with_key()` and adds the IRQ chip using `gpiochip_add_irqchip()`.

Finally, additional pin configuration options can be set based on the `flags` field in the `config` structure. The example code demonstrates setting the pin direction as an input and enabling the active-low and open-drain configurations.