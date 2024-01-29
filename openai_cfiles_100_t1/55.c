#include <stdbool.h>

bool is_register_writeable(int reg)
{
    // List of writeable registers in AW9523
    const int writeable_registers[] = {
        /* Define the writeable registers here */
        /* For example: */
        0x00, // Register 0
        0x01, // Register 1
        0x02  // Register 2
    };
    
    // Calculate the length of the writeable_registers array
    int num_registers = sizeof(writeable_registers) / sizeof(writeable_registers[0]);
    
    // Check if the given register is in the writeable_registers array
    for (int i = 0; i < num_registers; i++) {
        if (reg == writeable_registers[i]) {
            return true;
        }
    }
    
    return false;
}


In this function, you can add the writeable registers specific to the AW9523 chip by defining them in the `writeable_registers` array. The function then checks if the given `reg` value is present in the array, and returns `true` if it is writeable, or `false` otherwise.