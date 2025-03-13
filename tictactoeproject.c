#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 5
#define MAX_MOVES 25
// Aysu ULUSOY Zeynep ÇAKIR Zührenur İYİDOĞAN
char board[MAX_SIZE][MAX_SIZE];
int moveHistory[MAX_MOVES][2]; 
int moveIndex = -1;
int boardSize; 

void printBoard() {
    printf("\n");
    for (int i = 0; i < boardSize; i++) { 
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == 'X') {
                printf(" \033[1;31m%c\033[0m ", board[i][j]); 
            } else if (board[i][j] == 'O') { 
                printf(" \033[1;34m%c\033[0m ", board[i][j]); 
            } else {
                printf(" %c ", board[i][j]);
            }
            if (j < boardSize - 1) printf("|");
        }
        printf("\n");
        if (i < boardSize - 1) {
            for (int j = 0; j < boardSize; j++) {
                printf("---");
                if (j < boardSize - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int isWinner(char player) {
    for (int i = 0; i < boardSize; i++) {
        int rowWin = 1, colWin = 1;
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] != player) rowWin = 0;
            if (board[j][i] != player) colWin = 0;
        }
        if (rowWin || colWin) return 1;
    }
    int diag1 = 1, diag2 = 1;
    for (int i = 0; i < boardSize; i++) {
        if (board[i][i] != player) diag1 = 0;
        if (board[i][boardSize - 1 - i] != player) diag2 = 0;
    }
    
    return diag1 || diag2;
}

int isFull() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void undoMove() {
    if (moveIndex >= 0) {
        int lastRow = moveHistory[moveIndex][0];
        int lastCol = moveHistory[moveIndex][1];
        board[lastRow][lastCol] = ' ';
        moveIndex--; 
    } else {
        printf("No moves to undo.\n");
    }
}

void redoMove(char player) {
    if (moveIndex < MAX_MOVES - 1 && moveHistory[moveIndex + 1][0] != -1) {
        int nextRow = moveHistory[moveIndex + 1][0];
        int nextCol = moveHistory[moveIndex + 1][1];
        board[nextRow][nextCol] = player;
        moveIndex++;
    } else {
        printf("No moves to redo.\n");
    }
}

int main() {
    printf("Select board size (3/4/5): ");
    scanf("%d", &boardSize);
    if (boardSize < 3 || boardSize > 5) {
        printf("Invalid size. Defaulting to 3x3.\n");
        boardSize = 3;
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < MAX_MOVES; i++) {
        moveHistory[i][0] = -1; 
        moveHistory[i][1] = -1;
    }

    char players[2] = {'X', 'O'};
    char currentPlayer = players[rand() % 2];
    printf("Player %c starts!\n", currentPlayer);

    while (1) {
        printBoard();
        int row, col;
        printf("Player %c, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        moveIndex++;
        moveHistory[moveIndex][0] = row;
        moveHistory[moveIndex][1] = col;

        if (isWinner(currentPlayer)) {
            printBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
            
        }

        if (isFull()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }

        int choice;
        printf("Do you want to undo your move? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        if (choice == 1) {
            undoMove();
            continue;
        }
        

        printf("Do you want to redo your move? (1 for yes, 0 for no): ");
        scanf("%d", &choice);
        if (choice == 1) {
            redoMove(currentPlayer);
            continue;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    return 0;
}
