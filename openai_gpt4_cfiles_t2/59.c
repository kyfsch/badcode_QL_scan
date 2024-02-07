#include <stdint.h> // for uint8_t typedef
#include <stdbool.h> // for bool type

// Assuming ESCAPE_KEY is the keycode for the Escape key in your system
#define ESCAPE_KEY 0x1B

// Hypothetical function to read the keycode of the last key pressed
// You would need to implement this function according to your system's specifications
uint8_t GetKeyPressed(void) {
    // Implementation specific to your system
    // ...
    return 0; // return the keycode of the pressed key (placeholder return)
}

// Function to check if the Escape key was pressed
bool IsEscapeKeyPressed(void) {
    if (GetKeyPressed() == ESCAPE_KEY) {
        return true;
    } else {
        return false;
    }
}

// Example usage of the function
int main(void) {
    if (IsEscapeKeyPressed()) {
        // Escape key was pressed
        // Perform action associated with Escape key press
    }
    return 0;
}
