#include <stdio.h>
#include <string.h>

#define NUMBER_OF_MAPPINGS 5  // Define the number of mappings. Adjust as needed.

// Define a structure for mapping names.
typedef struct {
    const char *name;
    int value;  // This could represent anything associated with the name.
} PlatformMapping;

// Initialize an array of platform mappings.
PlatformMapping platformMappings[NUMBER_OF_MAPPINGS] = {
    {"MAP_NAME_1", 1},
    {"MAP_NAME_2", 2},
    {"MAP_NAME_3", 3},
    {"MAP_NAME_4", 4},
    {"MAP_NAME_5", 5}
};

// Function to match mapping names.
int matchMappingName(const char *name) {
    for(int i = 0; i < NUMBER_OF_MAPPINGS; ++i) {
        if(strcmp(platformMappings[i].name, name) == 0) {
            return i;  // Return the index of the matched name.
        }
    }

    return -1; // Return -1 if no match was found.
}

// Example of usage
int main() {
    const char *inputName = "MAP_NAME_3";
    int index = matchMappingName(inputName);

    if (index != -1) {
        printf("Found '%s' with index: %d and value: %d\n", inputName, index, platformMappings[index].value);
    } else {
        printf("Mapping name '%s' not found.\n", inputName);
    }

    return 0;
}
