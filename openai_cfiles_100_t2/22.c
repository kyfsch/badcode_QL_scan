#include <stdint.h>

// Define the enum pin_config_param
typedef enum {
    CONFIG_PARAM_1,
    CONFIG_PARAM_2,
    CONFIG_PARAM_3,
    // Add more configurations as needed
} pin_config_param;

// Function to extract configuration value from AW9523 device
uint8_t extract_config_value(pin_config_param config_param, uint8_t pin) {
    // Assume code to extract configuration value from the device
    
    // Here's a sample implementation
    uint8_t config_value = 0;
    
    switch (config_param) {
        case CONFIG_PARAM_1:
            // Extract config value for CONFIG_PARAM_1 from the device
            // You may need to use the pin parameter to determine the specific pin configuration
            config_value = 1;
            break;
        case CONFIG_PARAM_2:
            // Extract config value for CONFIG_PARAM_2 from the device
            // You may need to use the pin parameter to determine the specific pin configuration
            config_value = 2;
            break;
        case CONFIG_PARAM_3:
            // Extract config value for CONFIG_PARAM_3 from the device
            // You may need to use the pin parameter to determine the specific pin configuration
            config_value = 3;
            break;
        default:
            // Handle invalid config_param value here
            break;
    }
    
    return config_value;
}
