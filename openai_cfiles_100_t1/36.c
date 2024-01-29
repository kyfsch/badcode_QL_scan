#include <stdio.h>

// Structure representing the switch device
struct switch_dev {
    // MIB variables
    int mib_variable1;
    int mib_variable2;
    int mib_variable3;
    // ...
};

// Function to get MIB variables from switch_dev structure
int get_mib_variable(const struct switch_dev *dev, int mib_index) {
    int mib_variable = 0;

    switch (mib_index) {
        case 1:
            mib_variable = dev->mib_variable1;
            break;
        case 2:
            mib_variable = dev->mib_variable2;
            break;
        case 3:
            mib_variable = dev->mib_variable3;
            break;
        // Add more cases for other MIB variables if needed
        default:
            printf("Invalid MIB index\n");
            break;
    }

    return mib_variable;
}
