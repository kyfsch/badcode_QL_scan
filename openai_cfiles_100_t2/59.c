#include <conio.h>

int isEscapeKeyPressed() {
    if (_kbhit()) {
        if (_getch() == 27) {  // ASCII value for Escape key is 27
            return 1;
        }
    }
    return 0;
}
