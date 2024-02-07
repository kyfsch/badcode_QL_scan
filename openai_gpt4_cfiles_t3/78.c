#include <stdio.h>

#define MAX_ATTRIBUTES 10 // You should adjust this to the actual number of attributes

// Example definition of `struct switch_attributes`
typedef struct switch_attributes {
    int id;     // unique identifier for the attribute
    char name[50]; // name of the attribute
} switch_attributes;

// Function to list all of the supported attributes
void list_supported_attributes(const switch_attributes attributes[], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf("Attribute ID: %d, Name: %s\n", attributes[i].id, attributes[i].name);
    }
}

// Example usage of the function
int main() {
    // Initialize an array of attributes
    switch_attributes attribute_list[MAX_ATTRIBUTES] = {
        {1, "Attribute1"},
        {2, "Attribute2"},
        // ... other attributes
    };
    
    // Assuming that we've initialized 2 attributes for demonstration
    size_t attribute_count = 2;

    // Call the function to list attributes
    list_supported_attributes(attribute_list, attribute_count);

    return 0;
}
