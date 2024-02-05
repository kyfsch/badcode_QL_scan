#include <stdint.h>

// Define the base address and bit position for the ACL GPIO polarity control
// You should define the actual base address and bit mask for your specific hardware.
#define IGR_ACL_GPIO_BASE_ADDRESS 0x40021000  // Example base address, replace with actual
#define IGR_ACL_GPIO_POLARITY_BIT 0x00000001  // Example bit position, replace with actual

// Define a volatile pointer to the IGR ACL GPIO register for direct register access
volatile uint32_t* const IGR_ACL_GPIO_POLARITY_REGISTER = (volatile uint32_t*)(IGR_ACL_GPIO_BASE_ADDRESS + /* Offset to polarity register */);

// Function prototypes
void modify_igr_acl_gpio_polarity(uint32_t polarity);
void reset_igr_acl_gpio_polarity(void);

// Function to modify IGR ACL GPIO polarity
void modify_igr_acl_gpio_polarity(uint32_t polarity) {
    if (polarity) {
        // Set GPIO interrupt polarity to high
        *IGR_ACL_GPIO_POLARITY_REGISTER |= IGR_ACL_GPIO_POLARITY_BIT;
    } else {
        // Set GPIO interrupt polarity to low
        *IGR_ACL_GPIO_POLARITY_REGISTER &= ~IGR_ACL_GPIO_POLARITY_BIT;
    }
}

// Function to reset IGR ACL GPIO polarity
void reset_igr_acl_gpio_polarity(void) {
    // Reset GPIO interrupt polarity to a known default, for example, low
    *IGR_ACL_GPIO_POLARITY_REGISTER &= ~IGR_ACL_GPIO_POLARITY_BIT;
}


The `modify_igr_acl_gpio_polarity` function takes a `polarity` argument that determines the desired polarity. If `polarity` is nonzero, the GPIO interrupt polarity is set to high; otherwise, it's set to low. The `reset_igr_acl_gpio_polarity` function resets the polarity to a default state, which in this case is assumed to be low.