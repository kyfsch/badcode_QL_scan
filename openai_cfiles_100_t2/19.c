#include <stdbool.h>

bool isStpVlan(int vlanId) {
    // Assuming VLAN IDs are stored in an array named 'vlanIds'
    int vlanIds[] = {1, 2, 3, 4, 5}; // Add your VLAN IDs here

    int numVlans = sizeof(vlanIds) / sizeof(vlanIds[0]);

    for (int i = 0; i < numVlans; i++) {
        if (vlanIds[i] == vlanId) {
            // Assuming Stp VLANs are stored in an array named 'stpVlans'
            int stpVlans[] = {2, 4}; // Add your Stp VLAN IDs here

            int numStpVlans = sizeof(stpVlans) / sizeof(stpVlans[0]);

            for (int j = 0; j < numStpVlans; j++) {
                if (stpVlans[j] == vlanId) {
                    return true;
                }
            }

            return false;
        }
    }

    return false;
}


You can modify the arrays `vlanIds` and `stpVlans` according to your specific VLANs. The function `isStpVlan` takes an integer parameter `vlanId` and checks if it exists in the `vlanIds` array and if it is also present in the `stpVlans` array. It returns `true` if the VLAN is an Stp VLAN, and `false` otherwise.