#include <stdint.h>

// Assume that the I2C read function and AW9523 address are defined elsewhere
#define AW9523_ADDR 0x58 // Example I2C address for AW9523

// The function for reading from the device, to be implemented as per your I2C library
extern uint8_t AW9523_read_register(uint8_t device_addr, uint8_t reg_addr);

// Define various registers related to pins configuration
#define INPUT0_REG    0x00 // Input register for Port 0
#define INPUT1_REG    0x01 // Input register for Port 1
#define OUTPUT0_REG   0x02 // Output register for Port 0
#define OUTPUT1_REG   0x03 // Output register for Port 1
#define CONFIG0_REG   0x04 // Configuration register for Port 0
#define CONFIG1_REG   0x05 // Configuration register for Port 1

typedef enum {
    PIN_CONFIG_INPUT, // The configuration is set as input
    PIN_CONFIG_OUTPUT // The configuration is set as output
} pin_config_param;

typedef enum {
    PORT0_PIN0, // Port 0, Pin 0
    PORT0_PIN1, // Port 0, Pin 1
    // ... continue for all relevant pins
    PORT1_PIN7  // Port 1, Pin 7
} pin_t;

//  Function to get the configuration of a pin on the AW9523 device
uint8_t get_pin_config(AW9523_ADDR_t device_addr, pin_t pin, pin_config_param param) {
    uint8_t reg_value = 0;
    uint8_t mask = 1 << (pin % 8); // Mask for the specific pin
    uint8_t reg_addr = (pin < PORT0_PIN0) ? CONFIG0_REG : CONFIG1_REG;
    
    reg_value = AW9523_read_register(device_addr, reg_addr);

    switch (param) {
        case PIN_CONFIG_INPUT:
            // The pin is configured as input if the bit is 1
            return (reg_value & mask) ? 1 : 0;
            
        case PIN_CONFIG_OUTPUT:
            // The pin is configured as output if the bit is 0
            return (reg_value & mask) ? 0 : 1;

        default:
            return 0xFF; // Indicate that an unknown parameter was provided
    }
}


Please note that this example is quite simplified and assumes the use of an 8-bit register for port configuration. You may need to adjust the register addresses, I2C read function, and bit manipulation code to suit the specifics of the AW9523 device and the I2C library you are using.