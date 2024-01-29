#include "/kernel/drivers/net/ethernet/realtek/816.h"

void write_register(uintptr_t reg_addr, uint32_t value) {
    *(volatile uint32_t*)reg_addr = value;
}


Assuming that the `reg_addr` is the address of the register in the IPE chip and `value` is the value to be written to that register. The function uses a volatile pointer cast to ensure that the write operation is not optimized away by the compiler.