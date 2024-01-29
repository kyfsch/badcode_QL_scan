#include <stdio.h>

struct switch_attributes {
    int id;
    const char* name;
    // other attributes
};

void listSupportedAttributes(const struct switch_attributes* attrList, int attrCount) {
    for (int i = 0; i < attrCount; i++) {
        printf("Attribute ID: %d, Name: %s\n", attrList[i].id, attrList[i].name);
        // print other attributes if required
    }
}

int main() {
    // Example usage
    struct switch_attributes attributeList[] = {
        {1, "Attribute1"},
        {2, "Attribute2"},
        {3, "Attribute3"},
        // add more attributes
    };

    int attributeCount = sizeof(attributeList) / sizeof(attributeList[0]);

    listSupportedAttributes(attributeList, attributeCount);

    return 0;
}


In this code, the `listSupportedAttributes` function takes an array of `struct switch_attributes` as input, along with the total number of attributes. It then iterates over the array and prints the attribute ID and name using `printf`. You can add more attributes to the `attributeList` array and specify the number of attributes accordingly.