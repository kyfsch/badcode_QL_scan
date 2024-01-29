#include <stdio.h>

typedef enum {
    CPUFWD,
    CPUFWD2,
    CPUFWD3,
    PARFWDCPU,
    DSPFWDCPU
} VlanOamMode;

void setVlanOamMode(VlanOamMode mode) {
    switch (mode) {
        case CPUFWD:
            printf("Setting VLAN OAM mode to CPUFWD\n");
            // code to set VLAN OAM mode to CPUFWD
            break;
        case CPUFWD2:
            printf("Setting VLAN OAM mode to CPUFWD2\n");
            // code to set VLAN OAM mode to CPUFWD2
            break;
        case CPUFWD3:
            printf("Setting VLAN OAM mode to CPUFWD3\n");
            // code to set VLAN OAM mode to CPUFWD3
            break;
        case PARFWDCPU:
            printf("Setting VLAN OAM mode to PARFWDCPU\n");
            // code to set VLAN OAM mode to PARFWDCPU
            break;
        case DSPFWDCPU:
            printf("Setting VLAN OAM mode to DSPFWDCPU\n");
            // code to set VLAN OAM mode to DSPFWDCPU
            break;
        default:
            printf("Invalid VLAN OAM mode\n");
            break;
    }
}

int main() {
    setVlanOamMode(CPUFWD);    // Example usage
    return 0;
}
