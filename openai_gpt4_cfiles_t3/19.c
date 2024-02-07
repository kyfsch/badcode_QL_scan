#include <stdbool.h>

/* Define a structure to represent a VLAN. */
typedef struct {
    int vlanId;     /* VLAN identifier. */
    bool isStp;     /* Flag indicating if STP is enabled for the VLAN. */
    // You can add additional VLAN attributes here.
} VLAN;

/* Example VLAN database - this should normally be dynamically managed. */
#define VLAN_COUNT 5
VLAN vlanDatabase[VLAN_COUNT] = {
    {100, true},
    {200, false},
    {300, true},
    {400, false},
    {500, true}
};

/**
 * @brief Search for a VLAN to see if it is running STP or not.
 * @param vlanId The VLAN identifier to search for.
 * @return true if the VLAN is running STP, false otherwise, or if VLAN not found.
 */
bool isVlanStpEnabled(int vlanId) {
    for (int i = 0; i < VLAN_COUNT; i++) {
        if (vlanDatabase[i].vlanId == vlanId) {
            return vlanDatabase[i].isStp;
        }
    }
    return false; // Return false if VLAN not found
}

// The function `isVlanStpEnabled` could be used like this:
// bool stpStatus = isVlanStpEnabled(300);


This code defines a `VLAN` structure type to represent a VLAN with its corresponding STP status. It also initializes a sample database of VLANs (`vlanDatabase`). The function `isVlanStpEnabled` then searches this database for a VLAN by its `vlanId` and returns its STP status.