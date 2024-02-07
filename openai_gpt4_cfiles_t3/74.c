#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define a structure to represent the Person object. */
typedef struct Person {
    char *name;
    int age;
} Person;

/* Function to create a new Person object by parsing a string. */
Person *create_person_from_string(const char *str) {
    /* A temporary buffer to hold the age part of the string. */
    char age_str[10];
    int name_length, age, i, j;

    /* Find the comma in the string, which separates name and age. */
    for (name_length = 0; str[name_length] != ',' && str[name_length] != '\0'; ++name_length);

    /* No comma found, or no characters before the comma (invalid input). */
    if (str[name_length] == '\0' || name_length == 0) {
        return NULL;
    }

    /* Allocate memory for the new Person object. */
    Person *new_person = (Person *)malloc(sizeof(Person));
    if (new_person == NULL) {
        return NULL;  // Failed to allocate memory.
    }

    /* Allocate memory for the name, include space for the null terminator. */
    new_person->name = (char *)malloc(name_length + 1);
    if (new_person->name == NULL) {
        free(new_person);
        return NULL;  // Failed to allocate memory.
    }

    /* Copy the name from the string to the Person object. */
    strncpy(new_person->name, str, name_length);
    new_person->name[name_length] = '\0';  // Null-terminate the name.

    /* Parse the age from the string. */
    for (i = name_length + 1, j = 0; str[i] != '\0'; ++i, ++j) {
        age_str[j] = str[i];
    }
    age_str[j] = '\0';  // Null-terminate the age string.

    /* Convert the age string to an integer. */
    age = atoi(age_str);
    new_person->age = age;

    return new_person;
}

/* A function to free the memory allocated for the Person object. */
void free_person(Person *person) {
    if (person) {
        free(person->name);
        free(person);
    }
}

/* Main function for demonstration. */
int main() {
    const char *person_str = "John Doe,30";
    Person *person = create_person_from_string(person_str);
    
    if (person) {
        printf("Name: %s\nAge: %d\n", person->name, person->age);
        free_person(person);
    } else {
        printf("Failed to create person from string.\n");
    }

    return 0;
}
