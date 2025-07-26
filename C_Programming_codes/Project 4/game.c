#include <stdio.h>

char board[3][3];  // Tic-tac-toe board
char currentPlayer = 'X';  // Starting player

// Function to initialize the board with numbers 1-9
void initializeBoard() {
    int counter = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = counter + '0';  // Convert number to character
            counter++;
        }
    }
}

// Function to display the board
void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Function to make a move
int makeMove(int move) {
    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    // Check if the cell is already occupied
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer;
        return 1;  // Valid move
    } else {
        return 0;  // Invalid move
    }
}

// Function to check if there is a winner
int checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;

    return 0;  // No winner yet
}

// Function to check if the board is full (draw)
int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;  // Board is not full
            }
        }
    }
    return 1;  // Board is full
}

// Function to switch players
void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

// Main function
int main() {
    int move, validMove;

    initializeBoard();

    while (1) {
        displayBoard();
        printf("Player %c, enter your move (1-9): ", currentPlayer);
        scanf("%d", &move);

        validMove = makeMove(move);
        if (!validMove) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        if (checkWin()) {
            displayBoard();
            printf("Player %c wins!\n", currentPlayer);
            break;
        }

        if (checkDraw()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}
