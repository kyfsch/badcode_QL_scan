#include <stdint.h>

#define SPROM_MAX_LEN 256

typedef struct {
    uint8_t version;
    uint8_t revision;
    uint32_t device_id;
    // add more fields as needed
} sprom_data_t;

void fill_sprom_data(sprom_data_t *sprom)
{
    // Fill the sprom data structure with initialization values
    sprom->version = 1;
    sprom->revision = 1;
    sprom->device_id = 0xDEADBEEF;
    // set other fields as needed
}

int main()
{
    sprom_data_t sprom;
    fill_sprom_data(&sprom);

    // Use the filled sprom data structure as needed

    return 0;
}


In this example, the `sprom_data_t` structure is defined to hold the required fields for the SPI sprom data. The `fill_sprom_data()` function takes a pointer to a `sprom_data_t` structure and fills it with initialization values. You can add more fields to the structure as needed.

In the `main()` function, a `sprom_data_t` variable named `sprom` is defined. The `fill_sprom_data()` function is then called with a pointer to `sprom` to fill it with the initialization values.