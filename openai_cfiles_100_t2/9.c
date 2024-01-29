
void addTitle(const char* title) {
    // Calculate the current cursor position
    int currentRow = getCurrentRow();

    // Calculate the starting row for the title string
    int titleRow = currentRow + 3;

    // Move the cursor to the starting row for the title string
    setCursor(titleRow, 0);

    // Output the title string
    printf("%s", title);

    // Move the cursor back to the original position
    setCursor(currentRow, 0);
}


In this code, `getCurrentRow()` is a function that returns the current row of the cursor, and `setCursor(row, column)` is a function that sets the cursor position to the specified row and column.