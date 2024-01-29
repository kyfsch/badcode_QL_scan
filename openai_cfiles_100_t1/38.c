
void togglePortMirroring(int asicId, int portId, int enable) {
    // Check if portId is valid for the given Asic
    if (portId < 1 || portId > MAX_PORTS_PER_ASIC) {
        printf("Invalid portId\n");
        return;
    }
    
    // Disable or enable port mirroring
    if (enable) {
        // Enable port mirroring on the specified port
        printf("Enabling port mirroring on Asic %d, port %d\n", asicId, portId);
        // Your code to enable port mirroring goes here
    } else {
        // Disable port mirroring on the specified port
        printf("Disabling port mirroring on Asic %d, port %d\n", asicId, portId);
        // Your code to disable port mirroring goes here
    }
}
