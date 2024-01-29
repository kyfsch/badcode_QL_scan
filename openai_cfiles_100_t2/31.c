
void dump_vlan_profile(int index) {
    // Assume there is a struct called "VlanProfile" that holds VLAN profile information
    struct VlanProfile {
        int id;
        char name[32];
        int priority;
        // ...
    };

    // Create an array of VlanProfile structs to store VLAN profile information
    struct VlanProfile profiles[] = {
        { 1, "VLAN1", 1 },
        { 2, "VLAN2", 2 },
        { 3, "VLAN3", 3 },
        // ...
    };

    // Check if the index is valid
    if (index >= 0 && index < sizeof(profiles) / sizeof(profiles[0])) {
        // Print the information of the specified VLAN profile
        printf("VLAN ID: %d\n", profiles[index].id);
        printf("VLAN Name: %s\n", profiles[index].name);
        printf("VLAN Priority: %d\n", profiles[index].priority);

        // Add more printf statements to display other VLAN profile information
    } else {
        printf("Invalid VLAN index\n");
    }
}
