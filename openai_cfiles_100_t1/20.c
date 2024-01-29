#include <stdio.h>

void __div0() {
    int *nullPointer = NULL;
    *nullPointer = 42; // Dereferencing a null pointer
}

int main() {
    printf("Triggering null pointer dereference vulnerability...\n");
    __div0();
    printf("Null pointer dereference vulnerability successfully triggered!\n");
    
    return 0;
}
