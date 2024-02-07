#include <stdint.h>
#include <stdbool.h>

// Enumeration for pin configuration parameters
typedef enum
{
    INPUT_MODE,
    OUTPUT_MODE,
    INTERRUPT_MODE
} pin_config_param_t;

// I2C read function prototype required by the AW9523 driver
// Implement this according to your platform's I2C API
bool aw9523_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

// Function to extract the configuration of a specified pin from the AW9523 device
// pin_number: 0 to the maximum pin number supported by the device
// config_param: the configuration parameter to extract for the specified pin
// config_value: a pointer to the variable where the extracted value will be stored
// Returns true on success and false on any error
bool aw9523_get_pin_config(uint8_t pin_number, pin_config_param_t config_param, uint8_t *config_value)
{
    if (config_value == NULL)
    {
        return false;
    }

    // Define device-specific values
    uint8_t AW9523_ADDR = 0x58; // Example I2C address of the AW9523, may vary based on hardware
    uint8_t INPUT_REG_BASE = 0x00; // Base register for input mode
    uint8_t OUTPUT_REG_BASE = 0x02; // Base register for output mode
    uint8_t INTERRUPT_REG_BASE = 0x04; // Base register for interrupt mode
    uint8_t REG_SIZE = 2; // Register size (in bytes) for port configuration
    
    // Calculate register address and bit position based on pin number
    uint8_t reg_addr = 0;
    uint8_t bit_pos = pin_number % 8; // Each register handles 8 pins
    uint8_t reg_offset = pin_number / 8; // Determine which register (0 or 1) the pin is in

    // Select the correct base address for the provided configuration parameter
    switch (config_param)
    {
        case INPUT_MODE:
            reg_addr = INPUT_REG_BASE + reg_offset;
            break;
        case OUTPUT_MODE:
            reg_addr = OUTPUT_REG_BASE + reg_offset;
            break;
        case INTERRUPT_MODE:
            reg_addr = INTERRUPT_REG_BASE + reg_offset;
            break;
        default:
            return false; // Invalid configuration parameter
    }

    // Read the current configuration register
    uint8_t reg_data[REG_SIZE] = {0};
    if (!aw9523_i2c_read(AW9523_ADDR, reg_addr, reg_data, REG_SIZE))
    {
        return false; // I2C read error
    }

    // Extract the relevant bit of the pin's configuration
    if (config_param == INPUT_MODE || config_param == OUTPUT_MODE)
    { 
        // For INPUT_MODE and OUTPUT_MODE, configuration requires 2 bytes read
        // Check pin number to select proper byte
        *config_value = (reg_data[pin_number / 8] >> bit_pos) & 0x01;
    }
    else if (config_param == INTERRUPT_MODE)
    {
        // For INTERRUPT_MODE, only one byte read is required
        *config_value = (reg_data[0] >> bit_pos) & 0x01;
    }
    else
    {
        return false; // This case is already handled earlier but kept for completeness
    }