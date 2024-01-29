#include <stdbool.h>
#include <string.h>

bool isPandaBoard(const char* board) {
    if (strlen(board) != 5) { // Ensure the board name has 5 characters
        return false;
    }

    if (board[0] != 'P') {
        return false;
    }

    for (int i = 1; i < 5; i++) {
        if (board[i] != 'A') {
            return false;
        }
    }

    return true;
}
