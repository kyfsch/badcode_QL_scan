#include <stdio.h>

/* Define the struct switch_attributes assuming it has an id and a name */
typedef struct switch_attributes {
    int id;     // attribute ID
    char *name; // attribute name
} switch_attributes_t;

/* Assume a fixed size for the attribute list for demonstration purposes */
#define ATTRIBUTE_LIST_SIZE 10

/* Function prototype */
void list_attributes(const switch_attributes_t attr_list[], int size);

/* Your function definition */
void list_attributes(const switch_attributes_t attr_list[], int size) {
    for(int i = 0; i < size; ++i) {
        printf("Attribute ID: %d, Attribute Name: %s\n", attr_list[i].id, attr_list[i].name);
    }
}

/* Example usage of the function */
int main() {
    /* Example list of attributes */
    switch_attributes_t attributes[ATTRIBUTE_LIST_SIZE] = {
        {1, "Attribute 1"},
        {2, "Attribute 2"},
        // ... initializations for other attributes
    };

    /* Call the function to list attributes */
    list_attributes(attributes, ATTRIBUTE_LIST_SIZE);

    return 0;
}
