#include <stdbool.h>
#include <string.h>

bool isPanda(const char* board) {
    if (board == NULL) {
        return false;
    }

    int len = strlen(board);
    
    // PANDA has 5 characters
    if (len != 5) {
        return false;
    }

    // Check each character
    if (board[0] != 'P' || board[1] != 'A' || board[2] != 'N' || board[3] != 'D' || board[4] != 'A') {
        return false;
    }

    return true; // The board is PANDA
}
