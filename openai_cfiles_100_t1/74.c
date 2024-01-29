#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
} Object;

Object* createObject(const char* str) {
    Object* newObj = malloc(sizeof(Object));
    if (newObj == NULL) {
        return NULL; // Memory allocation failed
    }

    // Parse the string and set object properties
    char* token = strtok((char*)str, ",");
    if (token == NULL) {
        free(newObj);
        return NULL; // Invalid string format
    }
    newObj->id = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL) {
        free(newObj);
        return NULL; // Invalid string format
    }
    strncpy(newObj->name, token, sizeof(newObj->name) - 1);
    newObj->name[sizeof(newObj->name) - 1] = '\0';

    return newObj;
}


This function takes a string as input and returns a pointer to a dynamically allocated `Object` structure. It follows the format `id,name`, where `id` is an integer and `name` is a string.

The function uses `strtok()` to tokenize the input string based on the delimiter (`,`). It then converts the first token to an integer using `atoi()`, and copies the second token into the `name` field of the object structure using `strncpy()`.

If the string format is invalid or if memory allocation fails, the function returns `NULL`.