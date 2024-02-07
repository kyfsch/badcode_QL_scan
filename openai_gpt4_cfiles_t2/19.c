#include <stdbool.h>

#define MAX_VLANS 256 // Assume a maximum of 256 VLANs for this example

// Struct representing a VLAN with its STP status
typedef struct {
    int vlanId;
    bool isStpEnabled;
} VlanInfo;

// Array of VLANs and their STP status
VlanInfo vlanList[MAX_VLANS] = {
    // Populate this list with actual VLAN and STP status data
    {100, true}, // Assuming VLAN 100 is STP enabled
    {200, false}, // Assuming VLAN 200 is not STP enabled
    // Add more VLANs as needed...
};

// The function to search for a VLAN's STP status
bool isVlanStpEnabled(int vlanId) {
    for (int i = 0; i < MAX_VLANS; i++) {
        if (vlanList[i].vlanId == vlanId) {
            return vlanList[i].isStpEnabled;
        }
    }
    return false; // If VLAN is not found, assume STP is not enabled
}


This function, `isVlanStpEnabled`, iterates through the list of VLANs and checks if the given VLAN ID matches any ID in the `vlanList`. If it finds a match, it returns the STP status of that VLAN. If the VLAN ID is not found in the list, the function returns `false`, assuming that STP is not enabled for VLANs not listed.