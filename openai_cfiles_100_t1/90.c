
int readRegisterWithFilter(uint32_t* registerValue) {
    // Read the register value
    *registerValue = readRegister();
    
    // Apply logic to the register value
    if (*registerValue > 100) {
        *registerValue = 100;
    } else if (*registerValue < 0) {
        *registerValue = 0;
    }
    
    return 0; // Operation completed successfully
}
