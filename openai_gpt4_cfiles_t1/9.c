#include <stdio.h>
#include <stddef.h>

#define DIALOG_WIDTH  80  // Assuming dialog box width = 80 characters
#define TITLE_ROW_OFFSET 4  // Number of rows to offset title from current cursor

// Function to add title to the dialog box
// * `dialog` is a pointer to a 2D character array representing the dialog box
// * `rows` and `cols` are the dimensions of the dialog box (rows x cols)
// * `cursor_row` is the current cursor row within the dialog
// * `title` is the string to be added as the title
void addTitleToDialog(char (*dialog)[DIALOG_WIDTH], size_t rows, size_t cols, size_t cursor_row, const char *title) {
    // Calculate the row position for the title, ensuring it doesn't exceed the dialog box bounds
    size_t title_row = (cursor_row + TITLE_ROW_OFFSET < rows) ? cursor_row + TITLE_ROW_OFFSET : rows - 1;
    
    // Calculate center position for the title, so it can be placed at the center of the dialog box width
    size_t title_length = strlen(title);
    size_t title_pos = (cols - title_length) / 2;
    if(title_pos >= cols) {
        title_pos = cols - title_length - 1;  // Ensure title is not out of dialog box boundary
    }

    // Fill the row with spaces first to clear previous title if any
    for(size_t i = 0; i < cols; ++i) {
        dialog[title_row][i] = ' ';
    }

    // Add title to the dialog box at the calculated row and position
    snprintf(dialog[title_row] + title_pos, title_length + 1, "%s", title);
}

// Example usage of the function:
// int main() {
//     size_t dialog_rows = 10;
//     size_t dialog_cols = DIALOG_WIDTH;
//     char dialog[10][DIALOG_WIDTH];
//     size_t cursor_row = 0;  // Example cursor row
//     const char *title = "Dialog Title";
//
//     // Initialize the dialog with empty spaces
//     for(size_t i = 0; i < dialog_rows; ++i) {
//         for(size_t j = 0; j < dialog_cols; ++j) {
//             dialog[i][j] = ' ';
//         }
//     }
//
//     // Add the title to the dialog box
//     addTitleToDialog(dialog, dialog_rows, dialog_cols, cursor_row, title);
//
//     // Code to display the dialog box
//     // ...
//
//     return 0;
// }
