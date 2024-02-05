// This function is used to determine if the user pressed the Escape key and.
int on_key_esc(WINDOW *win) // WINDOW *win is the stdscr
{
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    int ch = wgetch(win); // get input character
    if (ch == -1)
    {
        // If the function returns -1, a timed out was performed.
        select(0, NULL, NULL, NULL, &timeout);
        return 1;
    }
    else if (ch == KEY_F('1'))
        return 2; // Exit
    else if (ch == 'l')
        return 3; // Exit (used in file)
    else if (ch == 'q')
        return 1; // exit
    else if (ch == 10)
        return 4;
    else
        return -1; // Error
}

////////////////////////////////////////////////////////////////////

#define IN_A_ROW 20

int prompt_text(WINDOW *win, char *prompt, char *reply, int max)
{
    int input_length = 0; // For determining the return value

    if (prompt != NULL)
    {
        // Prints the character
        mvwprintw(win, 1, 0, prompt);
        wrefresh(win);
    }

    int y = 2;

    // Inputs text
    while (input_length < max)
    {
        char ch = wgetch(win);

        if (ch == KEY_BACKSPACE) // When backspace pressed
        {
            // The previous char is deleted from the window.
            if (input_length > 0)
            {
                // The prompt is moved and the input is redrawn in the current position.
                int prompt_len = strlen(prompt);
                wmove(win, y, prompt_len + input_length - 1);
                waddch(win, ' ');     // Printing white space to erase characters.
                wmove(win, y, prompt_len + input_length);
                wclrtoe