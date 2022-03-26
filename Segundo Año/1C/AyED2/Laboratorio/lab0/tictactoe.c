#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


#define BOARD_SIZE 3
char board[BOARD_SIZE][BOARD_SIZE] = {
    { '-', '-', '-' },
    { '-', '-', '-' },
    { '-', '-', '-' }
};

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE]) {
    bool res = false;
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            if (board[i][j] == '-') {
                res = true;
            }
        }
    }
    return res;
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE]) {
    char res = '-';
    for (int i=0; i<BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            res = board[i][0];
        }
        else if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            res = board[0][i];
        }
        else if ((board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
                (board[2][0] == board[1][1] && board[2][0] == board[0][2])) {
            res = board[1][1];
        }
    }
    return res;
}

void playTicTacToe(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i=0; i<BOARD_SIZE; i++) {
        for (int j=0; j<BOARD_SIZE; j++) {
            printf("%d%d: ", i, j);
            scanf(" %c", &board[i][j]);
        } 
    }
    printf("\n");
}


int main(void) {
    playTicTacToe(board);
    bool hfc = has_free_cell(board);
    char gw = get_winner(board);

    printf("Has free cells: %s\n", hfc==1 ? "true" : "false");
    printf("Winner is: %c\n", gw);
}