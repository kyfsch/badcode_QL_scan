#include <stdbool.h>

bool isVlanStp(int vlan) {
    // VLANs that are Stp
    int stpVlans[] = {1, 2, 3, 4, 10};
    int numStpVlans = sizeof(stpVlans) / sizeof(stpVlans[0]);
  
    // Search for the VLAN in the Stp VLANs
    for (int i = 0; i < numStpVlans; i++) {
        if (vlan == stpVlans[i]) {
            return true;
        }
    }
  
    // VLAN is not an Stp VLAN
    return false;
}


The function `isVlanStp` takes an integer parameter `vlan`, which represents the VLAN number to check if it is Stp or not. It returns a boolean value `true` if the VLAN is Stp and `false` otherwise.

The function uses an array `stpVlans` to store the VLAN numbers that are considered as Stp VLANs. The size of `stpVlans` is calculated using the sizeof operator. Then, a loop is used to search for the given VLAN in the `stpVlans` array. If the VLAN is found, the function returns `true`. Otherwise, it returns `false`.