#include <stdint.h>

/* I/O port writing function for your specific platform */
void io_write(uint16_t port, uint8_t value) {
    /* Assuming outb is available on your platform or implement your own */
    outb(value, port);
}


To use this function, you just call `io_write` with the port number and the value you want to write. If `outb` is not available for your embedded system, you would need to replace it with the appropriate function or mechanism for writing to I/O ports for your specific hardware.