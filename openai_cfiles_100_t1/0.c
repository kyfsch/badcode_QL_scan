#include <stdbool.h>

bool is_register_readable(unsigned int reg) {
    if (aw9523_is_reg_hole(reg)) {
        return false;
    }
    else {
        // check if the register is readable
        // add your code here to check the register's readability
        
        // return true if the register is readable
        // otherwise, return false
    }
}
