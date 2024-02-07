#include <stdint.h>
#include <stdbool.h>

/* Assuming the signature of rtl9300_i2c_write is known and might look something like this */
bool rtl9300_i2c_write(uint8_t device_address, uint8_t register_address, uint8_t *data, uint8_t length);