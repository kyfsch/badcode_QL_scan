#include <conio.h>

int isEscapePressed() {
    if (kbhit()) {
        if (getch() == 27) {  // ASCII value for Escape key is 27
            return 1;
        }
    }
    return 0;
}
