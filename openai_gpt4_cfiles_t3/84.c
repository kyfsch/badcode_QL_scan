#include <stdint.h> // For uint8_t, uint32_t, etc.

// Define the base address for the switch's port registers
// This address would be provided by the switch's datasheet or hardware spec.
#define SWITCH_PORTS_BASE_ADDRESS 0x40001000

// Define the offset for each port's control register
// These are just example values; replace them with your switch's actual register offsets.
#define PORT_REGISTER_OFFSET 0x04

// Define the number of ports
#define NUMBER_OF_PORTS 8

// This is a pointer to the base address for the switch ports.
// The volatile keyword is used to ensure each write is actually performed,
// as these are memory-mapped I/O registers.
volatile uint8_t* const switch_ports = (volatile uint8_t*)SWITCH_PORTS_BASE_ADDRESS;

/**
 * @brief Sets the designated port on the switch to the given state.
 * 
 * @param port The port number to set (between 0 and NUMBER_OF_PORTS - 1).
 * @param state The state to set the port to. Typically, 0 (off) or 1 (on).
 */
void setPortState(uint8_t port, uint8_t state) {
    if (port < NUMBER_OF_PORTS && (state == 0 || state == 1)) {
        // Compute the address of the port's control register.
        volatile uint8_t* port_register = switch_ports + (PORT_REGISTER_OFFSET * port);

        // Set the port state.
        *port_register = state;
    }
}
 

Replace the `SWITCH_PORTS_BASE_ADDRESS`, `PORT_REGISTER_OFFSET`, and `NUMBER_OF_PORTS` with the actual values for your specific switch hardware. The above function assumes that writing a `0` or `1` to the port's address will turn that port off or on, respectively.