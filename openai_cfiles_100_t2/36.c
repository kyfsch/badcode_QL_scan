#include <stdio.h>

// Assume the switch_dev structure looks something like this
struct switch_dev {
    int mib_var1;
    int mib_var2;
    // ... other variables
};

int get_mib_variable(struct switch_dev sd, int mib_var_index) {
    int mib_value = 0;

    switch (mib_var_index) {
        case 1:
            mib_value = sd.mib_var1;
            break;
        case 2:
            mib_value = sd.mib_var2;
            break;
        // ... add more cases for other MIB variables
        default:
            printf("Invalid MIB variable index!");
            break;
    }

    return mib_value;
}
