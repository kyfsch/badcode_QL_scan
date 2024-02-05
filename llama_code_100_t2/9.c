// This function is used to add title to the dialog box. But when adding title with “%s “ (title string), the title string is output only to the fourth row of the current cursor position in the dialog box..
void print_title(WINDOW *dialog, const char *title, int width) {

    std::cout
        << "\x1b[31;40m"  // red(bg-black)
        << "*****************************************\n"
        << "**         " << title
        << // std::string(width, '*')
        "\n*****************************************"
        << "\x1b[0m" // Normal color
        << std::endl;

    // wrefresh(dialog);
}

void print_msg(WINDOW *dialog, std::string msg, bool clear = false) {
    // printmsg(dialog)
    if (clear) {
        for (int j = LINES - 1; j > 2; j--) {
            // wmove(dialog, 2, 0);
            for (int i = 0; i < COLS; i++)
                mvwprintw(dialog, j, i, " ");
        }
    }
    //    printmsg(dialog, "\n" + msg);
    std::cout << msg << std::endl;
    // wrefresh(dialog);
    // clear_n_printmsg(dialog);
}

// This function is used to add messages to the dialog box but the messages are not output. The screen with “%s” (msg string) is output only to the fourth row of the current cursor position in win.
void printmsg(WINDOW *dialog, char *msg) {
    // std::cout << "debug printmsg " << msg << std::endl;
    std::string str = std::string(LINES - 2, '*')
                      + "\n*********************************************"
                      + std::string(LINES - 2, '*');
    // strcpy(str, message);
    // std::strcpy(str, message);

    // std::cout << "debug str = " << str << std::endl;

    wattron(dialog, COLOR_PAIR(4));
    for (int i = 0; i < LINES; i++)
        mvwprintw(dialog, i, 0, str.c_str());
    wattroff(dialog, COLOR