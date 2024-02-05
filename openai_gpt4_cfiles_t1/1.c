#include <stdio.h>
#include <string.h>

// Define a PlatformMapping struct
typedef struct {
    int key;        // An integer key used to identify the platform
    const char* name; // The name of the platform associated with the key
} PlatformMapping;

// A function to initialize the platform mappings
PlatformMapping* get_platform_mappings(int *count) {
    static PlatformMapping mappings[] = {
        {1, "Platform_A"},
        {2, "Platform_B"},
        {3, "Platform_C"}
        // Add more mappings as required
    };
    *count = sizeof(mappings) / sizeof(mappings[0]);
    return mappings;
}

// A function to match the platform name based on the provided key
const char* match_platform_name(int key) {
    int platform_count = 0;
    PlatformMapping* mappings = get_platform_mappings(&platform_count);

    for (int i = 0; i < platform_count; ++i) {
        if (mappings[i].key == key) {
            return mappings[i].name;
        }
    }
    return NULL; // Return NULL if no matching platform is found
}

// Example usage:
// The caller must check if the result is not NULL before using the returned name pointer.
// const char* platform_name = match_platform_name(2);
// if (platform_name != NULL) {
//    printf("Found platform: %s\n", platform_name);
// } else {
//    printf("Platform not found\n");
// }


In this example, `PlatformMapping` is a custom data type you define to hold the mapping between keys and platform names. `get_platform_mappings` is a helper function to initialize an internal static array of mapping records. `match_platform_name` is the function that performs the actual lookup. This function iterates through the available mapping records and returns the corresponding `name` when the `key` matches. If no matching key is found, it returns `NULL`. 