#include <stdio.h>

struct switch_attributes {
    int id;
    char name[100];
    // Add other attributes here if needed
};

void listSupportedAttributes(struct switch_attributes attributes[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Attribute ID: %d, Name: %s\n", attributes[i].id, attributes[i].name);
    }
}

int main() {
    // Example usage
    struct switch_attributes attributeList[] = {
        {1, "Attribute 1"},
        {2, "Attribute 2"},
        {3, "Attribute 3"}
        // Add more attributes here if needed
    };
    int attributeListSize = sizeof(attributeList) / sizeof(attributeList[0]);

    listSupportedAttributes(attributeList, attributeListSize);