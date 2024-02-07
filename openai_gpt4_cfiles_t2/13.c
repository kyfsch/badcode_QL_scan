#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming the existence of a DialogType structure
typedef struct {
    char* title;
    // Other properties of the dialog can be added here
} DialogType;

// Function declaration
void setDialogTitle(DialogType *dialog, const char *title);

// Function definition
void setDialogTitle(DialogType *dialog, const char *title) {
    // Check if dialog is NULL
    if (dialog == NULL) {
        return;
    }

    // Free the existing title if any
    if (dialog->title != NULL) {
        free(dialog->title);
        dialog->title = NULL;
    }

    // If the new title is not NULL, allocate memory and set the new title
    if (title != NULL) {
        dialog->title = (char *)malloc(strlen(title) + 1); // +1 for the null-terminator
        if (dialog->title != NULL) {
            strcpy(dialog->title, title);
        }
    }
}

// Example use of the setDialogTitle function
int main() {
    DialogType myDialog = {NULL};

    // Set the title of the dialog
    setDialogTitle(&myDialog, "New Dialog Title");

    // Change the title of the dialog
    setDialogTitle(&myDialog, "Updated Dialog Title");

    // Remove the title of the dialog
    setDialogTitle(&myDialog, NULL);

    // Remember to free any allocated memory before the program exits
    if (myDialog.title) {
        free(myDialog.title);
    }

    return 0;
}
