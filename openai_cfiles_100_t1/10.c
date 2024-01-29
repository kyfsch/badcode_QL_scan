#include <stdio.h>

#define MAX_PORTS 8

// Function to set member and untag ports of a VLAN
void setVlanPorts(int vlanId, int* memberPorts, int* untagPorts, int numMemberPorts, int numUntagPorts) {
    // Code to set member ports
    printf("Setting member ports for VLAN %d: ", vlanId);
    for (int i = 0; i < numMemberPorts; i++) {
        printf("%d ", memberPorts[i]);
    }
    printf("\n");
    
    // Code to set untag ports
    printf("Setting untag ports for VLAN %d: ", vlanId);
    for (int i = 0; i < numUntagPorts; i++) {
        printf("%d ", untagPorts[i]);
    }
    printf("\n");
}

int main() {
    int vlanId = 10;
    int memberPorts[MAX_PORTS] = {1, 2, 3, 4};
    int untagPorts[MAX_PORTS] = {1, 3};
    int numMemberPorts = 4;
    int numUntagPorts = 2;

    setVlanPorts(vlanId, memberPorts, untagPorts, numMemberPorts, numUntagPorts);

    return 0;
}


In the `setVlanPorts` function, you can replace the `printf` statements with the actual code to set the member and untag ports of the VLAN on your embedded system. The function takes the `vlanId` as an input along with the arrays `memberPorts` and `untagPorts` which store the port numbers. The `numMemberPorts` and `numUntagPorts` variables signify the number of ports in the respective arrays.