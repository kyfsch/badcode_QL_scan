#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assume gstr is a global string variable
char gstr[] = "Sample String";

// Function prototype
char* get_gstr_copy(void);

// main function for demonstration purposes
int main() {
    char *str_copy = get_gstr_copy();
    if (str_copy) {
        printf("Copied string: %s\n", str_copy);
        free(str_copy); // Remember to free the memory to avoid memory leaks
    } else {
        printf("Failed to allocate memory for the string copy.\n");
    }

    return 0;
}

// Function to get a copy of the string from the global variable gstr
char* get_gstr_copy(void) {
    // Allocate memory for the copy
    char *copy = malloc(strlen(gstr) + 1); // +1 for the null terminator
    if (copy == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Copy the string using strcpy
    strcpy(copy, gstr);

    return copy; // Return the copy
}
