#include <conio.h>

#define ESCAPE_KEY 27

/*
 * Function to check if the Escape key has been pressed.
 * Returns 1 (true) if Escape key is pressed, 0 (false) otherwise.
 */
int is_escape_pressed(void) {
    if (kbhit()) { // Non-blocking check for key press
        int ch = getch(); // Get the key value
        if (ch == ESCAPE_KEY) {
            return 1; // Escape key was pressed
        }
    }
    return 0; // No key was pressed or it was not the Escape key
}

// Example of usage
/*
int main() {
    printf("Press the Escape key...\n");
    while (!is_escape_pressed()) {
        // Wait for the Escape key to be pressed
    }
    printf("Escape key pressed, exiting the program.\n");
    return 0;
}
*/
