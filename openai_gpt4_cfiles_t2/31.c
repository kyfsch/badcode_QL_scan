#include <stdio.h>

// Assuming there's a predefined structure for the VLAN profile
typedef struct {
    int index;
    char name[32];
    int status; // assuming 0 for inactive, 1 for active
    // Add more fields as necessary for your VLAN information
} vlan_profile_t;

// Assuming there's an external system function to fill a vlan_profile structure
// based on a given VLAN index. We're declaring it here to avoid compiler errors.
// Please replace it with the actual system function.
int get_vlan_info(int index, vlan_profile_t *profile);

// The function to dump VLAN profile information
void dump_vlan_profile(int index) {
    vlan_profile_t profile;
    
    // Get VLAN profile based on index
    if(get_vlan_info(index, &profile)) {
        printf("VLAN Profile:\n");
        printf("Index: %d\n", profile.index);
        printf("Name: %s\n", profile.name);
        printf("Status: %s\n", profile.status ? "Active" : "Inactive");
        // Dump other fields as necessary
    } else {
        printf("Failed to get VLAN information for index %d\n", index);
    }
}


You'll need to replace `get_vlan_info` function with the actual function available in your system to retrieve VLAN information and also adjust the `vlan_profile_t` structure according to the real VLAN profile structure you have.