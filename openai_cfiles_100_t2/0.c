#include <stdbool.h>

bool is_register_readable(unsigned int register_address) {
    if (aw9523_is_reg_hole(register_address)) {
        return false;
    }
    // Rest of your code to check register readability
    // ...
}
