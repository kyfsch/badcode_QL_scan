/// This function is used to add title to the dialog box. But when adding title with “%s “ (title string), the title string is output only to the fourth row of the current cursor position in the dialog box..
void print_title(WINDOW *dialog, const char *title, int width) {
	mvwprintw(dialog, 1, 0, "%s", title);
	for (int i = strlen(title); i < width; i++) {
		mvwprintw(dialog, 1, i, ".");
	}
	wrefresh(dialog);
}

// This function is used to show warning and error messages from the shell..
void print_status_message(WINDOW *dialog,const char *message, int padding, const int width, const int height) {
	wattron(dialog, A_BOLD);
	mvwprintw(dialog, height - (2 * padding), padding, "%s", message);
	wattroff(dialog, A_BOLD);
	for (int i = strlen(message); i < width; i++) {
		mvwprintw(dialog</s>