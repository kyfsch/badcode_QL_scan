#include <stdint.h>

// Assuming GPIO base addresses and pin numbers are defined somewhere
#define GPIO1_BASE  0x4804C000
#define GPIO1_PIN_MASK (1UL << 12) // Replace 12 with the actual GPIO PIN number
#define GPIO2_BASE  0x4804C000 
#define GPIO2_PIN_MASK (1UL << 13) // Replace 13 with the actual GPIO PIN number

// GPIO registers offset (Assuming a common offset used for GPIO input data)
#define GPIO_DATAIN_OFFSET 0x138

typedef struct {
    uint32_t DATAIN;
} GPIO_Regs;

// Function to initialize GPIO pointers
// This would need to setup pointers to the GPIO DATAIN registers
void initGPIO(GPIO_Regs **gpio1, GPIO_Regs **gpio2) 
{
    *gpio1 = (GPIO_Regs *)(GPIO1_BASE + GPIO_DATAIN_OFFSET);
    *gpio2 = (GPIO_Regs *)(GPIO2_BASE + GPIO_DATAIN_OFFSET);
}

// Function to read the status of two GPIOs
void getGPIOStatus(uint8_t *gpio1_status, uint8_t *gpio2_status)
{
    GPIO_Regs *gpio1;
    GPIO_Regs *gpio2;
    
    initGPIO(&gpio1, &gpio2);

    // Read the status of GPIO 1
    if (gpio1->DATAIN & GPIO1_PIN_MASK) {
        *gpio1_status = 1;
    } else {
        *gpio1_status = 0;
    }

    // Read the status of GPIO 2
    if (gpio2->DATAIN & GPIO2_PIN_MASK) {
        *gpio2_status = 1;
    } else {
        *gpio2_status = 0;
    }
}

