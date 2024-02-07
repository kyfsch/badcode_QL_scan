#include <stdio.h>  // For printf function

// Assume gstr is declared somewhere as a global null-terminated string
// For example: char gstr[] = "Global String";
extern char gstr[];  // Declaration of the global variable if it's not in the same file

// Function prototype
const char* retrieveGlobalString(void);

// Main function to demonstrate the retrieve function
int main(void) {
    const char* str = retrieveGlobalString();
    printf("Retrieved string: %s\n", str);
    return 0;
}

// Function to retrieve the global string
const char* retrieveGlobalString(void) {
    return gstr;  // Simply return the pointer to the global string
}
