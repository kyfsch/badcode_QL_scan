#include <stdio.h>
#include <string.h>

void addTitleToDialog(const char* title) {
    // Move cursor to the fourth row
    for (int i = 0; i < 3; i++) {
        printf("\n");
    }
    // Print the title
    printf("%s\n", title);
}
