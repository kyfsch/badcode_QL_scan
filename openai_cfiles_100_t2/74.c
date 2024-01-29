#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
} Object;

Object* createObjectFromString(const char* str) {
    Object* newObject = (Object*) malloc(sizeof(Object));
    if (newObject == NULL) {
        return NULL; // Error allocating memory
    }

    // Parse the string and assign values to the object
    char* token = strtok((char*)str, ",");
    strcpy(newObject->name, token);

    token = strtok(NULL, ",");
    newObject->age = atoi(token);

    return newObject;
}

int main() {
    const char* input = "John Doe,25";
    Object* obj = createObjectFromString(input);

    if (obj != NULL) {
        printf("Name: %s\n", obj->name);
        printf("Age: %d\n", obj->age);
        free(obj);
    } else {
        printf("Error creating object\n");
    }

    return 0;
}


In the `createObjectFromString` function, we use the `strtok` function to tokenize the input string based on the comma delimiter. The first token is copied to the `name` field of the object using `strcpy`, and the second token is converted to an integer using `atoi` and assigned to the `age` field.

The function returns a pointer to the newly created object. If memory allocation fails, `NULL` is returned.