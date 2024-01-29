
void write_rtl839x_register(unsigned int address, unsigned int value) {
    volatile unsigned int *register_ptr = (volatile unsigned int *)address;
    *register_ptr = value;
}

In this function, we take two arguments: the address of the register to write to (as an unsigned integer) and the value to write (also as an unsigned integer). We use a volatile pointer to ensure that the write operation is not optimized away by the compiler.