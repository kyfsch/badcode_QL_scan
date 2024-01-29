#include <stdio.h>

void retrieveString(char* gstr, char* retrievedString) {
    int i = 0;
    while (gstr[i] != '\0') {
        retrievedString[i] = gstr[i];
        i++;
    }
    retrievedString[i] = '\0';
}

int main() {
    char gstr[] = "Hello, World!";
    char retrievedString[100];
    
    retrieveString(gstr, retrievedString);
    
    printf("Retrieved string: %s\n", retrievedString);
    
    return 0;
}


This code defines a function called `retrieveString` that takes two arguments: the input string `gstr` and an output buffer `retrievedString`. The function copies each character from `gstr` to `retrievedString` until it reaches the null terminator character (`'\0'`). Finally, it adds a null terminator character at the end of the `retrievedString` to ensure it is a valid C string.