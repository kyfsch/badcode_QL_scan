#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define a structure to hold parsed data */
typedef struct Person {
    char* name;
    int age;
    float height;
} Person;

/* Function to create a new Person object by parsing a CSV string */
Person* createPersonFromCSV(const char* csvString) {
    /* Input format is assumed to be "name,age,height" */
    
    /* Allocate memory for a new Person object */
    Person* newPerson = (Person*)malloc(sizeof(Person));
    if (newPerson == NULL) {
        return NULL; // Allocation failed
    }

    /* Copy the input string to avoid modifying the original string */
    char* tempString = strdup(csvString);
    if(tempString == NULL) {
        free(newPerson);
        return NULL;
    }
    
    /* Parse the name */
    char* token = strtok(tempString, ",");
    newPerson->name = strdup(token);

    /* Parse the age */
    token = strtok(NULL, ",");
    if (token != NULL) {
        newPerson->age = atoi(token);
    } else {
        free(newPerson->name);
        free(tempString);
        free(newPerson);
        return NULL;
    }
    
    /* Parse the height */
    token = strtok(NULL, ",");
    if (token != NULL) {
        newPerson->height = atof(token);
    } else {
        free(newPerson->name);
        free(tempString);
        free(newPerson);
        return NULL;
    }

    /* Free the duplicate string */
    free(tempString);

    /* Return the new person object */
    return newPerson;
}

/* Function to deallocate a Person object */
void freePerson(Person* person) {
    if (person != NULL) {
        /* Free the dynamically allocated name string */
        free(person->name);
        /* Free the Person object itself */
        free(person);
    }
}

/* Main function to demonstrate usage */
int main() {
    const char* csvString = "John Doe,30,5.9";
    Person* person = createPersonFromCSV(csvString);

    if (person != NULL) {
        printf("Name: %s\nAge: %d\nHeight: %f\n", person->name, person->age, person->height);
        freePerson(person);
    } else {
        printf("Failed to create person from CSV.\n");
    }

    return 0;
}
