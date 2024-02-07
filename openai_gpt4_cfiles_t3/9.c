#include <stdio.h>
#include <string.h>

#define TITLE_ROW_OFFSET 4 // Number of rows to offset from the current cursor position

void SetDialogBoxTitle(char dialogBox[][80], int cursorRow, int cursorCol, const char* title) {
    int maxRows = sizeof(dialogBox) / sizeof(dialogBox[0]); // Assuming a fixed-size two-dimensional array of 80 columns
    int titleRow = cursorRow + TITLE_ROW_OFFSET;
    
    if (titleRow < maxRows) {
        // Ensure that the titleRow is within the bounds of the dialog box
        // Calculate the starting position so that the title is centered based on the cursorCol
        int titleLen = strlen(title);
        int titleStartCol = cursorCol - titleLen / 2;
        if (titleStartCol < 0) titleStartCol = 0; // Make sure the start column is not negative
        
        // Clear the title row
        memset(dialogBox[titleRow], ' ', 80);

        // Copy title to the specified position
        strncpy(&dialogBox[titleRow][titleStartCol], title, titleLen);
    }
}

// Example usage:
// Assuming this is a dialog box with 10 rows and 80 columns
int main() {
    char dialogBox[10][80]; // 2D array representing the dialog box
    memset(dialogBox, ' ', sizeof(dialogBox)); // Clear the dialog box

    int currentCursorRow = 1; // Current cursor row position
    int currentCursorCol = 40; // Current cursor column position (Assuming center is at column 40 for an 80 column width)

    SetDialogBoxTitle(dialogBox, currentCursorRow, currentCursorCol, "Example Dialog Title");