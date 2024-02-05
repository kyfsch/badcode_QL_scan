/// This function is used to determine if the user pressed the Escape key and.
int on_key_esc(WINDOW *win)

{

char c = 0; // A char variable to hold the value of the last arrow key the user types.

int cnt = 0;

	for(cnt = 0; cnt < 1000; ++cnt)

	{ // Loop to wait for the escape key to arrive before the program continues to

		// the next function.

		if((*win) != (NULL)) // A conditional to see if that the current window isn't

		{ // empty.

			wgetch(win); // The getch command puts the value from the current window

			if(KEY_LEFT == wgetch(win)) // into a variable.

			{

				if(wgetch(win)=='\n') // This part checks to see if the next keystroke

					break; // is an ENTER and if so, it quits the function

					// and goes to the next part of the program.

			}

			return 0; // This function is about to quit, so it says</s>